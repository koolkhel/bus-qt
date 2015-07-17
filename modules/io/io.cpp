#include "io.h"
#include "io_message.pb.h"

#include "resource.h"

Q_LOGGING_CATEGORY(IOC, "io")

IO::IO(QObject *parent)
{
    setParent(parent);

    this->name = "io works";

    qCDebug(IOC, "hello,world");
}

IO::~IO()
{
    stop();
}

QStringList IO::getPubTopics()
{
    QStringList topics;

    return topics;
}

void IO::respond(QString topic, indigo::pb::internal_msg &message)
{
}

void IO::publish(QByteArray data)
{
    qDebug() << data;

    ::indigo::pb::io_message io;
    io.set_content(data.toStdString());


    Module::publish(io, "io");
}

void IO::start()
{
    stop();

    QStringList devices = getConfigurationParameter("devices", "").toString().split(",");

    for(int i = 0; i < devices.size(); ++i) {
        QSharedPointer<AbstractResource> resource = QSharedPointer<AbstractResource>(new Resource(devices.at(i)));
        data[resource->getName()] = new ControlledResource(resource);

        connect(data[resource->getName()], SIGNAL(dataReady(QByteArray)),
                this, SLOT(publish(QByteArray)));
    }
}

void IO::stop()
{
    foreach(QString key, data.keys()) {
        delete data[key];
    }

    data.clear();
}
