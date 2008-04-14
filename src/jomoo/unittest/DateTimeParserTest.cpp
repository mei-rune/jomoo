
#include "stdafx.h"
#include "DateTimeParserTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "jomoo/DateTimeParser.h"
#include "jomoo/DateTimeFormatter.h"
#include "jomoo/DateTime.h"
#include "jomoo/Timestamp.h"
#include "jomoo/exception.hpp"


DateTimeParserTest::DateTimeParserTest(const std::string& name): CppUnit::TestCase(name)
{
}


DateTimeParserTest::~DateTimeParserTest()
{
}


void DateTimeParserTest::testISO8601()
{
	int tzd;
	DateTime dt = DateTimeParser::parse(DateTimeFormatter::ISO8601_FORMAT, "2005-01-08T12:30:00Z", tzd);

	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);

	dt = DateTimeParser::parse(DateTimeFormatter::ISO8601_FORMAT, "2005-01-08T12:30:00+01:00", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 3600);

	dt = DateTimeParser::parse(DateTimeFormatter::ISO8601_FORMAT, "2005-01-08T12:30:00-01:00", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == -3600);

	dt = DateTimeParser::parse(DateTimeFormatter::ISO8601_FORMAT, "2005-01-08T12:30:00", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);

	dt = DateTimeParser::parse(DateTimeFormatter::ISO8601_FORMAT, "2005-01-08", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 0);
	CPPUNIT_ASSERT (dt.minute() == 0);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);
}


void DateTimeParserTest::testRFC822()
{
	int tzd;
	DateTime dt = DateTimeParser::parse(DateTimeFormatter::RFC822_FORMAT, "Sat, 8 Jan 05 12:30:00 GMT", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);

	dt = DateTimeParser::parse(DateTimeFormatter::RFC822_FORMAT, "Sat, 8 Jan 05 12:30:00 +0100", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 3600);

	dt = DateTimeParser::parse(DateTimeFormatter::RFC822_FORMAT, "Sat, 8 Jan 05 12:30:00 -0100", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == -3600);

	dt = DateTimeParser::parse(DateTimeFormatter::RFC822_FORMAT, "Tue, 18 Jan 05 12:30:00 CET", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 18);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 3600);

	dt = DateTimeParser::parse(DateTimeFormatter::RFC822_FORMAT, "Wed, 12 Sep 73 02:01:12 CEST", tzd);
	CPPUNIT_ASSERT (dt.year() == 1973);
	CPPUNIT_ASSERT (dt.month() == 9);
	CPPUNIT_ASSERT (dt.day() == 12);
	CPPUNIT_ASSERT (dt.hour() == 2);
	CPPUNIT_ASSERT (dt.minute() == 1);
	CPPUNIT_ASSERT (dt.second() == 12);
	CPPUNIT_ASSERT (tzd == 7200);

	dt = DateTimeParser::parse(DateTimeFormatter::RFC822_FORMAT, "12 Sep 73 02:01:12 CEST", tzd);
	CPPUNIT_ASSERT (dt.year() == 1973);
	CPPUNIT_ASSERT (dt.month() == 9);
	CPPUNIT_ASSERT (dt.day() == 12);
	CPPUNIT_ASSERT (dt.hour() == 2);
	CPPUNIT_ASSERT (dt.minute() == 1);
	CPPUNIT_ASSERT (dt.second() == 12);
	CPPUNIT_ASSERT (tzd == 7200);
}


void DateTimeParserTest::testRFC1123()
{
	int tzd;
	DateTime dt = DateTimeParser::parse(DateTimeFormatter::RFC1123_FORMAT, "Sat, 8 Jan 2005 12:30:00 GMT", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);

	dt = DateTimeParser::parse(DateTimeFormatter::RFC1123_FORMAT, "Sat, 8 Jan 2005 12:30:00 +0100", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 3600);

	dt = DateTimeParser::parse(DateTimeFormatter::RFC1123_FORMAT, "Sat, 8 Jan 2005 12:30:00 -0100", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == -3600);

	dt = DateTimeParser::parse(DateTimeFormatter::RFC1123_FORMAT, "Sun, 20 Jul 1969 16:17:30 EDT", tzd);
	CPPUNIT_ASSERT (dt.year() == 1969);
	CPPUNIT_ASSERT (dt.month() == 7);
	CPPUNIT_ASSERT (dt.day() == 20);
	CPPUNIT_ASSERT (dt.hour() == 16);
	CPPUNIT_ASSERT (dt.minute() == 17);
	CPPUNIT_ASSERT (dt.second() == 30);
	CPPUNIT_ASSERT (tzd == -14400);
}


void DateTimeParserTest::testHTTP()
{
	int tzd;
	DateTime dt = DateTimeParser::parse(DateTimeFormatter::HTTP_FORMAT, "Sat, 08 Jan 2005 12:30:00 GMT", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);

	dt = DateTimeParser::parse(DateTimeFormatter::HTTP_FORMAT, "Sat, 08 Jan 2005 12:30:00 +0100", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 3600);

	dt = DateTimeParser::parse(DateTimeFormatter::HTTP_FORMAT, "Sat, 08 Jan 2005 12:30:00 -0100", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == -3600);
}


void DateTimeParserTest::testRFC850()
{
	int tzd;
	DateTime dt = DateTimeParser::parse(DateTimeFormatter::RFC850_FORMAT, "Saturday, 8-Jan-05 12:30:00 GMT", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);

	dt = DateTimeParser::parse(DateTimeFormatter::RFC850_FORMAT, "Saturday, 8-Jan-05 12:30:00 +0100", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 3600);

	dt = DateTimeParser::parse(DateTimeFormatter::RFC850_FORMAT, "Saturday, 8-Jan-05 12:30:00 -0100", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == -3600);
	
	dt = DateTimeParser::parse(DateTimeFormatter::RFC850_FORMAT, "Wed, 12-Sep-73 02:01:12 CEST", tzd);
	CPPUNIT_ASSERT (dt.year() == 1973);
	CPPUNIT_ASSERT (dt.month() == 9);
	CPPUNIT_ASSERT (dt.day() == 12);
	CPPUNIT_ASSERT (dt.hour() == 2);
	CPPUNIT_ASSERT (dt.minute() == 1);
	CPPUNIT_ASSERT (dt.second() == 12);
	CPPUNIT_ASSERT (tzd == 7200);
}


void DateTimeParserTest::testRFC1036()
{
	int tzd;
	DateTime dt = DateTimeParser::parse(DateTimeFormatter::RFC1036_FORMAT, "Saturday, 8 Jan 05 12:30:00 GMT", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);

	dt = DateTimeParser::parse(DateTimeFormatter::RFC1036_FORMAT, "Saturday, 8 Jan 05 12:30:00 +0100", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 3600);

	dt = DateTimeParser::parse(DateTimeFormatter::RFC1036_FORMAT, "Saturday, 8 Jan 05 12:30:00 -0100", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == -3600);
}


void DateTimeParserTest::testASCTIME()
{
	int tzd;
	DateTime dt = DateTimeParser::parse(DateTimeFormatter::ASCTIME_FORMAT, "Sat Jan  8 12:30:00 2005", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);
}


void DateTimeParserTest::testSORTABLE()
{
	int tzd;
	DateTime dt = DateTimeParser::parse(DateTimeFormatter::SORTABLE_FORMAT, "2005-01-08 12:30:00", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);

	dt = DateTimeParser::parse(DateTimeFormatter::SORTABLE_FORMAT, "2005-01-08", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 0);
	CPPUNIT_ASSERT (dt.minute() == 0);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);
}


void DateTimeParserTest::testCustom()
{
	int tzd;
	DateTime dt = DateTimeParser::parse("%d-%b-%Y", "18-Jan-2005", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 18);
	CPPUNIT_ASSERT (dt.hour() == 0);
	CPPUNIT_ASSERT (dt.minute() == 0);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);
	
	dt = DateTimeParser::parse("%m/%d/%y", "01/18/05", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 18);
	CPPUNIT_ASSERT (dt.hour() == 0);
	CPPUNIT_ASSERT (dt.minute() == 0);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);
	
	dt = DateTimeParser::parse("%h:%M %a", "12:30 am", tzd);
	CPPUNIT_ASSERT (dt.hour() == 0);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);

	dt = DateTimeParser::parse("%h:%M %a", "12:30 PM", tzd);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
}


void DateTimeParserTest::testGuess()
{
	int tzd;
	DateTime dt = DateTimeParser::parse("2005-01-08T12:30:00Z", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);

	dt = DateTimeParser::parse("Sat, 8 Jan 05 12:30:00 +0100", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 3600);
	
	dt = DateTimeParser::parse("Sat Jan  8 12:30:00 2005", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);

	dt = DateTimeParser::parse("2005-01-08 12:30:00", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 12);
	CPPUNIT_ASSERT (dt.minute() == 30);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);

	dt = DateTimeParser::parse("2005-01-08", tzd);
	CPPUNIT_ASSERT (dt.year() == 2005);
	CPPUNIT_ASSERT (dt.month() == 1);
	CPPUNIT_ASSERT (dt.day() == 8);
	CPPUNIT_ASSERT (dt.hour() == 0);
	CPPUNIT_ASSERT (dt.minute() == 0);
	CPPUNIT_ASSERT (dt.second() == 0);
	CPPUNIT_ASSERT (tzd == 0);
}


void DateTimeParserTest::testParseMonth()
{
	std::string str = "January";
	std::string::const_iterator it = str.begin();
	int month = DateTimeParser::parseMonth(it, str.end());
	CPPUNIT_ASSERT (month == 1);
	str = "February";
	it = str.begin();
	month = DateTimeParser::parseMonth(it, str.end());
	CPPUNIT_ASSERT (month == 2);
	str = "December";
	it = str.begin();
	month = DateTimeParser::parseMonth(it, str.end());
	CPPUNIT_ASSERT (month == 12);
	str = "Jan";
	it = str.begin();
	month = DateTimeParser::parseMonth(it, str.end());
	CPPUNIT_ASSERT (month == 1);
	str = "Feb";
	it = str.begin();
	month = DateTimeParser::parseMonth(it, str.end());
	CPPUNIT_ASSERT (month == 2);
	str = "jan";
	it = str.begin();
	month = DateTimeParser::parseMonth(it, str.end());
	CPPUNIT_ASSERT (month == 1);
	str = "feb";
	it = str.begin();
	month = DateTimeParser::parseMonth(it, str.end());
	CPPUNIT_ASSERT (month == 2);

	try
	{
		str = "ja";
		it = str.begin();
		month = DateTimeParser::parseMonth(it, str.end());
		fail("Not a valid month name - must throw");
	}
	catch (SyntaxException&)
	{
	}
}


void DateTimeParserTest::testParseDayOfWeek()
{
	std::string str = "Sunday";
	std::string::const_iterator it = str.begin();
	int dow = DateTimeParser::parseDayOfWeek(it, str.end());
	CPPUNIT_ASSERT (dow == 0);
	str = "Monday";
	it = str.begin();
	dow = DateTimeParser::parseDayOfWeek(it, str.end());
	CPPUNIT_ASSERT (dow == 1);
	str = "Saturday";
	it = str.begin();
	dow = DateTimeParser::parseDayOfWeek(it, str.end());
	CPPUNIT_ASSERT (dow == 6);
	str = "Sun";
	it = str.begin();
	dow = DateTimeParser::parseDayOfWeek(it, str.end());
	CPPUNIT_ASSERT (dow == 0);
	str = "Mon";
	it = str.begin();
	dow = DateTimeParser::parseDayOfWeek(it, str.end());
	CPPUNIT_ASSERT (dow == 1);
	str = "sun";
	it = str.begin();
	dow = DateTimeParser::parseDayOfWeek(it, str.end());
	CPPUNIT_ASSERT (dow == 0);
	str = "mon";
	it = str.begin();
	dow = DateTimeParser::parseDayOfWeek(it, str.end());
	CPPUNIT_ASSERT (dow == 1);

	try
	{
		str = "su";
		it = str.begin();
		dow = DateTimeParser::parseDayOfWeek(it, str.end());
		fail("Not a valid weekday name - must throw");
	}
	catch (SyntaxException&)
	{
	}
}


void DateTimeParserTest::setUp()
{
}


void DateTimeParserTest::tearDown()
{
}


CppUnit::Test* DateTimeParserTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DateTimeParserTest");

	//CppUnit_addTest(pSuite, DateTimeParserTest, testISO8601);
	//CppUnit_addTest(pSuite, DateTimeParserTest, testRFC822);
	//CppUnit_addTest(pSuite, DateTimeParserTest, testRFC1123);
	//CppUnit_addTest(pSuite, DateTimeParserTest, testHTTP);
	//CppUnit_addTest(pSuite, DateTimeParserTest, testRFC850);
	//CppUnit_addTest(pSuite, DateTimeParserTest, testRFC1036);
	//CppUnit_addTest(pSuite, DateTimeParserTest, testASCTIME);
	//CppUnit_addTest(pSuite, DateTimeParserTest, testSORTABLE);
	//CppUnit_addTest(pSuite, DateTimeParserTest, testCustom);
	//CppUnit_addTest(pSuite, DateTimeParserTest, testGuess);
	//CppUnit_addTest(pSuite, DateTimeParserTest, testParseMonth);
	//CppUnit_addTest(pSuite, DateTimeParserTest, testParseDayOfWeek);

	return pSuite;
}
