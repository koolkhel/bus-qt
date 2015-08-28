#ifndef REMOTEPROCESS_H
#define REMOTEPROCESS_H

#include <QString>
#include <QStringList>
#include <QProcess>

struct RemoteProcess
{
    QString path;
    QStringList StartParams;
    QStringList StopParams;
    bool state;
    QProcess process;
    bool disabled;
    
    bool start();
    bool stop();
    QString getOutput();
};

#endif // REMOTEPROCESS_H
