#include "indigologger.h"

#include <QByteArray>
#include <QDebug>
#include <QDateTime>

#include <QThread>

IndigoLogger *IndigoLogger::instance;

IndigoLogger::IndigoLogger()
{
    socket = new QUdpSocket();
   // socket->bind(QHostAddress::LocalHost, IndigoLogger::PORT,
   //              QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);

    instance = this;
}

QString IndigoLogger::getLevelTag(int logLevel) {
    switch (logLevel) {
    case DEBUG:
        return "[DEBUG] ";
        break;
    case ERROR:
        return "[ERROR] ";
        break;
    }

    return "";
}


void IndigoLogger::log(int logLevel, QString str)
{
    //qDebug() << "outputting " << str;
    QDateTime timestamp = QDateTime::currentDateTime();
    QByteArray qba = QString("%1 [t: %2] %3 %4\n")
            .arg(getLevelTag(logLevel))
            .arg(QThread::currentThreadId())
            .arg(timestamp.toString(Qt::ISODate))
            .arg(str)
            .toLocal8Bit();

    socket->writeDatagram(qba.data(), qba.size(), QHostAddress::Broadcast, IndigoLogger::PORT);
}
