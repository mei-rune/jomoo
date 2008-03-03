



#include <stdafx.h>

#ifdef TEST

#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include "../ThreadSafePtrQueue.hpp"



struct LINK LIST_INTERFACE( LINK )
{
	LIST_DEFINE( LINK );
	int value;
};


class LinkTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( LinkTestCase );
  CPPUNIT_TEST( testSimply );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

protected:
	void testSimply();
};


CPPUNIT_TEST_SUITE_REGISTRATION( LinkTestCase );

void LinkTestCase::setUp()
{
}

void LinkTestCase::tearDown()
{
}

void LinkTestCase::testSimply()
{
	ThreadSafePtrQueue< LINK > queue;
	for( int i = 0; i < 100 ; i ++ )
	{
		LINK* l = new LINK();
		l->value = i;
		queue.push( l );
	}

	LINK* l = queue.pop( );
	while( l != 0 )
	{
		std::cout << l->value << "";
		
		l = queue.pop( );
	}
	std::cout << std::endl;
}


#endif // TEST