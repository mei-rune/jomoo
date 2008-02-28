
#ifndef CPP_UNIT_EXAMPLETESTCASE_H
#define CPP_UNIT_EXAMPLETESTCASE_H

#include <cppunit/extensions/HelperMacros.h>

/* 
 * A test case that is designed to produce
 * example errors and failures
 *
 */

class stringTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( stringTestCase );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testDataAccess );
  CPPUNIT_TEST( testFind );
  CPPUNIT_TEST( testFind_First_Of );
  CPPUNIT_TEST_SUITE_END();

public:

  void setUp();

protected:

  void testConstructor();
  void testDataAccess();
  void testFind();
  void testFind_First_Of();

};


#endif
