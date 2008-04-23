


#ifndef DateTimeTest_INCLUDED
#define DateTimeTest_INCLUDED


#include "CppUnit/TestCase.h"

#include <cppunit/extensions/HelperMacros.h>

class DateTimeTest: public CppUnit::TestFixture
{
public:
  CPPUNIT_TEST_SUITE( DateTimeTest );
	CPPUNIT_TEST( testTimestamp);
	CPPUNIT_TEST( testJulian);
	CPPUNIT_TEST( testGregorian);
	CPPUNIT_TEST( testConversions);
	CPPUNIT_TEST( testStatics);
	CPPUNIT_TEST( testCalcs);
	CPPUNIT_TEST( testAMPM);
	CPPUNIT_TEST( testRelational);
	CPPUNIT_TEST( testArithmetics);
	CPPUNIT_TEST( testSwap);

	CPPUNIT_TEST( testUsage);
	CPPUNIT_TEST( testSetYearDay);
	CPPUNIT_TEST( testIsValid);
	CPPUNIT_TEST( testDayOfWeek);
	CPPUNIT_TEST( testIncrementDecrement);
	CPPUNIT_TEST( testUTC);
	CPPUNIT_TEST( testTM);

  CPPUNIT_TEST_SUITE_END();

public:

	void testTimestamp();
	void testJulian();
	void testGregorian();
	void testConversions();
	void testStatics();
	void testCalcs();
	void testAMPM();
	void testRelational();
	void testArithmetics();
	void testSwap();
	void testUsage();
	void testSetYearDay();
	void testIsValid();
	void testDayOfWeek();
	void testIncrementDecrement();
	void testUTC();
	void testTM();

	void setUp();
	void tearDown();


private:
};


#endif // DateTimeTest_INCLUDED
