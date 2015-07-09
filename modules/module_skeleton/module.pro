include(../../defaults.pri)

include(../plugins.pri)

TARGET = module
TEMPLATE = lib
QT -= gui

SOURCES += module.cpp \
    modulepluginfactory.cpp
LIBS += -L../../src/ -lprotobuf-lite -lindigo -lmodule_message 

HEADERS += module.h \
    modulepluginfactory.h

DISTFILES += \
    module.json \
    proto/module_message.proto
