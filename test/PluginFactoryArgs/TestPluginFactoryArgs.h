#ifndef PLUGIN_MANAGER_TEST_PLUGIN_FACTORY_ARGS_H
# define PLUGIN_MANAGER_TEST_PLUGIN_FACTORY_ARGS_H

# include "../PluginFactoryArgs/TestPluginTypeArgs.h"
# include "Hazel.PluginManager/PluginFactory.h"
# include "Base/Singleton.h"
# include "Base/Threading/Threading.h"


#define TEST_FACTORY(fname,proto, name ,version )			\
  class fname : public _seal PluginFactory<proto> {	\
  public: static fname &get (void){ return Hazel_Singleton< fname, Hazel_Mutex >::get(); }			\
  private: fname (void): _seal PluginFactory<proto> ( _seal getPluginManager(),name, version ) {}	\
  friend class Hazel_Singleton< fname, Hazel_Mutex >; }

//TEST_FACTORY (TestPluginFactoryArgsV, void);
TEST_FACTORY (TestPluginFactoryArgs0, TestPluginType0 *(void), "Test0" , "1");
TEST_FACTORY (TestPluginFactoryArgs1, TestPluginType1 *(int), "Test1","1");
TEST_FACTORY (TestPluginFactoryArgs2, TestPluginType2 *(int, int), "Test2" ,"1");
TEST_FACTORY (TestPluginFactoryArgs3, TestPluginType3 *(int, int, int), "Test3","1");
TEST_FACTORY (TestPluginFactoryArgs4, TestPluginType4 *(int, int, int, int), "Test4","1");

#endif // PLUGIN_MANAGER_TEST_PLUGIN_FACTORY_ARGS_H
