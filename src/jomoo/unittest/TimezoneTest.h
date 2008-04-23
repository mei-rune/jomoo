

#ifndef TimezoneTest_INCLUDED
#define TimezoneTest_INCLUDED


#include "CppUnit/TestCase.h"
#include <cppunit/extensions/HelperMacros.h>


class TimezoneTest: public CppUnit::TestFixture
{
public:

  CPPUNIT_TEST_SUITE( TimezoneTest );

	CPPUNIT_TEST( testTimezone );

  CPPUNIT_TEST_SUITE_END();

public:

	void testTimezone();

	void setUp();
	void tearDown();

};


#endif // TimezoneTest_INCLUDED
