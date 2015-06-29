#include "module.h"

#include <QDebug>

Q_LOGGING_CATEGORY(MODULE, "module")

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

void Module::publish(::google::protobuf::MessageLite &msg, QString topic)
{
    qCDebug(MODULE) << "publishing to topic: " << topic;
    QByteArray result = QByteArray::fromStdString(msg.SerializeAsString());
    dispatcher->publish(mod_p, result, topic);
}

void Module::subscribe(QString topicName)
{
    dispatcher->subscribe(this, topicName);
}

QString Module::getName() const
{
    return name;
}


void Module::messageReceived(const QList<QByteArray> &data)
{
    ::indigo::pb::internal_msg msg;

    QByteArray messageBytes = data.at(1);
    QString topic = QString::fromLocal8Bit(data.at(0));
    msg.ParseFromArray(messageBytes.data(), messageBytes.size());


    qCDebug(MODULE) << "data received, topic: " << topic;

    respond(topic, msg);
}

QVariant Module::getConfigurationParameter(const QString name, const QVariant &defaultValue = QVariant()) const
{
    return configuration.value(name, defaultValue);
}
