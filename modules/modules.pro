TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += skel test UI gpsmodule blackbox \
	debounce io power sender logs sendlog \
	stops

!build_pass:system(cd protos && ./shell.sh && cd ..)
