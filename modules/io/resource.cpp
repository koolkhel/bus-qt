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

int32_t Resource::read()
{
    open();
    int32_t value;

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

void Resource::write(int32_t data)
{
    open();

    stream << data;
}

QString Resource::getName()
{
    return QString("file_resource_%1").arg(file.fileName());
}

