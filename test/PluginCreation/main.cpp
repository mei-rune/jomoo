//<<<<<< INCLUDES                                                       >>>>>>

#include "Hazel.PluginManager/PluginManager.h"
#include "../PluginFactory/TestPluginFactory.cpp"
#include "../PluginFactory/TestPluginType.h"

#include "../PluginFactoryArgs/TestPluginFactoryArgs.h"
#include "../PluginFactoryArgs/TestPluginTypeArgs.h"

int main (int, char **argv)
{
    TestPluginType *p;

	_seal initPluginManager();
   
    assert (p = TestPluginFactory::get ().create ("Sample", 1, 2.0));
	assert( p->foo() == "Sample" );
	TestPluginFactory::get().release( "Sample",p );

    assert (p = TestPluginFactory::get ().create ("Init", 3, 4.0));
	assert( p->foo() == "Init" );
    TestPluginFactory::get().release( "Init",p );


	TestPluginType0 *p0;
    TestPluginType1 *p1;
    TestPluginType2 *p2;
    TestPluginType3 *p3;
    TestPluginType4 *p4;
	TestPluginType4 *p5;
   

    assert (p0 = TestPluginFactoryArgs0::get ().create ("Sample"));
	assert( p0->foo() == "Test0" );
    assert (p1 = TestPluginFactoryArgs1::get ().create ("Sample", 1));
	assert( p1->foo() == "Test1" );
    assert (p2 = TestPluginFactoryArgs2::get ().create ("Sample", 1, 2));
	assert( p2->foo() == "Test2" );
    assert (p3 = TestPluginFactoryArgs3::get ().create ("Sample", 1, 2, 3));
	assert( p3->foo() == "Test3" );
    assert (p4 = TestPluginFactoryArgs4::get ().create ("Sample", 1, 2, 3, 4));
	assert( p4->foo() == "Test4" );

	assert (p5 = TestPluginFactoryArgs4::get ().create ( 1, 2, 3, 4));
	assert( p5->foo() == "Test4" );

	TestPluginFactoryArgs0::get ().release( "Sample", p0 );
    TestPluginFactoryArgs1::get ().release( "Sample", p1 );
    TestPluginFactoryArgs2::get ().release( "Sample", p2 );
    TestPluginFactoryArgs3::get ().release( "Sample", p3 );
    TestPluginFactoryArgs4::get ().release( "Sample", p4 );
	TestPluginFactoryArgs4::get ().release( p5 );

    return 0;
}
