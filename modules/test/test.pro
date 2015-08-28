include(../../defaults.pri)

include(../plugins.pri)

TARGET = test
TEMPLATE = lib

QT -= gui

LIBS += -L../protos/bin -ltest_message -lskel_message -lio_message

SOURCES += test.cpp \
    testpluginfactory.cpp

HEADERS += test.h \
    testpluginfactory.h

DISTFILES += \
    test.json \
    proto/test_message.proto
