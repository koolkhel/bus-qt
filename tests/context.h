#ifndef CONTEXT_H
#define CONTEXT_H
#include <nzmqt/nzmqt.hpp>
#include <QObject>

class Context: public QObject
{
    Q_OBJECT
    static Context *pInstance;
public:
    Context();
    static Context* instance();
    Context(const Context&);
    nzmqt::ZMQContext* context;

};

#endif // CONTEXT_H
