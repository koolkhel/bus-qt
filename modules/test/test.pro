include(../../defaults.pri)

include(../plugins.pri)

TARGET = test
TEMPLATE = lib

QT -= gui

SOURCES += test.cpp \
    testpluginfactory.cpp

HEADERS += test.h \
    testpluginfactory.h

DISTFILES += \
    test.json \
    proto/test_message.proto
