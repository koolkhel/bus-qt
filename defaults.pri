INCLUDEPATH += $$PWD/ $$PWD/src $$PWD/src/nzmqt/include $$PWD/src/nzmqt/3rdparty/cppzmq $$PWD/modules/protos/include
LIBS += -L$$PWD/src/nzmqt/bin -lzmq -lnzmqt -rdynamic -L$$PWD/modules/protos/bin

CONFIG += debug
