//<<<<<< INCLUDES                                                       >>>>>>

#include "TestPluginType.h"
#include "TestPluginFactory.h"
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
    std::cout << "factory test library was loaded\n";
    return true;
}

class PluginType : public TestPluginType
{
public:
    PluginType (int arg, double stuff)
		: TestPluginType( arg, stuff )
{
	v = "PluginType";
	std::cout << "Test PluginType arg=" << arg << ", stuff=" << stuff << std::endl; 
}
    virtual ~PluginType (void)
	{
		std::cout << v << " destructor" << std::endl; 
	}
	virtual const std::string& foo() const
	{
		std::cout << v << std::endl;
		return v;
	}

	std::string v;
};


DEFINE_SEAL_MODULE ();
DEFINE_SEAL_PLUGIN (TestPluginFactory, PluginType, "PluginType");

static bool autoload = onload ();
