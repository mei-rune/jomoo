#ifndef PLUGIN_INIT_TEST_INIT_PLUGIN_H
# define PLUGIN_INIT_TEST_INIT_PLUGIN_H


# include "PluginFactory/TestPluginType.h"


class TestInitPlugin : public TestPluginType
{
public:
    TestInitPlugin (int arg, double stuff);
	~TestInitPlugin()
	{

	std::cout << v << "destructor" << std::endl;
}
    // implicit copy constructor
    // implicit assignment operator
    // implicit destructor

	virtual const std::string& foo() const;
	std::string v;
};

#endif // PLUGIN_INIT_TEST_INIT_PLUGIN_H
