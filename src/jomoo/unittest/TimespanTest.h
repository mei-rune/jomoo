

#ifndef TimespanTest_INCLUDED
#define TimespanTest_INCLUDED


#include "CppUnit/TestCase.h"

#include <cppunit/extensions/HelperMacros.h>

class TimespanTest: public CppUnit::TestFixture
{
public:
  CPPUNIT_TEST_SUITE( TimespanTest );

	CPPUNIT_TEST( testConversions);
	CPPUNIT_TEST( testComparisons);
	CPPUNIT_TEST( testArithmetics);
	CPPUNIT_TEST( testSwap);

  CPPUNIT_TEST_SUITE_END();

public:

	void testConversions();
	void testComparisons();
	void testArithmetics();
	void testSwap();

	void setUp();
	void tearDown();


private:
};


#endif // TimespanTest_INCLUDED
