files="module.cpp module.h module.pro module.json modulepluginfactory.cpp modulepluginfactory.h proto/module_message.proto"
TARGET=$1
TARGET_CAPS=`echo $TARGET | tr a-z A-Z`
SOURCE=module_skeleton

mkdir -p $TARGET/proto
cp -a $SOURCE/qmake $TARGET/qmake

for oldname in $files; do
	newname=`echo $oldname | sed -e "s/module/$TARGET/g"`

	if [ $oldname == "module.h" ]; then
		cat $SOURCE/$oldname | sed -e "s/module/$TARGET/g" | sed -e "s/MODULE/$TARGET_CAPS/g" | sed -e "s/\#include \"$TARGET.h\"/\#include \"module.h\"/g" > $TARGET/$newname
	elif [ $oldname == "modulepluginfactory.h" ]; then
		cat $SOURCE/$oldname | sed -e "s/module/$TARGET/g" | sed -e "s/MODULE/$TARGET_CAPS/g" | sed -e "s/\#include \"plugin${TARGET}factory.h\"/\#include \"pluginmodulefactory.h\"/g" > $TARGET/$newname
	else
		cat $SOURCE/$oldname | sed -e "s/module/$TARGET/g" | sed -e "s/MODULE/$TARGET_CAPS/g" > $TARGET/$newname
	fi
done
