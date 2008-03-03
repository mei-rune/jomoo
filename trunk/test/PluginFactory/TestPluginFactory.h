#ifndef PLUGIN_MANAGER_TEST_PLUGIN_FACTORY_H
# define PLUGIN_MANAGER_TEST_PLUGIN_FACTORY_H

//<<<<<< INCLUDES                                                       >>>>>>

# include "../PluginFactory/TestPluginType.h"
# include "Hazel.PluginManager/PluginFactory.h"
# include "Base/Singleton.h"
# include "Base/Threading/Threading.h"

//<<<<<< PUBLIC DEFINES                                                 >>>>>>
//<<<<<< PUBLIC CONSTANTS                                               >>>>>>
//<<<<<< PUBLIC TYPES                                                   >>>>>>
//<<<<<< PUBLIC VARIABLES                                               >>>>>>
//<<<<<< PUBLIC FUNCTIONS                                               >>>>>>
//<<<<<< CLASS DECLARATIONS                                             >>>>>>

class TestPluginFactory : public _seal PluginFactory<TestPluginType *(int, double)>
{
public:
	static TestPluginFactory& get (void)
	{
		return Hazel_Singleton< TestPluginFactory , Threading::MUTEX >::get();
	}
private:

	friend class Hazel_Singleton< TestPluginFactory , Threading::MUTEX >;

	TestPluginFactory ( /*IPluginManager& manager*/ )    : _seal PluginFactory<TestPluginType *(int, double)> ( _seal getPluginManager(), "Test","2")
	{}
};



//<<<<<< INLINE PUBLIC FUNCTIONS                                        >>>>>>
//<<<<<< INLINE MEMBER FUNCTIONS                                        >>>>>>

#endif // PLUGIN_MANAGER_TEST_PLUGIN_FACTORY_H
