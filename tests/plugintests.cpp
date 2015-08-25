#include <gtest/gtest.h>

#include "indigologger.h"
#include <QtNetwork/QTcpSocket>

#include <QDebug>
#include <QTest>
#include <QSignalSpy>

#include <QPluginLoader>
#include <QJsonObject>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/text_format.h>

#include "events_message.pb.h"
#include "geo_message.pb.h"
#include "sender_message.pb.h"

#include "module.h"
#include "pluginmodulefactory.h"

TEST(PLUGINS, skel)
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
    ASSERT_TRUE(module->getName() == "skel works");
}

TEST(PLUGINS, test_module)
{
    QPluginLoader loader("../modules/bin/libtest.so");
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

    QString moduleName = module->getName();
    ASSERT_STREQ(qPrintable(moduleName), "test_instance");
}

TEST(PLUGINS, ui_module)
{
    QPluginLoader loader("../modules/bin/libUI.so");
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

    QString moduleName = module->getName();
    ASSERT_STREQ(qPrintable(moduleName), "ui_instance");
}
