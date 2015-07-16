#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include <QFile>

class Resource : public QObject
{
    Q_OBJECT
public:
    explicit Resource(QString name, QObject *parent = 0);
    void setName(QString name);

    void write(QByteArray);
signals:
    void DataReady(QByteArray);
public slots:
    QByteArray read();
private:
    QString resourceName;
    QFile file;
    void open();
};

#endif // RESOURCE_H
