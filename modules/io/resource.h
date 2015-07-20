#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
class Resource
{
public:
    explicit Resource(QString name);

    void setName(QString name);
    char read();
    void write(char);
    QString getName();
private:
    QString resourceName;
    QFile file;
    QTextStream stream;

    void open();
};

#endif // RESOURCE_H
