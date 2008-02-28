
#ifdef TEST
#ifndef TEST_SYSTEMPOOL_H
#define TEST_SYSTEMPOOL_H

#include "../SystemPool.cpp"

_memory_begin

void TestSystemPool()
{
	for( int i = 1; i < 1000; i ++ )
	{
		void* p = SystemPool::get().malloc( i );
		memset( p, 0, i );
		SystemPool::get().free( p );
	}
	
	for( int i = 1; i < 1000; i ++ )
	{
		void* p = SystemPool::get().malloc( i );
		memset( p, 0, i );
		SystemPool::get().free( p );
	}
}

_memory_end

#endif //TEST_SYSTEMPOOL_H
#endif //TEST