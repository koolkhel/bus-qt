#include "io.h"
#include "io_message.pb.h"
Q_LOGGING_CATEGORY(IOC, "io")

IO::IO(QObject *parent)
{
    setParent(parent);

    this->name = "io works";

    qCDebug(IOC, "hello,world");
}

IO::~IO()
{

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
    io.set_content_string(data.toStdString());

    Module::publish(io, "io");
}

void IO::start()
{
    stop();

    QStringList devices = getConfigurationParameter("devices", "").toString().split(",");
    data.resize(devices.size());

    for(int i = 0; i < devices.size(); ++i) {
        data[i].first = new Resource(devices.at(i));
        data[i].second = new QTimer();
        data[i].second->setSingleShot(false);

        connect(data[i].second, SIGNAL(timeout()),
                data[i].first, SLOT(read()));

        connect(data[i].first, SIGNAL(DataReady(QByteArray)),
                this, SLOT(publish(QByteArray)));

        data[i].second->start(50);
    }
}

void IO::stop()
{
    for(int i = 0; i < data.size(); ++i) {
        data[i].first->deleteLater();
        data[i].second->deleteLater();
    }
    data.clear();
}
