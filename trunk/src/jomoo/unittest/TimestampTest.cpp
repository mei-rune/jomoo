
#include "stdafx.h"

#include "TimestampTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "jomoo/Timestamp.h"
#include "jomoo/Threading.hpp"


TimestampTest::TimestampTest(const std::string& name): CppUnit::TestCase(name)
{
}


TimestampTest::~TimestampTest()
{
}


void TimestampTest::testTimestamp()
{
	Timestamp t1;
	::Sleep(200);
	Timestamp t2;
	Timestamp t3 = t2;
	CPPUNIT_ASSERT (t1 != t2);
	CPPUNIT_ASSERT (!(t1 == t2));
	CPPUNIT_ASSERT (t2 > t1);
	CPPUNIT_ASSERT (t2 >= t1);
	CPPUNIT_ASSERT (!(t1 > t2));
	CPPUNIT_ASSERT (!(t1 >= t2));
	CPPUNIT_ASSERT (t2 == t3);
	CPPUNIT_ASSERT (!(t2 != t3));
	CPPUNIT_ASSERT (t2 >= t3);
	CPPUNIT_ASSERT (t2 <= t3);
	int64_t d = (t2 - t1);
	CPPUNIT_ASSERT (d >= 180000 && d <= 300000);
	
	t1.swap(t2);
	CPPUNIT_ASSERT (t1 > t2);
	t2.swap(t1);
	
	int64_t tv = t1.utcTime();
	Timestamp t4 = Timestamp::fromUtcTime(tv);
	CPPUNIT_ASSERT (t1 == t4);
	
	Timestamp epoch(0);
	tv = epoch.utcTime();
	CPPUNIT_ASSERT (tv >> 32 == 0x01B21DD2);
	CPPUNIT_ASSERT ((tv & 0xFFFFFFFF) == 0x13814000);
	
	Timestamp now;
	::Sleep(201);
	CPPUNIT_ASSERT (now.elapsed() >= 200000);
	CPPUNIT_ASSERT (now.isElapsed(200000));
	CPPUNIT_ASSERT (!now.isElapsed(2000000));
	
#if defined(_WIN32)
	{
		Timestamp now;
		u_int32_t low;
		u_int32_t high;
		now.toFileTimeNP(low, high);
		Timestamp ts = Timestamp::fromFileTimeNP(low, high);
		CPPUNIT_ASSERT (now == ts);
	}
#endif
}


void TimestampTest::setUp()
{
}


void TimestampTest::tearDown()
{
}


CppUnit::Test* TimestampTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TimestampTest");

	//CppUnit_addTest(pSuite, TimestampTest, testTimestamp);

	return pSuite;
}
