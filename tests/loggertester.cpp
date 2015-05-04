#include "loggertester.h"

#include "indigologger.h"

#include <QDebug>

LoggerTester::LoggerTester(QObject *parent) : QObject(parent)
{
    loggerSocket = new QUdpSocket(this);
    loggerSocket->bind(IndigoLogger::PORT, QUdpSocket::ShareAddress);

    lastMessage = "NOTHING";

    connect(loggerSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void LoggerTester::wait()
{
    loggerSocket->waitForReadyRead(500000);
}

void LoggerTester::readyRead()
{
    while (loggerSocket->hasPendingDatagrams()) {
        QByteArray qba;
        qba.resize(loggerSocket->pendingDatagramSize());
        loggerSocket->readDatagram(qba.data(), qba.size());
        QString message = QString::fromLocal8Bit(qba);
        lastMessage = message;
        qDebug() << message;
    }
}

