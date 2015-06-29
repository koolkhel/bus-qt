#include "blackbox.h"
#include <QtSql>

Q_LOGGING_CATEGORY(BLACKBOXC, "blackbox")



BLACKBOX::BLACKBOX(QObject *parent)
    :
      _sentRecordCount(0),
      _nandRecordCount(0),
      _ramRecordCount(0),
      _confirmedRecordCount(0)
{
    setParent(parent);

    this->name = "blackbox works";

    qCDebug(BLACKBOXC, "hello,world");
}

BLACKBOX::~BLACKBOX()
{

}

QStringList BLACKBOX::getPubTopics()
{
    QStringList topics;

    return topics;
}

void BLACKBOX::respond(QString topic, indigo::pb::internal_msg &message)
{
    QByteArray data = QByteArray::fromStdString(message.SerializeAsString());

    QSqlQuery insertQuery(db);
    criticalCheck(insertQuery.prepare("insert into ram_data (id, data) values (:id, :data)"));

    insertQuery.bindValue(":id", message.id());
    insertQuery.bindValue(":data", data);

    bool result = insertQuery.exec();
    if (result) {
        qCDebug(BLACKBOXC) << "inserting record #" << message.id();
    } else {
        qCDebug(BLACKBOXC) << "failure inserting: " << db.lastError().text();
    }
}

void BLACKBOX::start()
{
    QString dbName = getConfigurationParameter("nandDB", "/opt/nand.db").toString();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qFatal(qPrintable(db.lastError().text()));
    }

    initializeDB();
    // подписываемся сразу на все, что задано в аргументах
    QStringList topics = getConfigurationParameter("inputTopics", "").toString().split(",");

    foreach (QString topic, topics) {
        subscribe(topic);
    }
}

void BLACKBOX::stop()
{
}

void BLACKBOX::initializeDB()
{
    executeDDL("ATTACH DATABASE ':memory:' AS 'ram'");
    // 1M хранимых данных
    executeDDL("PRAGMA ram.PAGE_SIZE = 4096");
    executeDDL("PRAGMA ram.MAX_PAGE_COUNT = 256");

    // хранилище в ПЗУ
    executeDDL("DROP TABLE IF EXISTS main.nand_data");
    executeDDL("CREATE TABLE main.nand_data ("
      "id   INT NOT NULL,"
      "data BLOB,"
      "PRIMARY KEY (id))");
    executeDDL("DROP INDEX IF EXISTS main.nand_data_idx");
    executeDDL("CREATE INDEX main.nand_data_idx ON nand_data (id);");

    // хранилище в ОЗУ
    executeDDL("DROP TABLE IF EXISTS ram.ram_data");
    executeDDL("CREATE TABLE ram.ram_data ("
      "id   INT NOT NULL,"
      "data BLOB,"
      "PRIMARY KEY (id))");
    executeDDL("DROP INDEX IF EXISTS ram.ram_data_idx");
    executeDDL("CREATE INDEX ram.ram_data_idx ON ram_data (id)");

    // подтвержденные данные
    executeDDL("DROP TABLE IF EXISTS ram.confirmed_data");
    executeDDL("CREATE TABLE ram.confirmed_data ("
      "confirmed_id INT NOT NULL,"
      "PRIMARY KEY (confirmed_id))");

    executeDDL("DROP TABLE IF EXISTS ram.sent_data");
    executeDDL("CREATE TABLE ram.sent_data ("
      "sent_id INT NOT NULL,"
      "PRIMARY KEY (sent_id))");

    // отсюда делаем выборки для передачи сендеру и сохраняем всё, что приходит по топикам (неважно, что)
    executeDDL("DROP VIEW IF EXISTS stored_data");
    executeDDL("CREATE TEMP VIEW stored_data  AS     SELECT        id,        data, \"RAM\" AS STORAGE "
      "FROM ram.ram_data UNION                                       SELECT        id,        data,  \"NAND\" AS STORAGE "
      "FROM main.nand_data      ORDER BY id        ASC");

    // если удаляем из view, сносим так же с любого хранилища
    executeDDL("DROP TRIGGER IF EXISTS stored_data_delete_trg");
    executeDDL("CREATE TEMPORARY TRIGGER stored_data_delete_trg INSTEAD OF DELETE ON stored_data "
    "BEGIN "
      "DELETE FROM nand_data "
      " WHERE id = OLD.id; "
      " DELETE FROM ram_data "
      " WHERE id = OLD.id; "
    " END; ");

    // статистика для того, чтобы алгоритм ориентировался
    executeDDL("DROP VIEW IF EXISTS STATS");
    executeDDL("CREATE TEMP VIEW STATS    AS "
                      "SELECT count(*) AS CNT, 'CONFIRMED' AS TYPE FROM confirmed_data "
      " UNION SELECT count(*) AS CNT, 'SENT' AS TYPE FROM sent_data"
      " UNION SELECT count(*) AS CNT, 'NAND_DATA' AS TYPE FROM nand_data "
      " UNION SELECT count(*) AS CNT, 'RAM_DATA' AS TYPE FROM ram_data "
      " ORDER BY TYPE");

    // если подтвердили передачу данных, то мы из всех возможных таблиц всё удаляем
    executeDDL("DROP TRIGGER IF EXISTS confirmed_data_trigger");
    executeDDL("CREATE TEMPORARY TRIGGER confirmed_data_trigger AFTER INSERT ON ram.confirmed_data "
    " BEGIN "
      " DELETE FROM confirmed_data WHERE confirmed_id = NEW.confirmed_id; "
      " DELETE FROM sent_data WHERE sent_id = NEW.confirmed_id; "
      " DELETE FROM stored_data WHERE id = NEW.confirmed_id;"
    " END;");
}

// все ошибки фатальны, их быть не должно
void BLACKBOX::executeDDL(QString queryText)
{
    QSqlQuery query(db);
    bool result = query.exec(queryText);
    if (!result) {
        qFatal(qPrintable(db.lastError().text()));
    }
}

void BLACKBOX::copyFromRAMtoNAND()
{
    bool result = true;

    db.transaction();

    QSqlQuery selectInto(db);
    result &= selectInto.exec("INSERT INTO nand_data (id, data) SELECT id, data FROM ram_data;");
    selectInto.finish();

    QSqlQuery deleteFrom(db);
    result &= deleteFrom.exec("DELETE FROM ram_data");
    deleteFrom.finish();

    db.commit();

    criticalCheck(result);
}

void BLACKBOX::collectStatistics()
{
    QSqlQuery statsQuery(db);
    criticalCheck(statsQuery.exec("SELECT CNT, TYPE FROM STATS"));

    while (statsQuery.next()) {
        QString type = statsQuery.value("TYPE").toString();
        int cnt = statsQuery.value("CNT").toInt();

        if (type == "NAND_DATA") {
            qCDebug(BLACKBOXC) << "nand record count: " << cnt;
            _nandRecordCount = cnt;
        } else if (type == "RAM_DATA") {
            qCDebug(BLACKBOXC) << "ram record count: " << cnt;
            _ramRecordCount = cnt;
        } else if (type == "CONFIRMED") {
            qCDebug(BLACKBOXC) << "confirmed record count: " << cnt;
            _confirmedRecordCount = cnt;
        } else if (type == "SENT") {
            qCDebug(BLACKBOXC) << "sent record count: " << cnt;
            _sentRecordCount = cnt;
        }
    }
}

void BLACKBOX::criticalCheck(bool result) {
    if (!result) {
        qFatal(qPrintable(db.lastError().text()));
    }
}
