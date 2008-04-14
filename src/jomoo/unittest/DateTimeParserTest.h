

#ifndef DateTimeParserTest_INCLUDED
#define DateTimeParserTest_INCLUDED


#include "CppUnit/TestCase.h"


class DateTimeParserTest: public CppUnit::TestCase
{
public:
	DateTimeParserTest(const std::string& name);
	~DateTimeParserTest();

	void testISO8601();
	void testRFC822();
	void testRFC1123();
	void testHTTP();
	void testRFC850();
	void testRFC1036();
	void testASCTIME();
	void testSORTABLE();
	void testCustom();
	void testGuess();
	void testParseMonth();
	void testParseDayOfWeek();

	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // DateTimeParserTest_INCLUDED
