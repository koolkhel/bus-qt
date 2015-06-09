#include "module.h"

Module::Module()
{
    this->name = "";
}

Module::Module(QMap<QString, QVariant>& configuration, QString name)
{
    this->configuration = configuration;
    this->name = name;
}

Module::Module(QString name)
{
    this->name = name;
}

Module::~Module()
{

}

void Module::configure(QMap<QString, QVariant> &configuration, Dispatcher *d)
{
    this->configuration = configuration;
    dispatcher = d;
}

void Module::start()
{

}

void Module::stop()
{

}

void Module::publish()
{

}

void Module::subscribe(QString topicName)
{
    d->subscribe(this, topicName);
}

void Module::messageReceived(QList<QByteArray> &data)
{
    // assert data.size() > 0
    ::indigo::pb::internal_msg msg;

    QByteArray messageBytes = data.at(0);
    msg.ParseFromArray(messageBytes.data(), messageBytes.size());

    respond(msg);
}
