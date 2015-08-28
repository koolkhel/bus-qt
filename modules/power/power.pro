include(../../defaults.pri)

include(../plugins.pri)

TARGET = power
TEMPLATE = lib
QT -= gui

SOURCES += power.cpp \
    powerpluginfactory.cpp
LIBS += -L../../src/ -lprotobuf-lite -lindigo -lpower_message -lio_message

HEADERS += power.h \
    powerpluginfactory.h

DISTFILES += \
    power.json \
    proto/power_message.proto
