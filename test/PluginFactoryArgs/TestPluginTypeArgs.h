#ifndef PLUGIN_MANAGER_TEST_PLUGIN_TYPE_ARGS_H
# define PLUGIN_MANAGER_TEST_PLUGIN_TYPE_ARGS_H


#include <iostream>

#define TEST_TYPE(name,proto)					\
class name { public: name proto ; virtual ~name (void);virtual const std::string& foo() const = 0; }

TEST_TYPE(TestPluginType0, (void));
TEST_TYPE(TestPluginType1, (int));
TEST_TYPE(TestPluginType2, (int, int));
TEST_TYPE(TestPluginType3, (int, int, int));
TEST_TYPE(TestPluginType4, (int, int, int, int));


#define DEF_TEST_TYPE(name,proto,args)				\
  name::~name (void) {}						\
  name::name proto { std::cout << args << '\n'; }

DEF_TEST_TYPE (TestPluginType0, (void), "Test0")
DEF_TEST_TYPE (TestPluginType1, (int a1), "Test1 a1=" << a1)
DEF_TEST_TYPE (TestPluginType2, (int a1, int a2), "Test2 a1=" << a1 << " a2=" << a2)
DEF_TEST_TYPE (TestPluginType3, (int a1, int a2, int a3), "Test3 a1=" << a1 << " a2=" << a2 << " a3=" << a3)
DEF_TEST_TYPE (TestPluginType4, (int a1, int a2, int a3, int a4), "Test4 a1=" << a1 << " a2=" << a2 << " a3=" << a3 << " a4=" << a4)


#endif // PLUGIN_MANAGER_TEST_PLUGIN_TYPE_ARGS_H
