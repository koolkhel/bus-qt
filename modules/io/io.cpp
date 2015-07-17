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

void IO::publish(QByteArray data, QString name)
{
    qDebug() << data;

    ::indigo::pb::io_message io;
    io.set_content(data.toStdString());
    io.set_resource_name(name.toStdString());

    Module::publish(io, "io");
}

void IO::start()
{
    stop();

    QStringList devices = getConfigurationParameter("devices", "").toString().split(",");

    for(int i = 0; i < devices.size(); ++i) {
        QSharedPointer<AbstractResource> resource = QSharedPointer<AbstractResource>(new Resource(devices.at(i)));
        data[resource->getName()] = new ControlledResource(resource);

        connect(data[resource->getName()], SIGNAL(dataReady(QByteArray,QString)),
                this, SLOT(publish(QByteArray,QString));
    }
}

void IO::stop()
{
    foreach(QString key, data.keys()) {
        delete data[key];
    }

    data.clear();
}
