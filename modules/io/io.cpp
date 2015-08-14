#include "io.h"
#include <QTime>
Q_LOGGING_CATEGORY(IOC, "io")

using namespace indigo::pb;

IO::IO(QObject *parent)
{
    setParent(parent);

    previousState = 2;

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
    qint32 currentState = resource->read();
    if(currentState != previousState) {
        previousState = currentState;
        internal_msg ioMessage;
        io_message *io = ioMessage.MutableExtension(io_message::io_message_in);
        if(invert) {
            currentState = (currentState == 1) ? 0 : 1;
        }
        io->set_value(currentState);
        io->set_io_id(id);
        io->set_epoch(QTime::currentTime().second());
        publish(ioMessage, outputTopic);
    }
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
    outputTopic   = getConfigurationParameter("outputTopic", "io_out").toString();
    id                      = static_cast< io_message_IO_id > (getConfigurationParameter("id", 0).toInt());
    int timeout    = getConfigurationParameter("timeout", 100).toInt();
    invert             = getConfigurationParameter("invert", false).toBool();

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
