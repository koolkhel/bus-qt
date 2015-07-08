#include <gtest/gtest.h>

#include "indigologger.h"
#include <QtNetwork/QTcpSocket>

#include <QDebug>
#include <QTest>
#include <QSignalSpy>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/text_format.h>

#include "events_message.pb.h"
#include "geo_message.pb.h"
#include "sender_message.pb.h"

TEST(protobuf, workWithExtensions) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    ::indigo::pb::indigo_msg message;
    ::indigo::pb::indigo_geo geo;
    ::indigo::pb::indigo_event myevent;

    geo.set_latitude(5.0);
    geo.set_longitude(6.0);
    geo.set_unixtime(555);

    // код расширения берется из расширяющего класса. В нем записано название
    // поля из основного класса
    message.AddExtension(::indigo::pb::indigo_geo::geo_coords)->CopyFrom(geo);
    ASSERT_TRUE(message.HasExtension(::indigo::pb::indigo_geo::geo_coords))
            << "Geo coord extension failed to add";

    myevent.set_type(::indigo::pb::EVENT_NOTHING);
    myevent.set_time(666);
    message.AddExtension(::indigo::pb::indigo_event::events)->CopyFrom(myevent);
    ASSERT_TRUE(message.HasExtension(::indigo::pb::indigo_event::events))
            << "Events extension failed to add";

    message.mutable_device_id()->set_least_significant_bits(5);
    message.mutable_device_id()->set_most_significant_bits(7);

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    bool result = false;
    int byte_size = message.ByteSize();
    result = message.SerializeToArray(buffer, sizeof(buffer));
    ASSERT_TRUE(result)
            << "unable to successfully serialize indigo_msg object";

    ::indigo::pb::indigo_msg message2;

    // здесь принципиально важно парсить столько, сколько ожидается длина сообщения
    // TRUE будет только если мы закончили разбор сообщения четко по границе входного буфера
    result = message2.ParseFromArray(buffer, byte_size);

    // Печаль, но почему-то нельзя понять, распарсили мы что-то или нет
    ASSERT_TRUE(result) << ".ParseFromArray() returned false. Perhaps. wrong message border";

    // проверка того, что установлены required поля
    ASSERT_TRUE(message2.IsInitialized())
            << "message not initialized; not enough required fields";

    ASSERT_EQ(message2.device_id().least_significant_bits(), 5)
            << "parsed data differs from sent data";
    ASSERT_EQ(message2.device_id().most_significant_bits(), 7)
            << "parsed data differs from sent data";;

    ASSERT_TRUE(message2.HasExtension(::indigo::pb::indigo_geo::geo_coords))
            << "Geo coord extension failed to parse after serialization";

    ::indigo::pb::indigo_geo geo2;
    geo2.CopyFrom(message2.GetRepeatedExtension(::indigo::pb::indigo_geo::geo_coords).Get(0));

    ASSERT_EQ(geo2.latitude(), 5.0)
            << "Wrong received latitude";
    ASSERT_EQ(geo2.longitude(), 6.0)
            << "Wrong received longitude";
    ASSERT_EQ(geo2.unixtime(), 555)
            << "Wrong received unixtime";

    ASSERT_TRUE(message2.HasExtension(::indigo::pb::indigo_event::events))
            << "Events extension failed to parse after serialization";
    ::indigo::pb::indigo_event event2;
    event2.CopyFrom(message2.GetRepeatedExtension(::indigo::pb::indigo_event::events).Get(0));

    ASSERT_EQ(event2.type(), ::indigo::pb::EVENT_NOTHING)
            << "Incorrect parsed event type";
    ASSERT_EQ(event2.time(), 666)
            << "Incorrect parsed event time";
}

TEST(protobuf, setBinarySubmessage) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    ::indigo::pb::indigo_msg message;
    ::indigo::pb::indigo_geo geo;
    ::indigo::pb::indigo_event myevent;

    geo.set_latitude(5.0);
    geo.set_longitude(6.0);
    geo.set_unixtime(555);

    // TODO проверить
}
