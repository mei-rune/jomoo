// thread_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include "jomoo/threading.hpp"
#include <jomoo/functional.hpp>
#include <boost/tr1/memory.hpp>


mutex _m;
class runner
{
public:
	void run1()
	{
		mutex::spcode_lock lock( _m );
		std::cout << "runer::run1()" << std::endl;
	}

	void run2(int i)
	{
		mutex::spcode_lock lock( _m );
		std::cout << "runer::run2( " << i << ")" << std::endl;
	}

	void run3(int i,int j)
	{
		mutex::spcode_lock lock( _m );
		std::cout << "runer::run3(" << i << "," << j << ")" << std::endl;
	}
};

void _run1()
{
		mutex::spcode_lock lock( _m );
	std::cout << "_run1()" << std::endl;
}

void _run2(int i)
{
		mutex::spcode_lock lock( _m );
	std::cout << "_run2( " << i << ")" << std::endl;
}

void _run3(int i,int j)
{
		mutex::spcode_lock lock( _m );
	std::cout << "_run3(" << i << "," << j << ")" << std::endl;
}

void _run4(int i,int j, int k)
{
		mutex::spcode_lock lock( _m );
	std::cout << "_run4(" << i << "," << j << "," << k << ")" << std::endl;
}


int _tmain(int argc, _TCHAR* argv[])
{

	runner * r = new runner();
	std::tr1::shared_ptr<runner> ptr( r );

	std::list< _jomoo_thread thread_t > threads;

 	threads.push_back( _jomoo_thread create_thread( _jomoo mem_fun( &runner::run1 ), r ,0 ) );
	threads.push_back( _jomoo_thread create_thread( _jomoo mem_fun( &runner::run1 ), ptr,0  ) );

	

 	threads.push_back( _jomoo_thread create_thread( _jomoo mem_fun( &runner::run2 ), r, 1 , 0 ) );
	threads.push_back( _jomoo_thread create_thread( _jomoo mem_fun( &runner::run2 ), ptr,2 , 0  ) );

	
 	threads.push_back( _jomoo_thread create_thread( _jomoo mem_fun( &runner::run3 ), r, 1 ,1, 0 ) );
	threads.push_back( _jomoo_thread create_thread( _jomoo mem_fun( &runner::run3 ), ptr,2 ,2, 0  ) );


	
	threads.push_back( _jomoo_thread create_thread( &_run1 ) );
	threads.push_back( _jomoo_thread create_thread( &_run2, 1, 0 ) );
	threads.push_back( _jomoo_thread create_thread( &_run3, 2,1, 0 ) );
	threads.push_back( _jomoo_thread create_thread( &_run4, 2,2,1, 0 ) );

	for( std::list<_jomoo_thread thread_t >::iterator it = threads.begin()
		; it != threads.end(); it ++ )
	{
		_jomoo_thread join_thread( *it );
	}

	return 0;
}

