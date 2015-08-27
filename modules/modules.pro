TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += skel test UI gpsmodule blackbox sender logs sendlog
QMAKE_EXTRA_TARGETS += customtarget1

# цель
customtarget1.target = readme.txt

# команда - создание файла в каталоге исходников
# без $$PWD файл создасться в $$OUT_PWD
customtarget1.commands = "echo 321 > readme.txt"

