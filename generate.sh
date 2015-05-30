export PROTOC="protoc --cpp_out=src/pb"
$PROTOC indigo.proto
$PROTOC geo.proto
$PROTOC events.proto
#/opt/qt/5.4/gcc/bin/rcc --binary -o indigo.qcc indigo.qrc
