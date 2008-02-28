//<<<<<< INCLUDES                                                       >>>>>>

#include "TestPluginTypeArgs.h"
#include "TestPluginFactoryArgs.h"
#include "Hazel.PluginManager/ModuleDef.h"
#include <iostream>

//<<<<<< PRIVATE DEFINES                                                >>>>>>
//<<<<<< PRIVATE CONSTANTS                                              >>>>>>
//<<<<<< PRIVATE TYPES                                                  >>>>>>
//<<<<<< PRIVATE VARIABLE DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC VARIABLE DEFINITIONS                                    >>>>>>
//<<<<<< CLASS STRUCTURE INITIALIZATION                                 >>>>>>
//<<<<<< PRIVATE FUNCTION DEFINITIONS                                   >>>>>>
//<<<<<< PUBLIC FUNCTION DEFINITIONS                                    >>>>>>
//<<<<<< MEMBER FUNCTION DEFINITIONS                                    >>>>>>

static bool onload (void) {
    std::cout << "factoryargs test library was loaded\n";
    return true;
}

#define RTEST_TYPE(name,proto)					\
class name : public Test##name {  public: name proto ; std::string v; virtual ~name (void); const std::string& foo() const { std::cout << v << std::endl;return v; } }

RTEST_TYPE(PluginType0, (void));
RTEST_TYPE(PluginType1, (int));
RTEST_TYPE(PluginType2, (int, int));
RTEST_TYPE(PluginType3, (int, int, int));
RTEST_TYPE(PluginType4, (int, int, int, int));


#define DEF_RTEST_TYPE( name,v1, proto,proto2,args)				\
	name::~name (void) { std::cout << v << "destructor" << std::endl;}						\
  name::name proto :Test##name proto2 { v= v1; std::cout << args << '\n'; }

DEF_RTEST_TYPE (PluginType0, "Test0", (void),(), "RTest0")
DEF_RTEST_TYPE (PluginType1, "Test1", (int a1),(a1), "RTest0 a1=" << a1)
DEF_RTEST_TYPE (PluginType2, "Test2", (int a1, int a2),(a1,a2), "RTest0 a1=" << a1 << " a2=" << a2)
DEF_RTEST_TYPE (PluginType3, "Test3", (int a1, int a2, int a3), (a1,a2,a3),"RTest0 a1=" << a1 << " a2=" << a2 << " a3=" << a3)
DEF_RTEST_TYPE (PluginType4, "Test4", (int a1, int a2, int a3, int a4), (a1,a2,a3,a4),"RTest0 a1=" << a1 << " a2=" << a2 << " a3=" << a3 << " a4=" << a4)



DEFINE_SEAL_MODULE ();
DEFINE_SEAL_PLUGIN (TestPluginFactoryArgs0, PluginType0, "Sample");
DEFINE_SEAL_PLUGIN (TestPluginFactoryArgs1, PluginType1, "Sample");
DEFINE_SEAL_PLUGIN (TestPluginFactoryArgs2, PluginType2, "Sample");
DEFINE_SEAL_PLUGIN (TestPluginFactoryArgs3, PluginType3, "Sample");
DEFINE_SEAL_PLUGIN (TestPluginFactoryArgs4, PluginType4, "Sample");

static bool autoload = onload ();