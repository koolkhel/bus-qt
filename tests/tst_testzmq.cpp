#include <QString>
#include <QtTest>

#include "testclass.h"

class TestZMQ : public QObject
{
    Q_OBJECT

public:
    TestZMQ();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testPubSub();
};

TestZMQ::TestZMQ()
{
}

void TestZMQ::initTestCase()
{
}

void TestZMQ::cleanupTestCase()
{
}

void TestZMQ::testPubSub()
{
    testclass cl;
    QVERIFY2(cl.test(), "Failure");
}

QTEST_APPLESS_MAIN(TestZMQ)

#include "tst_testzmq.moc"
