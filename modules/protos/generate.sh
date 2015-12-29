rm -rf *.proto
find .. -name "*.proto" -exec cp {} . \;

mkdir include

for i in sender_message.proto *.proto; do
	CLASS=`basename $i .proto`
	DIR=pb-$CLASS
	rm -rf $DIR
	mkdir -p $DIR
	protoc --cpp_out=$DIR/ $i || exit 1
	cat template.pro | sed -e "s/CLASS/$CLASS/g" > $DIR/$CLASS.pro
	cd $DIR
	make || exit 1
	cd ..
done
rm -rf *.proto
