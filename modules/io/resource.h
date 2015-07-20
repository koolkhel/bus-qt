#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include <QFile>

class Resource
{
public:
    explicit Resource(QString name);

    void setName(QString name);
    QByteArray read();
    void write(QByteArray);
    QString getName();
private:
    QString resourceName;
    QFile file;
    void open();
};

#endif // RESOURCE_H
