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

char Resource::read()
{
    open();
    char value;

    stream >> value;

    return value;
}

void Resource::open()
{
    if(!file.isOpen()) {
        if(file.open(QIODevice::ReadWrite)) {
            stream.setDevice(&file);
        } else {
            qDebug() << "error opening resource file";
        }
    } else {
        stream.seek(0);
    }
}

void Resource::write(char data)
{
    open();

    stream << data;
}

QString Resource::getName()
{
    return QString("file_resource_%1").arg(file.fileName());
}

