#pragma once

#ifdef UNITTEST

#include "testTypes.h"

class SerializeTestCase :
	public CppUnit::TestFixture
{
public:
	CPPUNIT_TEST_SUITE(SerializeTestCase);
CPPUNIT_TEST( testArray );
//CPPUNIT_TEST( testDB );
CPPUNIT_TEST( testcostumlist );
CPPUNIT_TEST( testSerialize );
CPPUNIT_TEST( testSerialize2 );
CPPUNIT_TEST( testStream );
//CPPUNIT_TEST( testStream2 );
CPPUNIT_TEST( testDomAdapter );
CPPUNIT_TEST_SUITE_END();
public:
	SerializeTestCase(void);
	~SerializeTestCase(void);



	// 初始化函数
	void setUp ();
	// 清理函数
	void tearDown();
	
	void testDB();

	void testSerialize ();

	void testRefletion( );

	void testArray( );

	void testStream( );

	void testSerialize2 ();

	void testDomAdapter( );

	void testcostumlist( );

	void testStream2( );

	void show( Tester& t  , const char* file = 0 );
	
private:


	std::auto_ptr< Tester > ptr;
};


#endif