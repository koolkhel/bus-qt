#include "io.h"
#include "io_message.pb.h"

#include "resource.h"

Q_LOGGING_CATEGORY(IOC, "io")

IO::IO(QObject *parent)
{
    setParent(parent);

    this->name = "io works";

    resource = NULL;

    timer.setSingleShot(false);
    timer.setInterval(100);

    connect(&timer, SIGNAL(timeout()), this, SLOT(doOutputJob()));

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

void IO::doOutputJob()
{
    ::indigo::pb::internal_msg ioMessage;
    ::indigo::pb::io_message *io = ioMessage.MutableExtension(::indigo::pb::io_message::io_message_in);
    io->set_content(resource->read());
    publish(ioMessage, id);
}

void IO::doInputJob(uint64_t content)
{
    timer.stop();
    resource->write(content);
    timer.start();
}


void IO::start()
{
    stop();

    QString device = getConfigurationParameter("device", "").toString();
    id = "io" + getConfigurationParameter("id", "").toString();
    int timeout    = getConfigurationParameter("timeout", 100).toInt();
    if(resource != NULL) {
        stop();
    }
    if(device == "") {
        qCDebug(IOC) << "empty device!";
    }

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
