
#include "PluginInit/TestInitPlugin.h"
#include "PluginFactory/TestPluginFactory.h"
#include "Hazel.PluginManager/ModuleDef.h"

DEFINE_SEAL_MODULE ();
DEFINE_SEAL_PLUGIN (TestPluginFactory, TestInitPlugin, "Init");
