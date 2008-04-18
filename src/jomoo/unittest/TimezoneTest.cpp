
#include "stdafx.h"
#include "marco.h"
#include "TimezoneTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "jomoo/Timezone.h"
#include <iostream>


TimezoneTest::TimezoneTest(const std::string& name): CppUnit::TestCase(name)
{
}


TimezoneTest::~TimezoneTest()
{
}


void TimezoneTest::testTimezone()
{
	std::string name = Timezone::name();
	std::string stdName = Timezone::standardName();
	std::string dstName = Timezone::dstName();
	std::cout << "Timezone Names: " << name << ", " << stdName << ", " << dstName << std::endl;
	int utcOffset = Timezone::utcOffset();
	std::cout << "UTC Offset: " << utcOffset << std::endl;
	int dst = Timezone::dst();
	std::cout << "DST Offset: " << dst << std::endl;
}


void TimezoneTest::setUp()
{
}


void TimezoneTest::tearDown()
{
}


CppUnit::Test* TimezoneTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TimezoneTest");

	CppUnit_addTest(pSuite, TimezoneTest, testTimezone);

	return pSuite;
}
