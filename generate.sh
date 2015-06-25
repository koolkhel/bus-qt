export PROTOC="protoc --cpp_out=src/pb"
$PROTOC indigo.proto
$PROTOC geo.proto
$PROTOC events.proto
$PROTOC ui.proto
#/opt/qt/5.4/gcc/bin/rcc --binary -o indigo.qcc indigo.qrc
