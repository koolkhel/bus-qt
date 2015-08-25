#ifndef OUTGOINGMESSAGE_H
#define OUTGOINGMESSAGE_H

#include <QObject>
#include <QVector>

#include "sender_message.pb.h"

class OutgoingMessage : public QObject
{
    Q_OBJECT
public:
    explicit OutgoingMessage(QObject *parent = 0);

    void consumeSample(QString topic, ::indigo::pb::internal_msg &sample);

    ::indigo::pb::indigo_msg& msg() { return _msg; }
    QVector<int>& sampleIds() { return _iHaveTheseIds; }
    int id() { return _myId; }
    void setId(int id) { _myId = id; _msg.set_id(id); }

signals:

public slots:
private:
    int _myId;
    QVector<int> _iHaveTheseIds;
    ::indigo::pb::indigo_msg _msg;
};

#endif // OUTGOINGMESSAGE_H
