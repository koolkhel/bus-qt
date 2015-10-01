#ifndef MODULE_H
#define MODULE_H

#include <QStringList>
#include <QString>
#include <QMap>

#include "sender_message.pb.h"
#include "modulep.h"
#include "dispatcher.h"

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(MODULE)

class Dispatcher;

class Module : public QObject
{
    Q_OBJECT
public:
    Module(QObject *parent = 0);
    Module(QMap<QString, QVariant>& configuration, QString name, QObject *parent = 0);
    Module(QString name);
    virtual ~Module() = 0;
    friend class Dispatcher;
    void configure(QMap<QString, QVariant> &configuration, Dispatcher *d);
    virtual QStringList getPubTopics() = 0;
    virtual QString getName() const;
    virtual QVariant getConfigurationParameter(const QString name, const QVariant &defaultValue) const;
    virtual QMap<QString, QVariant>& getAllConfiguration() { return configuration; }

public slots:
    virtual void start();
    virtual void stop();

    void messageReceived(const QList<QByteArray> &data);
    virtual void respond(QString topic, ::indigo::pb::internal_msg &message) = 0;
protected:
    void publish(::indigo::pb::internal_msg &msg, QString topic);
    void subscribe(QString topicName);
    QString name;
private:
    ModuleP *mod_p;
    Dispatcher *dispatcher;

    QMap<QString, QVariant> configuration;
};

#endif // MODULE_H








