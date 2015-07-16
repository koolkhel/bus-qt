include(../../defaults.pri)

include(../plugins.pri)

TARGET = io
TEMPLATE = lib
QT -= gui

SOURCES += io.cpp \
    iopluginfactory.cpp \
    resource.cpp
LIBS += -L../../src/ -lprotobuf-lite -lindigo -lio_message 

HEADERS += io.h \
    iopluginfactory.h \
    resource.h

DISTFILES += \
    io.json \
    proto/io_message.proto
