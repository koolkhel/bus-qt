#include "resource.h"
#include <QLoggingCategory>
Resource::Resource(QString name)
    :
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
    return file.readAll();
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

QString Resource::getName()
{
    return QString("file_resource_%1").arg(file.fileName());
}

