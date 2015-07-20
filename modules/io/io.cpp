#include "io.h"
#include "io_message.pb.h"

#include "resource.h"

Q_LOGGING_CATEGORY(IOC, "io")

IO::IO(QObject *parent)
{
    setParent(parent);

    this->name = "io works";

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
    uint64_t content = 0ll;
    for(int i = 0; i < resources.size(); ++i) {
    }
    ::indigo::pb::io_message io;
    io.set_content(content);
    io.set_content_size(resources.size());
}


void IO::start()
{
    stop();

    QStringList devices = getConfigurationParameter("devices", "").toString().split(",");

    resources.reserve(devices.size());

    for(int i = 0; i < devices.size(); ++i) {
        resources.push_back(
                   QSharedPointer<Resource>(
                        new Resource(devices.at(i))));
    }

    timer.start();
}

void IO::stop()
{
    resources.clear();
}
