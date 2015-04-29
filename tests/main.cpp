#include <gtest/gtest.h>

#include "testclass.h"
#include "nzmqt/nzmqt.hpp"

void enableSignalHandling();

TEST(myWTF, testOneOne) {
    testclass cl;
    EXPECT_TRUE(cl.test());
}

TEST(myWTF, testOneTwo) {
    EXPECT_EQ(2, 2);
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
