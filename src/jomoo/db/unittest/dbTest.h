

#ifndef DbTest_INCLUDED
#define DbTest_INCLUDED


#include "CppUnit/TestCase.h"
#include <cppunit/extensions/HelperMacros.h>

class dbTest: public CppUnit::TestFixture
{
public:

  CPPUNIT_TEST_SUITE( dbTest );
	CPPUNIT_TEST( testConnection );
	CPPUNIT_TEST( testCommand );
	CPPUNIT_TEST( testQuery );
	CPPUNIT_TEST( testTransaction );
  CPPUNIT_TEST_SUITE_END();
public:

	void testConnection();
	void testCommand();
	void testQuery();
	void testTransaction();

	void setUp();
	void tearDown();


private:
};


#endif // DbTest_INCLUDED
