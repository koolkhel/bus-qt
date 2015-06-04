#include <gtest/gtest.h>

#include "indigologger.h"
#include "loggertester.h"
#include <QtNetwork/QTcpSocket>

#include <QDebug>
#include <QTest>
#include <QSignalSpy>

#include <QPluginLoader>
#include <QJsonObject>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/text_format.h>

#include "events.pb.h"
#include "geo.pb.h"
#include "indigo.pb.h"

#include "module.h"
#include "pluginmodulefactory.h"

TEST(PLUGINS, test)
{
    QPluginLoader loader("../modules/bin/libskel.so");
    QJsonObject metadata = loader.metaData();
    printf("%s\n", qPrintable(metadata.keys().join(",")));
    printf("%s\n", qPrintable(metadata.value("IID").toString()));

    bool result = loader.load();
    ASSERT_TRUE(result);
    //printf("%s\n", qPrintable(loader.errorString()));

    QObject *obj = loader.instance();
    ASSERT_TRUE(obj != NULL);

    PluginModuleFactory *factory = qobject_cast<PluginModuleFactory *>(obj);
    Module *module = factory->createModule();
    ASSERT_TRUE(module->name() == "skel works");
}
