
#include "stdafx.h"


#include "DateTimeTestSuite.h"
#include "TimestampTest.h"
#include "TimespanTest.h"
#include "TimezoneTest.h"
#include "DateTimeTest.h"
//#include "LocalDateTimeTest.h"
#include "DateTimeFormatterTest.h"
#include "DateTimeParserTest.h"


CppUnit::Test* DateTimeTestSuite::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DateTimeTestSuite");

	pSuite->addTest(TimestampTest::suite());
	pSuite->addTest(TimespanTest::suite());
	pSuite->addTest(TimezoneTest::suite());
	pSuite->addTest(DateTimeTest::suite());
	//pSuite->addTest(LocalDateTimeTest::suite());
	pSuite->addTest(DateTimeFormatterTest::suite());
	pSuite->addTest(DateTimeParserTest::suite());

	return pSuite;
}
