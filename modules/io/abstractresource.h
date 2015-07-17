#ifndef ABSTRACTRESOURCE
#define ABSTRACTRESOURCE
#include <QObject>
#include <QByteArray>
#include <QString>

class AbstractResource : public QObject
{
    Q_OBJECT
public:
    AbstractResource(QObject *parent = 0) : QObject(parent) {}
public slots:
    virtual QByteArray read() = 0;
    virtual void write(QByteArray) = 0;
    virtual QString getName() = 0;
};

#endif // ABSTRACTRESOURCE

