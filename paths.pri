PRJ_PATH=/home/yury/work/QTFinal

linux-g++ {
    P=$$PRJ_PATH/linux-x86
}

linux-arm-indigo-g++ {
    P=$$PRJ_PATH/linux-arm
}

BUILDDIR=$$P/build
BINDIR=$$P/bin
MODDIR=$$P/modules/bin
PROTODIR=$$P/modules/protos/bin
MODROOTDIR=$$P/modules/

UI_DIR=$$BUILDDIR
MOC_DIR=$$BUILDDIR
RCC_DIR=$$P/modules/resources
OBJECTS_DIR=$$BUILDDIR
