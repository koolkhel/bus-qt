include(../../defaults.pri)

include(../plugins.pri)

TARGET = sendlog
TEMPLATE = lib
QT -= gui
QT += network

SOURCES += sendlog.cpp \
    sendlogpluginfactory.cpp
LIBS += -L../../src/ -lprotobuf-lite -lindigo -lsendlog_message 

HEADERS += sendlog.h \
    sendlogpluginfactory.h

DISTFILES += \
    sendlog.json \
    proto/sendlog_message.proto
