#include "outgoingmessage.h"
#include "sender.h"

#include "geo_message.pb.h"

OutgoingMessage::OutgoingMessage(QObject *parent) : QObject(parent)
{
    _msg.Clear();
}

void OutgoingMessage::consumeSample(QString topic, indigo::pb::internal_msg &sample)
{
    bool consumed = false;
    if (sample.HasExtension(::indigo::pb::indigo_geo::geo_coords_in)) {
        qCDebug(SENDERC) << "consuming geo message id " << sample.id();
        ::indigo::pb::indigo_geo geo = sample.GetExtension(::indigo::pb::indigo_geo::geo_coords_in);
        ::indigo::pb::indigo_geo *geo2 = _msg.AddExtension(::indigo::pb::indigo_geo::geo_coords);
        geo2->CopyFrom(geo);

        consumed = true;
    }

    if (consumed) {
        _iHaveTheseIds.append(sample.id());
    }
}
