
#include "PluginSample/TestSamplePlugin.h"
#include <iostream>
#include <string>

TestSamplePlugin::TestSamplePlugin (int arg, double stuff)
    : TestPluginType (arg, stuff)
{
	std::cout << "Test sample plugin\n";
	v = "Sample";
}


const std::string& TestSamplePlugin::foo() const
{
	std::cout << v << std::endl;
	return v;
}
