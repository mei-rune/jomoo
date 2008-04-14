


#ifndef DateTimeTest_INCLUDED
#define DateTimeTest_INCLUDED


#include "CppUnit/TestCase.h"


class DateTimeTest: public CppUnit::TestCase
{
public:
	DateTimeTest(const std::string& name);
	~DateTimeTest();

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

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // DateTimeTest_INCLUDED
