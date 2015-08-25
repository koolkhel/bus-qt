rm -rf *.proto
find .. -name "*.proto" -exec cp {} . \;

OUTPUT=bin
mkdir include
mkdir -p $OUTPUT

for i in sender_message.proto *.proto; do
	CLASS=`basename $i .proto`
	DIR=lib
	rm -rf $DIR
	mkdir -p $DIR
	protoc --cpp_out=lib $i || exit 1
	cat template.pro | sed -e "s/CLASS/$CLASS/g" > $DIR/$CLASS.pro
	cd $DIR
	../qmake
	make || exit 1
	cd ..
	cp -a $DIR/lib* $OUTPUT/
	cp -a $DIR/*.h include/
done
rm -rf *.proto
