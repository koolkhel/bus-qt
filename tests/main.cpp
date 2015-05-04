#include <gtest/gtest.h>

#include "testclass.h"
#include "nzmqt/nzmqt.hpp"

#include "indigologger.h"
#include "loggertester.h"

void enableSignalHandling();

TEST(logging, testLog) {
    LoggerTester tester;

    QString lastStr;

    lastStr = QString("fuck you");
    ISL_DEBUG(lastStr);
    tester.wait();
    //ASSERT_STREQ(lastStr.simplified().toStdString().c_str(), tester.lastMessage.simplified().toStdString().c_str());
    ASSERT_TRUE(tester.lastMessage.simplified().contains(lastStr.simplified()));

    lastStr = QString("hello, world!");
    ISL_ERROR(lastStr);
    tester.wait();
    //ASSERT_STREQ(lastStr.simplified().toStdString().c_str(), tester.lastMessage.simplified().toStdString().c_str());
    ASSERT_TRUE(tester.lastMessage.simplified().contains(lastStr.simplified()));

    lastStr = QString("wtf %1").arg(5);
    ISL_DEBUG(lastStr);
    tester.wait();
    ASSERT_TRUE(tester.lastMessage.simplified().contains(lastStr.simplified()));
    //ASSERT_STREQ(lastStr.simplified().toStdString().c_str(), .toStdString().c_str());
}

TEST(Zmq, testWTF) {
    QObject obj;
    nzmqt::ZMQContext* context = nzmqt::createDefaultContext(&obj);
    context->start();
    context->stop();
}

int main(int argc, char **argv) {
    enableSignalHandling();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
