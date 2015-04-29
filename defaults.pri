INCLUDEPATH += $$PWD/src $$PWD/src/nzmqt/include $$PWD/src/nzmqt/3rdparty/cppzmq
LIBS += -L$$PWD/src/nzmqt/bin -lzmq -lnzmqt -rdynamic

CONFIG += debug
