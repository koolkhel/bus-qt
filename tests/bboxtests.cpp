#include <gtest/gtest.h>

#include "indigologger.h"
#include "dispatcher.h"
#include "modules/gpsmodule/gpsmodule.h"
#include "modules/test/test.h"
#include <QDebug>
#include <QTest>
#include <QSignalSpy>

#include <unistd.h>
#include <QtSql>

#include "sender_message.pb.h"
#include "geo_message.pb.h"
#include "blackbox_message.pb.h"

TEST(BBOX, sqlite) {
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(":memory:");

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

TEST(BBOX, create) {
    QStringList c;
    c << "[modules]"
      << "bbox_instance=blackbox"
      << "[bbox_instance]"
      << "nandDB=/opt/nanddb.sqlite"
      << "inputTopics=raw_gps";

    Dispatcher *dispatcher = new Dispatcher();
    dispatcher->initializeAll(c);
    dispatcher->startAll();

    ASSERT_TRUE(dispatcher->getModuleInstances().value("bbox_instance") != NULL);
}

TEST(BBOX, zeromq_version) {
    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    qDebug() << QString("%1.%2.%3").arg(major).arg(minor).arg(patch);

    ASSERT_GE(major, 4);
    ASSERT_EQ(minor, 0);
}

TEST(BBOX, overflowHandling) {
    QStringList c;
    c << "[modules]"
      << "bbox_instance=blackbox"
      << "test_instance=test_module"
      << "[bbox_instance]"
      << "nandDB=/opt/nanddb.sqlite"
      << "inputTopics=raw_gps"
       << "maxRamPages=10"
       << "ramPageSize=1024";

    Dispatcher *dispatcher = new Dispatcher();
    dispatcher->initializeAll(c);
    dispatcher->startAll();

    ASSERT_TRUE(dispatcher->getModuleInstances().value("bbox_instance") != NULL);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    ASSERT_TRUE(testModule != NULL);

    for (int i = 0; i < 400; i++) {
        ::indigo::pb::internal_msg positionMessage;
        ::indigo::pb::indigo_geo *geo = positionMessage.MutableExtension(::indigo::pb::indigo_geo::geo_coords_in);

        positionMessage.set_id(i);

        geo->set_longitude(35.5);
        geo->set_latitude(36.6);
        geo->mutable_unixtime()->set_time(QDateTime::currentMSecsSinceEpoch() / 1000);
        geo->set_satellites_used(10);

        testModule->sendMessage(positionMessage, "raw_gps");
        qApp->processEvents();
    }

    usleep(100 * 1000);

    for (int i = 0; i < 50000; i++) {
        qApp->processEvents();
    }
}

TEST(BBOX, sendingConfirmed) {
    QStringList c;
    c << "[modules]"
      << "bbox_instance=blackbox"
      << "test_instance=test_module"
      << "[bbox_instance]"
      << "nandDB=/opt/nanddb.sqlite"
      << "inputTopics=raw_gps"
       << "maxRamPages=10"
       << "ramPageSize=1024";

    Dispatcher *dispatcher = new Dispatcher();
    dispatcher->initializeAll(c);
    dispatcher->startAll();

    ASSERT_TRUE(dispatcher->getModuleInstances().value("bbox_instance") != NULL);

    TestModule *testModule = reinterpret_cast<TestModule *>(
                dispatcher->getModuleInstances().value("test_instance"));

    ASSERT_TRUE(testModule != NULL);

    testModule->subscribeTopic("to_send");

    for (int i = 0; i < 400; i++) {
        ::indigo::pb::internal_msg positionMessage;
        ::indigo::pb::indigo_geo *geo = positionMessage.MutableExtension(::indigo::pb::indigo_geo::geo_coords_in);

        positionMessage.set_id(i);

        geo->set_longitude(35.5);
        geo->set_latitude(36.6);
        geo->mutable_unixtime()->set_time(QDateTime::currentMSecsSinceEpoch() / 1000);
        geo->set_satellites_used(10);

        testModule->sendMessage(positionMessage, "raw_gps");
        qApp->processEvents();
    }

    for (int steps = 0; steps < 5; steps++) {
        usleep(1 * 1000 * 1000);

        for (int i = 0; i < 50000; i++) {
            qApp->processEvents();
        }
    }

    for (int i = 0; i < 30; i++) {
        ::indigo::pb::internal_msg message;
        ::indigo::pb::confirmed_messages *msg = message.MutableExtension(::indigo::pb::confirmed_messages::confirmed_messages_in);

        msg->add_message_ids(i);

        testModule->sendMessage(message, "confirmed_messages");
    }

    for (int steps = 0; steps < 5; steps++) {
        usleep(1 * 1000 * 1000);

        for (int i = 0; i < 50000; i++) {
            qApp->processEvents();
        }
    }
}
