#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QMap>
#include <QString>
#include <functional>
#include <QObject>
#include "module.h"
#include "topic.h"
#include "context.h"
#include <map>

class Dispatcher : public QObject
{
    Q_OBJECT

    friend class ModuleP;
    friend class Module;

    // имя, модуль
    std::map<QString,Module *> modules;
public:
    Dispatcher();
    virtual ~Dispatcher();

    Module* addModule(Module *,QString);

    void publish(Module *mod, QByteArray Data, QString Topic);
    //void sub(Module *, Topic);
private:
    Context *context;
};

#endif // DISPATCHER_H
