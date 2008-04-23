
#include "stdafx.h"
#include "marco.h"
#include "TimespanTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "jomoo/Timespan.h"




TimespanTest::TimespanTest(): CppUnit::TestCase()
{
}


TimespanTest::~TimespanTest()
{
}


void TimespanTest::testConversions()
{
	Timespan ts;
	CPPUNIT_ASSERT (ts.totalMicroseconds() == 0);
	ts = Timespan::DAYS;
	CPPUNIT_ASSERT (ts.totalMicroseconds() == Timespan::DAYS);
	CPPUNIT_ASSERT (ts.totalMilliseconds() == 86400000);
	CPPUNIT_ASSERT (ts.totalSeconds() == 86400);
	CPPUNIT_ASSERT (ts.totalMinutes() == 60*24);
	CPPUNIT_ASSERT (ts.totalHours() == 24);
	CPPUNIT_ASSERT (ts.days() == 1);
	
	CPPUNIT_ASSERT (ts.microseconds() == 0);
	CPPUNIT_ASSERT (ts.milliseconds() == 0);
	CPPUNIT_ASSERT (ts.seconds() == 0);
	CPPUNIT_ASSERT (ts.minutes() == 0);
	CPPUNIT_ASSERT (ts.hours() == 0);
	
	ts.assign(2, 12, 30, 10, 123456);
	CPPUNIT_ASSERT (ts.microseconds() == 456);
	CPPUNIT_ASSERT (ts.milliseconds() == 123);
	CPPUNIT_ASSERT (ts.seconds() == 10);
	CPPUNIT_ASSERT (ts.minutes() == 30);
	CPPUNIT_ASSERT (ts.hours() == 12);
	CPPUNIT_ASSERT (ts.days() == 2);

	ts.assign(0, 36, 30, 10, 123456);
	CPPUNIT_ASSERT (ts.microseconds() == 456);
	CPPUNIT_ASSERT (ts.milliseconds() == 123);
	CPPUNIT_ASSERT (ts.useconds() == 123456);
	CPPUNIT_ASSERT (ts.seconds() == 10);
	CPPUNIT_ASSERT (ts.minutes() == 30);
	CPPUNIT_ASSERT (ts.hours() == 12);
	CPPUNIT_ASSERT (ts.days() == 1);

	ts.assign(0, 0, 2190, 10, 123456);
	CPPUNIT_ASSERT (ts.microseconds() == 456);
	CPPUNIT_ASSERT (ts.milliseconds() == 123);
	CPPUNIT_ASSERT (ts.useconds() == 123456);
	CPPUNIT_ASSERT (ts.seconds() == 10);
	CPPUNIT_ASSERT (ts.minutes() == 30);
	CPPUNIT_ASSERT (ts.hours() == 12);
	CPPUNIT_ASSERT (ts.days() == 1);
}


void TimespanTest::testComparisons()
{
	Timespan ts1(10000000);
	Timespan ts2(20000000);
	Timespan ts3(20000000);
	
	CPPUNIT_ASSERT (ts1 != ts2);
	CPPUNIT_ASSERT (!(ts1 == ts2));
	CPPUNIT_ASSERT (ts1 <= ts2);
	CPPUNIT_ASSERT (ts1 < ts2);
	CPPUNIT_ASSERT (ts2 > ts1);
	CPPUNIT_ASSERT (ts2 >= ts1);
	
	CPPUNIT_ASSERT (ts2 == ts3);
	CPPUNIT_ASSERT (!(ts2 != ts3));
	CPPUNIT_ASSERT (ts2 >= ts3);
	CPPUNIT_ASSERT (ts2 <= ts3);
	CPPUNIT_ASSERT (!(ts2 > ts3));
	CPPUNIT_ASSERT (!(ts2 < ts3));
	
	CPPUNIT_ASSERT (ts1 == 10000000);
	CPPUNIT_ASSERT (ts1 != 20000000);
	CPPUNIT_ASSERT (ts1 <= 10000000);
	CPPUNIT_ASSERT (ts1 <= 20000000);
	CPPUNIT_ASSERT (ts1 >= 10000000);
	CPPUNIT_ASSERT (ts1 >= 5000000);
	CPPUNIT_ASSERT (ts1 < 20000000);
	CPPUNIT_ASSERT (ts1 > 5000000);
}


void TimespanTest::testArithmetics()
{
	Timespan ts1(100000000);
	Timespan ts2(50000000);
	Timespan ts3;
	ts3 = ts1 + ts2;
	CPPUNIT_ASSERT (ts3 == 150000000);
	ts3 = ts1 + 30000000;
	CPPUNIT_ASSERT (ts3 == 130000000);
	ts3 = ts1 - ts2;
	CPPUNIT_ASSERT (ts3 == 50000000);
	ts3 = ts1 - 20000000;
	CPPUNIT_ASSERT (ts3 == 80000000);
	ts3 += 20000000;
	CPPUNIT_ASSERT (ts3 == ts1);
	ts3 -= ts2;
	CPPUNIT_ASSERT (ts3 == ts2);
}


void TimespanTest::testSwap()
{
	Timespan ts1(10000000);
	Timespan ts2(50000000);
	
	CPPUNIT_ASSERT (ts1 < ts2);
	ts1.swap(ts2);
	CPPUNIT_ASSERT (ts2 < ts1);
}


void TimespanTest::setUp()
{
}


void TimespanTest::tearDown()
{
}


CppUnit::Test* TimespanTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TimespanTest");

	CppUnit_addTest(pSuite, TimespanTest, testConversions);
	CppUnit_addTest(pSuite, TimespanTest, testComparisons);
	CppUnit_addTest(pSuite, TimespanTest, testArithmetics);
	CppUnit_addTest(pSuite, TimespanTest, testSwap);

	return pSuite;
}
