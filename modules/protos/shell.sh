rm -rf *.proto
find .. -name "*.proto" -exec cp {} . \;

# $1 == куда весь выход пойдет
# $2 == путь к qmake

OUTPUT=$1
mkdir include
mkdir -p $OUTPUT
mkdir include

for i in sender_message.proto *.proto; do
	CLASS=`basename $i .proto`
	DIR=lib
	rm -rf $DIR
	mkdir -p $DIR
	protoc --cpp_out=lib $i || exit 1
	cat template.pro | sed -e "s/CLASS/$CLASS/g" > $DIR/$CLASS.pro
	cd $DIR
	$2
	make || exit 1
	cd ..
	cp -a $DIR/lib* $OUTPUT/
	cp -a $DIR/*.h include/
done
rm -rf *.proto
