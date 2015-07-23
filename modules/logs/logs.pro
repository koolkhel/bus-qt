include(../../defaults.pri)

include(../plugins.pri)

TARGET = logs
TEMPLATE = lib
QT -= gui

SOURCES += logs.cpp \
    logspluginfactory.cpp
LIBS += -L../../src/ -lprotobuf-lite -lindigo -llogs_message 

HEADERS += logs.h \
    logspluginfactory.h

DISTFILES += \
    logs.json \
    proto/logs_message.proto
