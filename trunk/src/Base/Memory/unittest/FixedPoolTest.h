
#ifdef TEST
#ifndef TEST_FIXEDPOOL_H
#define TEST_FIXEDPOOL_H

#include "../FixedPool.cpp"
#include <list>
_memory_begin

void TestFixedPool()
{
	FixedPool pool( "aaa", 1000, 20 );

	std::list< void* > ls;
	for( int i = 0; i < 1000; i ++ )
	{
		void* p = pool.malloc( );
		memset( p, 0, 20 );
		ls.push_back( p );
	}
	for( std::list< void* >::iterator it = ls.begin()
		; it != ls.end()
		; it ++ )
		pool.free( *it );
	ls.clear();
	
	for( int i = 0; i < 1000; i ++ )
	{
		void* p = pool.malloc( );
		memset( p, 0, 20 );
		ls.push_back( p );
	}
	for( std::list< void* >::iterator it = ls.begin()
		; it != ls.end()
		; it ++ )
		pool.free( *it );
	ls.clear();
}
_memory_end

#endif //TEST_FIXEDPOOL_H
#endif //TEST