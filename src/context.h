#ifndef CONTEXT_H
#define CONTEXT_H
#include <nzmqt/nzmqt.hpp>
#include <QObject>

class Context: public QObject
{
    Q_OBJECT
public:
    Context();
    static Context* instance();
    Context(const Context&);
    nzmqt::PollingZMQContext* context;
    void stop();
private:
    static Context *pInstance;
};

#endif // CONTEXT_H
