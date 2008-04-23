

#ifndef DateTimeFormatterTest_INCLUDED
#define DateTimeFormatterTest_INCLUDED


#include "CppUnit/TestCase.h"
#include <cppunit/extensions/HelperMacros.h>

class DateTimeFormatterTest: public CppUnit::TestFixture
{
public:

  CPPUNIT_TEST_SUITE( DateTimeFormatterTest );
	CPPUNIT_TEST( testISO8601);
	CPPUNIT_TEST( testRFC822);
	CPPUNIT_TEST( testRFC1123);
	CPPUNIT_TEST( testHTTP);
	CPPUNIT_TEST( testRFC850);
	CPPUNIT_TEST( testRFC1036);
	CPPUNIT_TEST( testASCTIME);
	CPPUNIT_TEST( testSORTABLE);
	CPPUNIT_TEST( testCustom);
	CPPUNIT_TEST( testTimespan);
  CPPUNIT_TEST_SUITE_END();
public:

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


private:
};


#endif // DateTimeFormatterTest_INCLUDED
