#include "io.h"

Q_LOGGING_CATEGORY(IOC, "io")

using namespace indigo::pb;

IO::IO(QObject *parent)
{
    setParent(parent);

    this->name = "io works";

    resource = NULL;

    timer.setSingleShot(false);
    timer.setInterval(100);

    connect(&timer, SIGNAL(timeout()), this, SLOT(doInputJob()));

    qCDebug(IOC, "hello,world");
}

IO::~IO()
{
    stop();
}

QStringList IO::getPubTopics()
{
    QStringList topics;

    topics << inputTopic << outputTopic;

    return topics;
}

void IO::respond(QString topic, internal_msg &message)
{
}

void IO::doInputJob()
{
    internal_msg ioMessage;
    io_message *io = ioMessage.MutableExtension(io_message::io_message_in);
    io->set_content(resource->read());
    io->set_io_id(id);
    publish(ioMessage, outputTopic);
}

void IO::doOutputJob(uint64_t content)
{
    timer.stop();
    resource->write(content);
    timer.start();
}


void IO::start()
{
    stop();

    QString device = getConfigurationParameter("device", "").toString();
    inputTopic     = getConfigurationParameter("inputTopic", "io_in").toString();
    outputTopic    = getConfigurationParameter("outputTopic", "io_out").toString();
    id             = static_cast< io_message_IO_id > (getConfigurationParameter("id", 0).toInt());
    int timeout    = getConfigurationParameter("timeout", 100).toInt();

    if(device == "") {
        qCWarning(IOC) << "empty device!";
    }

    if(id == io_message_IO_id_DEFAULT) {
        qCWarning(IOC) << "default id";
    }

    subscribe(inputTopic);

    resource = new Resource(device);

    timer.setInterval(timeout);
    timer.start();
}

void IO::stop()
{
    if(resource != NULL) {
        delete resource;
        resource = NULL;
    }
}
