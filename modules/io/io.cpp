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
        if(resources[i]->read().toInt()) {
            content |= (1 << i);
        }
    }
    if(content) {
        ::indigo::pb::io_message io;
        io.set_content(content);
        io.set_content_size(resources.size());
        publish(io, "io");
    }
    oldState = content;
}

void IO::doInputJob(uint64_t content)
{
    if(content == oldState)
        return;
    timer.stop();
    for(uint64_t i = 0; i < resources.size(); ++i) {
        char nbit = (content  >> i) & 1;
        char obit = (oldState >> i) & 1;
        if(nbit ^ obit) {
            QByteArray bA;
            bA.append(nbit);
            resources[i]->write(bA);
        }
    }
    timer.start();
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
