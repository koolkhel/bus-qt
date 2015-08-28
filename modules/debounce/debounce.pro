include(../../defaults.pri)

include(../plugins.pri)

TARGET = debounce
TEMPLATE = lib
QT -= gui

SOURCES += debounce.cpp \
    debouncepluginfactory.cpp
LIBS += -L../../src/ -lprotobuf-lite -lindigo -ldebounce_message -lio_message

HEADERS += debounce.h \
    debouncepluginfactory.h

DISTFILES += \
    debounce.json \
    proto/debounce_message.proto
