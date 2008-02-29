#ifdef TEST

#ifndef TEST_LINK_H
#define TEST_LINK_H

#include "../ThreadSafePtrQueue.hpp"
#include <iostream>

struct LINK LIST_INTERFACE( LINK )
{
	LIST_DEFINE( LINK );
	int value;
};

void Test()
{
	ThreadSafePtrQueue< LINK > queue;
	for( int i = 0; i < 100 ; i ++ )
	{
		LINK* l = new LINK();
		l->value = i;
		queue.push( l );
	}

	LINK* l = queue.pop( );
	while( l != 0 )
	{
		std::cout << l->value << "";
		
		l = queue.pop( );
	}
	std::cout << std::endl;
}

#endif // TEST_LINK_H
#endif // TEST