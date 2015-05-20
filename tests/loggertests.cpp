#include <gtest/gtest.h>

#include "indigologger.h"
#include "loggertester.h"
#include <QtNetwork/QTcpSocket>

#include <QDebug>
#include <QTest>
#include <QSignalSpy>

class IndigoLoggingTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        qInstallMessageHandler(indigoMessageHandler);
        indigoLoggerStart();
    }

    virtual void TearDown() {
        indigoLoggerStop();
    }


    LoggerTester tester;
};

TEST_F(IndigoLoggingTest, testLog) {

    QString lastStr;

    lastStr = QString("fuck you");
    qDebug() << lastStr;
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.simplified().contains(lastStr.simplified()));

    lastStr = QString("hello, world!");
    qDebug () << lastStr;
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.simplified().contains(lastStr.simplified()));

    lastStr = QString("wtf %1").arg(5);
    qCritical(qPrintable(lastStr));
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.simplified().contains(lastStr.simplified()));
}

TEST_F(IndigoLoggingTest, categories) {
    qCDebug(GSM, "Gsm test");
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.contains("indigo.gsm"));

    qCWarning(ZMQ, "ZMQ not working");
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.contains("indigo.zmq"));
}

TEST_F(IndigoLoggingTest, configuration) {
    qCDebug(ZMQ, "Gsm test");
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.simplified().contains("Gsm test"));

    QSignalSpy spy(instance, SIGNAL(configurationChanged()));

    tester.putConf("indigo.gsm=false");

    spy.wait(500000);

    ASSERT_TRUE(spy.size() != 0);
    QList<QVariant> signal = spy.at(0);

    qCWarning(ZMQ, "ZMQ not working");
    qCDebug(GSM, "Gsm test");
    tester.wait();
    ASSERT_FALSE(tester.lastMessage.simplified().contains("Gsm test"));
}



