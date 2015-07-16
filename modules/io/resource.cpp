#include "resource.h"
#include <QLoggingCategory>
Resource::Resource(QString name, QObject *parent)
    :
      QObject(parent),
      resourceName(name)
{
    file.setFileName(name);
    open();
}

void Resource::setName(QString name)
{
    resourceName = name;
}

QByteArray Resource::read()
{
    open();

    QByteArray data = file.readAll();

    if(data.size()) {
        Q_EMIT DataReady(data);
    }

    return data;
}

void Resource::open()
{
    if(!file.isOpen()) {
        if(file.open(QIODevice::ReadWrite)) {
            qDebug() << "error opening resource file";
        }
    }
}

void Resource::write(QByteArray data)
{
    open();

    if(file.write(data) != data.size()) {
        qDebug() << "error writing resource file";
    }
    file.close();
}

