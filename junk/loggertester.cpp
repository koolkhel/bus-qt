#include "loggertester.h"

#include "indigologger.h"

#include <QtNetwork/QTcpSocket>
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
        //printf(qPrintable(message));
    }
}

void LoggerTester::putConf(QString conf)
{
    QTcpSocket *socket = new QTcpSocket();
    socket->connectToHost(QHostAddress::LocalHost, IndigoLogger::CONF_PORT);
    socket->waitForConnected(500000);
    if (!socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "bad bad";
        return;
    }

    socket->write((conf + "\n").toLocal8Bit());
    socket->flush();
    socket->waitForBytesWritten(500000);
    socket->close();
    socket->waitForDisconnected(500000);

}
