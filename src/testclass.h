#ifndef TESTCLASS_H
#define TESTCLASS_H
#include <nzmqt/nzmqt.hpp>

class testclass : public QObject
{
    nzmqt::ZMQSocket* subscriber;
    nzmqt::ZMQSocket* pusher;
public:
    testclass(QObject *parent=0);
    bool test();
};

#endif // TESTCLASS_H
