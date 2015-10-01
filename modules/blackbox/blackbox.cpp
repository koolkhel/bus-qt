#include "blackbox.h"
#include <QtSql>

#include <sqlite3.h>

#include "blackbox_message.pb.h"

Q_LOGGING_CATEGORY(BLACKBOXC, "blackbox")


#define criticalCheck(result) do { \
    if (!result) { \
        qCWarning(BLACKBOXC) << "blackbox error: " << db.lastError().driverText(); \
    } \
} while (0)


BLACKBOX::BLACKBOX(QObject *parent)
{
    _sentRecordCount =0;
    _nandRecordCount = 0;
    _ramRecordCount = 0;
    _confirmedRecordCount = 0;
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

void BLACKBOX::handleConfirmedMessages(indigo::pb::internal_msg &message)
{
    qCDebug(BLACKBOXC) << "handleConfirmedMessages called";
    QString insertConfirmedText = "insert into ram.confirmed_data (confirmed_id) values (:id)";    
    QSqlQuery insertConfirmedQuery(db);
    criticalCheck(insertConfirmedQuery.prepare(insertConfirmedText));


    ::indigo::pb::confirmed_messages cm = message.GetExtension(::indigo::pb::confirmed_messages::confirmed_messages_in);

    int count = cm.message_ids_size();
    db.transaction();
    for (int i = 0; i < count; i++) {
        int id = cm.message_ids(i);
        qCDebug(BLACKBOXC) << "confirming message " << id;
        insertConfirmedQuery.bindValue(":id", id);

        // FIXME безопасно ли это делать? если кончится память, хорошо не будет
        criticalCheck(insertConfirmedQuery.exec());
        //qCDebug(BLACKBOXC) << insertConfirmedQuery.lastError();
    }

    db.commit();
}

void BLACKBOX::respond(QString topic, indigo::pb::internal_msg &message)
{
    if (topic == confirmedMessagesTopic) {
        handleConfirmedMessages(message);
    } else {
        QByteArray data = QByteArray::fromStdString(message.SerializeAsString());
        store(message.id(), data);
    }
}

void BLACKBOX::doBlackboxJob()
{
    // 1. выяснить обстановку

    collectStatistics();
    // 2. если что-то надо еще отдать в отправленное, делаем
    int maxRecordCount = getConfigurationParameter("maxRecordCount", 30).toInt();

    if (_sentRecordCount < maxRecordCount) {
        int toSend = maxRecordCount - _sentRecordCount;

        QString selectString =
                "select "
                "s.id as id, st.sent_id, s.data as data, s.storage as storage "
                "from stored_data s left join ram.sent_data st "
                "on s.id = st.sent_id "
                "where st.sent_id IS NULL "
                "order by s.id ASC limit :limit";
        QSqlQuery selectQuery(db);
        criticalCheck(selectQuery.prepare(selectString));

        selectQuery.bindValue(":limit", toSend);

        bool result = selectQuery.exec();
        if (!result) {
            qCCritical(BLACKBOXC) << "cannot select from DB: " << db.lastError().text();
        }

        while (selectQuery.next()) {
            int id = selectQuery.value("id").toInt();
            QByteArray data = selectQuery.value("data").toByteArray();
            QString storage = selectQuery.value("storage").toString();

            ::indigo::pb::internal_msg message;
            message.ParseFromArray(data.data(), data.size());

            if (!message.IsInitialized()) {
                qCWarning(BLACKBOXC) << "rubbish message id " << id;
                continue;
            }
            qCDebug(BLACKBOXC) << "publishing data from storage: " << storage << " with id: " << id << " bytes: " << data.toHex();
            // выдаем все модулю передачи
            publish(message, "to_send");

            QString insertIntoSentQuery = "insert into ram.sent_data (sent_id) values (:id)";
            QSqlQuery insertIntoSent(db);
            criticalCheck(insertIntoSent.prepare(insertIntoSentQuery));

            qCDebug(BLACKBOXC) << "issuing " << insertIntoSentQuery << " with id " << id;
            insertIntoSent.bindValue(":id", id);
            criticalCheck(insertIntoSent.exec());
        }
    } else {
        qCDebug(BLACKBOXC) << "not ready to send anything";
    }
}

void BLACKBOX::store(int id, QByteArray data)
{
    QSqlQuery insertQuery(db);
    criticalCheck(insertQuery.prepare("insert into ram_data (id, data) values (:id, :data)"));

    insertQuery.bindValue(":id", id);
    insertQuery.bindValue(":data", data);

    bool result = insertQuery.exec();
    if (result) {
        qCDebug(BLACKBOXC) << "inserting record #" << id;
    } else {
        // SQLITE_FULL
        if (db.lastError().number() == -1) {
            qCDebug(BLACKBOXC) << "failure inserting: " << db.lastError().number() << "; performing copy to NAND";
            copyFromRAMtoNAND();
        }

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

    //sqlite3_trace(static_cast<sqlite3 *>(db.driver()->handle().value<void *>()), trace, NULL);

    initializeDB();
    // подписываемся сразу на все, что задано в аргументах
    QStringList topics = getConfigurationParameter("inputTopics", "").toString().split(",");

    foreach (QString topic, topics) {
        subscribe(topic);
    }

    confirmedMessagesTopic = getConfigurationParameter("confirmedMessagesTopic", "confirmed_messages").toString();
    subscribe(confirmedMessagesTopic);

    bbTimer = new QTimer(this);
    bbTimer->setInterval(500);
    bbTimer->setSingleShot(false);

    connect(bbTimer, SIGNAL(timeout()), SLOT(doBlackboxJob()));

    bbTimer->start();
}

void BLACKBOX::stop()
{
    bbTimer->stop();
}

void BLACKBOX::initializeDB()
{
    executeDDL("ATTACH DATABASE ':memory:' AS 'ram'");
    // 1M хранимых данных
    //executeDDL("PRAGMA ram.PAGE_SIZE = 4096");
    //executeDDL("PRAGMA ram.MAX_PAGE_COUNT = 256");
    executeDDL(QString("PRAGMA temp_store = 2"));
    executeDDL(QString("PRAGMA temp_store_directory = '/var/'"));
    executeDDL(QString("PRAGMA ram.PAGE_SIZE = %1")
               .arg(getConfigurationParameter("ramPageSize", 4096).toInt()));
    executeDDL(QString("PRAGMA ram.MAX_PAGE_COUNT = %1")
               .arg(getConfigurationParameter("maxRamPages", 256).toInt()));

    //fprintf(stderr, "temp = %s\n", sqlite3_temp_directory);

    // хранилище в ПЗУ
    //executeDDL("DROP TABLE IF EXISTS main.nand_data");
    executeDDL("CREATE TABLE IF NOT EXISTS main.nand_data ("
      "id   INT NOT NULL,"
      "data BLOB,"
      "PRIMARY KEY (id))");
    //executeDDL("DROP INDEX IF EXISTS main.nand_data_idx");
    executeDDL("CREATE INDEX IF NOT EXISTS main.nand_data_idx ON nand_data (id);");

    // хранилище в ОЗУ
    //executeDDL("DROP TABLE IF EXISTS ram.ram_data");
    executeDDL("CREATE TABLE IF NOT EXISTS ram.ram_data ("
      "id   INT NOT NULL,"
      "data BLOB,"
      "PRIMARY KEY (id))");
    //executeDDL("DROP INDEX IF EXISTS ram.ram_data_idx");
    executeDDL("CREATE INDEX IF NOT EXISTS ram.ram_data_idx ON ram_data (id)");

    // подтвержденные данные
    //executeDDL("DROP TABLE IF EXISTS ram.confirmed_data");
    executeDDL("CREATE TABLE IF NOT EXISTS ram.confirmed_data ("
      "confirmed_id INT NOT NULL,"
      "PRIMARY KEY (confirmed_id))");

    //executeDDL("DROP TABLE IF EXISTS ram.sent_data");
    executeDDL("CREATE TABLE IF NOT EXISTS ram.sent_data ("
      "sent_id INT NOT NULL,"
      "PRIMARY KEY (sent_id))");

    // отсюда делаем выборки для передачи сендеру и сохраняем всё, что приходит по топикам (неважно, что)
    //executeDDL("DROP VIEW IF EXISTS stored_data");
    executeDDL("CREATE TEMP VIEW stored_data  AS     SELECT        id,        data, \"RAM\" AS STORAGE "
      "FROM ram.ram_data UNION                                       SELECT        id,        data,  \"NAND\" AS STORAGE "
      "FROM main.nand_data      ORDER BY id        ASC");

    // если удаляем из view, сносим так же с любого хранилища
    //executeDDL("DROP TRIGGER IF EXISTS stored_data_delete_trg");
    executeDDL("CREATE TEMPORARY TRIGGER stored_data_delete_trg INSTEAD OF DELETE ON stored_data "
    "BEGIN "
      "DELETE FROM nand_data "
      " WHERE id = OLD.id; "
      " DELETE FROM ram_data "
      " WHERE id = OLD.id; "
    " END; ");

    // статистика для того, чтобы алгоритм ориентировался
    //executeDDL("DROP VIEW IF EXISTS STATS");
    executeDDL("CREATE TEMP VIEW STATS    AS "
                      "SELECT count(*) AS CNT, 'CONFIRMED' AS TYPE FROM confirmed_data "
      " UNION SELECT count(*) AS CNT, 'SENT' AS TYPE FROM sent_data"
      " UNION SELECT count(*) AS CNT, 'NAND_DATA' AS TYPE FROM nand_data "
      " UNION SELECT count(*) AS CNT, 'RAM_DATA' AS TYPE FROM ram_data "
      " ORDER BY TYPE");

    // если подтвердили передачу данных, то мы из всех возможных таблиц всё удаляем
    //executeDDL("DROP TRIGGER IF EXISTS confirmed_data_trigger");
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
    QString selectIntoText = "INSERT INTO nand_data (id, data) SELECT id, data FROM ram_data;";
    result &= selectInto.exec(selectIntoText);
    qCDebug(BLACKBOXC) << selectIntoText;
    selectInto.finish();

    QSqlQuery deleteFrom(db);
    QString deleteFromText = "DELETE FROM ram_data";
    result &= deleteFrom.exec(deleteFromText);
    qCDebug(BLACKBOXC) << deleteFromText;
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

#if 0
    QSqlQuery sentQuery(db);
    criticalCheck(sentQuery.exec("select sent_id from ram.sent_data"));
    while (sentQuery.next()) {
        qCDebug(BLACKBOXC) << "sent_id: " << sentQuery.value("sent_id").toInt();
    }

    QSqlQuery storedQuery(db);
    criticalCheck(storedQuery.exec("select id from stored_data"));
    while (storedQuery.next()) {
        qCDebug(BLACKBOXC) << "stored_id: " << storedQuery.value("id").toInt();
    }
#endif
}
