#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include <QFile>
#include "abstractresource.h"

class Resource : public AbstractResource
{
    Q_OBJECT
public:
    explicit Resource(QString name, QObject *parent = 0);
    void setName(QString name);
public slots:
    QByteArray read();
    void write(QByteArray);
    QString getName();
private:
    QString resourceName;
    QFile file;
    void open();
};

#endif // RESOURCE_H
