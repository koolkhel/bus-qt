#include "remoteprocess.h"
#include <QDebug>
bool RemoteProcess::start() {
    if(disabled) {
        return false;
    }
    if(!state) {
        process.start(path, StartParams);
    }
    state = true;
    return process.waitForStarted(2*1000);
}

bool RemoteProcess::stop() {
    if(disabled) {
        return false;
    }
    
    if(state) {
        process.start(path, StopParams);

    }
    state = false;

    return process.waitForStarted(2*1000);
}

QString RemoteProcess::getOutput()
{
    return process.readAll();
}
