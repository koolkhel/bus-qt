include(../../defaults.pri)

include(../plugins.pri)

TARGET = skel
TEMPLATE = lib
QT -= gui

SOURCES += skel.cpp \
    skelpluginfactory.cpp
LIBS += -L../../src/ -lprotobuf-lite -lindigo -ltest_message -lskel_message -lskel_message2

HEADERS += skel.h \
    skelpluginfactory.h

DISTFILES += \
    skel.json
