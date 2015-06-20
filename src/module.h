#ifndef MODULE_H
#define MODULE_H

#include <QStringList>
#include <QString>
#include <QMap>

#include "indigo_message.pb.h"
#include "modulep.h"
#include "dispatcher.h"

class Dispatcher;

class Module : public QObject
{
    Q_OBJECT

public:
    Module();
    Module(QMap<QString, QVariant>& configuration, QString name);
    Module(QString name);
    virtual ~Module() = 0;

    friend class Dispatcher;

    void configure(QMap<QString, QVariant> &configuration, Dispatcher *d);

    virtual void start();
    virtual void stop();

    virtual QStringList getPubTopics() = 0;

    virtual QString getName() const;

public slots:
    void messageReceived(QList<QByteArray> &data);

    virtual void respond(QString topic, ::indigo::pb::internal_msg &message) = 0;
protected:
    void publish(::google::protobuf::MessageLite &msg, QString topic);
    void subscribe(QString topicName);

    QString name;
private:
    ModuleP *mod_p;
    Dispatcher *dispatcher;

    QMap<QString, QVariant> configuration;
};

#endif // MODULE_H








