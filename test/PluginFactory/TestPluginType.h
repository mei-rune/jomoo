#ifndef PLUGIN_MANAGER_TEST_PLUGIN_H
# define PLUGIN_MANAGER_TEST_PLUGIN_H

//<<<<<< INCLUDES                                                       >>>>>>

#include <iostream>
#include <iomanip>
#include <string>

class TestPluginType
{
public:
    TestPluginType (int arg, double stuff)
{ std::cout << "Test plugin arg=" << arg << ", stuff=" << stuff << std::endl; }
    virtual ~TestPluginType (void){}
	virtual const std::string& foo() const = 0;
};

//<<<<<< INLINE PUBLIC FUNCTIONS                                        >>>>>>
//<<<<<< INLINE MEMBER FUNCTIONS                                        >>>>>>

#endif // PLUGIN_MANAGER_TEST_PLUGIN_H
