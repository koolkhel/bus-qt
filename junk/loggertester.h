#ifndef LOGGERTESTER_H
#define LOGGERTESTER_H

#include <QObject>
#include <QString>

#include <QtNetwork/QUdpSocket>

class LoggerTester : public QObject
{
    Q_OBJECT
public:
    explicit LoggerTester(QObject *parent = 0);
    void wait();
    void putConf(QString conf);
    QString lastMessage;
signals:

public slots:
    void readyRead();
private:
    QUdpSocket *loggerSocket;
};

#endif // LOGGERTESTER_H
