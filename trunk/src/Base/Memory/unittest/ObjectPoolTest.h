
#ifdef TEST
#ifndef TEST_ConnectionObjectPool_H
#define TEST_ConnectionObjectPool_H

#include "../ObjectPool.H"

_memory_begin

class Connection 
{
public:
	Connection( )
	{
		std::cout << "Connection" << std::endl;	
	}

	~Connection( )
	{
		std::cout << "~Connection" << std::endl;	
	}
};

//void TestObjectPool()
//{
//	_hazel ObjectPool< Connection > pool( "ConnectionObjectPool",1000 );
//	std::list< Connection* > ls;
//	for( int i = 0; i < 1000; i ++ )
//	{
//		Connection* p = pool.malloc( );
//		ls.push_back( p );
//	}
//	for( std::list< Connection* >::iterator it = ls.begin()
//		; it != ls.end()
//		; it ++ )
//		pool.free( *it );
//	ls.clear();
//	
//	for( int i = 0; i < 1000; i ++ )
//	{
//		Connection* p = pool.malloc( );
//		ls.push_back( p );
//	}
//	for( std::list< Connection* >::iterator it = ls.begin()
//		; it != ls.end()
//		; it ++ )
//		pool.free( *it );
//	ls.clear();
//
//}
//

void TestFixed_Pool_T()
{
	_hazel Fixed_Pool_T< Connection > pool( getPool( ),1000 ,"Fixed" );
	std::list< Connection* > ls;
	for( int i = 0; i < 1000; i ++ )
	{
		Connection* p = pool.malloc( );
		ls.push_back( p );
	}
	for( std::list< Connection* >::iterator it = ls.begin()
		; it != ls.end()
		; it ++ )
		pool.free( *it );
	ls.clear();
	
	for( int i = 0; i < 1000; i ++ )
	{
		Connection* p = pool.malloc( );
		ls.push_back( p );
	}
	for( std::list< Connection* >::iterator it = ls.begin()
		; it != ls.end()
		; it ++ )
		pool.free( *it );
	ls.clear();

}


void TestPool_T()
{
	typedef Pool_T< Connection > Pool;
	Pool pool( createPool( "ConnectionPool_T",1000 , Pool::CHUNK_SIZE ) , "ConnectionPool_T" );
	std::list< Connection* > ls;
	for( int i = 0; i < 1000; i ++ )
	{
		Connection* p = pool.malloc( );
		ls.push_back( p );
	}
	for( std::list< Connection* >::iterator it = ls.begin()
		; it != ls.end()
		; it ++ )
		pool.free( *it );
	ls.clear();
	
	for( int i = 0; i < 1000; i ++ )
	{
		Connection* p = pool.malloc( );
		ls.push_back( p );
	}
	for( std::list< Connection* >::iterator it = ls.begin()
		; it != ls.end()
		; it ++ )
		pool.free( *it );
	ls.clear();

}

_memory_end

#endif //TEST_ConnectionObjectPool_H
#endif //TEST