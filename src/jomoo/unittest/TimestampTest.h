

#ifndef TimestampTest_INCLUDED
#define TimestampTest_INCLUDED


#include "CppUnit/TestCase.h"
#include <cppunit/extensions/HelperMacros.h>


class TimestampTest: public CppUnit::TestFixture
{
public:
  CPPUNIT_TEST_SUITE( TimestampTest );

	CPPUNIT_TEST( testTimestamp);

  CPPUNIT_TEST_SUITE_END();

public:

	void testTimestamp();

	void setUp();
	void tearDown();
};


#endif // TimestampTest_INCLUDED
