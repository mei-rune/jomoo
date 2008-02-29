// PoolTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "test.h"
#include <time.h>


#ifdef TEST

void TestG()
{

	std::list< void* > ls;
	for( int i = 0; i < 1000; i ++ )
	{
		void* p = malloc( 20 );
		memset( p, 0, 20 );
		ls.push_back( p );
	}
	for( std::list< void* >::iterator it = ls.begin()
		; it != ls.end()
		; it ++ )
		free( *it );
	ls.clear();
	
	for( int i = 0; i < 1000; i ++ )
	{
		void* p = malloc( 20 );
		memset( p, 0, 20 );
		ls.push_back( p );
	}
	for( std::list< void* >::iterator it = ls.begin()
		; it != ls.end()
		; it ++ )
		free( *it );
	ls.clear();
}

time_t foopool()
{
	time_t t = time( 0 );
	for( int i = 0; i < 100; i ++ )
	_memory TestFixedPool();
	return time( 0 ) - t;
}

time_t foomalloc()
{
	time_t t = time( 0 );
	for( int i = 0; i < 100; i ++ )
	 TestG();
	return time( 0 ) - t;
}


class PoolTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( PoolTestCase );
  CPPUNIT_TEST( testRate );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();
protected:
	void testRate();
};


CPPUNIT_TEST_SUITE_REGISTRATION( PoolTestCase );

void PoolTestCase::setUp()
{
}

void PoolTestCase::tearDown()
{
}

void PoolTestCase::testRate()
{
	
	Test();

	time_t t = foomalloc();
	time_t p = foopool();

	std::cout << "pool:" << p << std::endl;
	std::cout << "malloc:" << t << std::endl;
	std::cout << "diff:" << t - p << std::endl;
	CPPUNIT_ASSERT( ( t - p ) > 0 );
}

#endif