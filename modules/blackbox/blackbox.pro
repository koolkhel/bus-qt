include(../../defaults.pri)

include(../plugins.pri)

TARGET = blackbox
TEMPLATE = lib
QT -= gui

SOURCES += blackbox.cpp \
    blackboxpluginfactory.cpp
LIBS += -L../../src/ -lprotobuf-lite -lindigo -lblackbox_message 

HEADERS += blackbox.h \
    blackboxpluginfactory.h

DISTFILES += \
    blackbox.json \
    proto/blackbox_message.proto
