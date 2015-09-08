include(paths.pri)

INCLUDEPATH += $$PRJ_PATH/ $$PRJ_PATH/src $$PRJ_PATH/src/nzmqt/include $$PRJ_PATH/src/nzmqt/3rdparty/cppzmq $$PRJ_PATH/modules/protos/include
LIBS += -lzmq -rdynamic -L$$PROTODIR

CONFIG += debug

DISTFILES += \
    $$PWD/paths.pri
