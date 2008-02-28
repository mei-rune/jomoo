//<<<<<< INCLUDES                                                       >>>>>>

#include "PluginSample/TestSamplePlugin.h"
#include "PluginFactory/TestPluginFactory.h"
#include "Hazel.PluginManager/ModuleDef.h"


DEFINE_SEAL_MODULE ();
DEFINE_SEAL_PLUGIN (TestPluginFactory, TestSamplePlugin, "Sample");
