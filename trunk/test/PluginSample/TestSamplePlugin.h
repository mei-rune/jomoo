#ifndef PLUGIN_MANAGER_TEST_SAMPLE_PLUGIN_H
# define PLUGIN_MANAGER_TEST_SAMPLE_PLUGIN_H

# include "PluginFactory/TestPluginType.h"


class TestSamplePlugin : public TestPluginType
{
public:
    TestSamplePlugin (int arg, double stuff);
	virtual const std::string& foo() const;
	~TestSamplePlugin()
	{
	std::cout << v << "destructor" << std::endl;
	}
	
	std::string v;
};

#endif // PLUGIN_MANAGER_TEST_SAMPLE_PLUGIN_H
