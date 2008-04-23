

#ifndef DateTimeFormatterTest_INCLUDED
#define DateTimeFormatterTest_INCLUDED


#include "CppUnit/TestCase.h"


class DateTimeFormatterTest: public CppUnit::TestCase
{
public:
	DateTimeFormatterTest( );
	~DateTimeFormatterTest();

	void testISO8601();
	void testRFC822();
	void testRFC1123();
	void testHTTP();
	void testRFC850();
	void testRFC1036();
	void testASCTIME();
	void testSORTABLE();
	void testCustom();
	void testTimespan();
	
	void setUp();
	void tearDown();

	static CppUnit::Test* suite();

private:
};


#endif // DateTimeFormatterTest_INCLUDED
