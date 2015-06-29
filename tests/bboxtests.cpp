#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "gpsmodule.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>


#include <QtSql>

TEST(BBOX, sqlite) {
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("tests.db");

    ASSERT_TRUE(sdb.open()) << "could not access database";

    QSqlQuery create(sdb);
    ASSERT_TRUE(create.exec("create table if not exists mydata(sample_id INTEGER PRIMARY KEY, data BLOB)"))
            << qPrintable(sdb.lastError().text());

    QSqlQuery insert(sdb);
    ASSERT_TRUE(insert.prepare("insert into mydata (sample_id, data) values (:id, :data)"));
    insert.bindValue(":id", 500);
    insert.bindValue(":data", QString("hello").toLocal8Bit());
    bool result = insert.exec();
    QSqlError error = sdb.lastError();
    // ASSERT_TRUE(result) << qPrintable(error.text());


    QSqlQuery select(sdb);
    ASSERT_TRUE(select.exec("select sample_id, data from mydata"));
    QSqlRecord rec = select.record();

    int col0 = rec.indexOf("sample_id");
    int col1 = rec.indexOf("data");
    while (select.next()) {
        int id = select.value(col0).toInt();
        QByteArray data = select.value(col1).toByteArray();

        qDebug() << id;
        ASSERT_EQ(id, 500) << "wrong id";
        ASSERT_TRUE(QString::fromLocal8Bit(data) == "hello") << "wrong data";
    }
}
