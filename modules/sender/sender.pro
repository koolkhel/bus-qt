include(../../defaults.pri)

include(../plugins.pri)

TARGET = sender
TEMPLATE = lib
QT -= gui
QT += network

SOURCES += sender.cpp \
    senderpluginfactory.cpp \
    protobufnegotiator.cpp \
    outgoingmessage.cpp \
    indigoqueue.cpp
LIBS += -L../../src/ -lprotobuf-lite -lindigo -lsender_message -lblackbox_message

HEADERS += sender.h \
    senderpluginfactory.h \
    protobufnegotiator.h \
    outgoingmessage.h \
    indigoqueue.h

DISTFILES += \
    sender.json \
    proto/sender_message.proto
