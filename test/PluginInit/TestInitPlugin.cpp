//<<<<<< INCLUDES                                                       >>>>>>

#include "PluginInit/TestInitPlugin.h"
#include <iostream>
#include <string>



static std::string foo_ ("foo");
TestInitPlugin::TestInitPlugin (int arg, double stuff)
    : TestPluginType (arg, stuff)
{
	std::cout << "Test init plugin: " << foo_ << "\n";
	v = "Init";
}

//void TestInitPlugin::foo()
//{
//
//	std::cout << "TestInitPlugin" << std::endl;
//}


const std::string& TestInitPlugin::foo() const
{
	std::cout << v << std::endl;
	return v;
}
