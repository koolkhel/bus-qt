include(../../defaults.pri)

include(../plugins.pri)

TARGET = stops
TEMPLATE = lib
QT -= gui

SOURCES += stops.cpp \
    stopspluginfactory.cpp
LIBS += -L../../src/ -lprotobuf-lite -lindigo -lstops_message -lgpsmodule_message


HEADERS += stops.h \
    stopspluginfactory.h

DISTFILES += \
    stops.json \
    proto/stops_message.proto
