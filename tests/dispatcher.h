#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <QMap>
#include <QString>
#include <functional>

class Dispatcher
{
    QMap<QString,QString> modules;
public:
    Dispatcher();
    void publish(QString);
    static void dispatch();
    static void sub();

};

#endif // DISPATCHER_H
