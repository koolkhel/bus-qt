#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <QMap>
#include <QString>
#include <functional>

class Dispatcher : public QObject
{
    Q_OBJECT

    friend class ModuleP;
    friend class Module;
    QMap<QString,Module> modules;
public:
    Dispatcher();
    virtual ~Dispatcher();
    void addModule(Name, Module *);

    void publish(Module, QByteArray Data, QString Topic);

    void sub(Module, Topic);
private:
    nzmqt::ZMQContext *context;
};

#endif // DISPATCHER_H
