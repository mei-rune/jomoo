// addr_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "communication/BOE_INET_Addr.H"
#include "assert.h"

int _tmain(int argc, _TCHAR* argv[])
{
	BOE_INET_Addr addr1( "100.100.100.1:34" );
	BOE_INET_Addr addr2( 34 , inet_addr( "100.100.100.1" ) );
	BOE_INET_Addr addr3( 34, "100.100.100.1" );
	BOE_INET_Addr addr4( "34","100.100.100.1" );
	BOE_INET_Addr addr5( "34","localhost" );

	assert( "100.100.100.1:34" == addr1.to_string() );
	assert( "100.100.100.1:34" == addr2.to_string() );
	assert( "100.100.100.1:34" == addr3.to_string() );
	assert( "100.100.100.1:34" == addr4.to_string() );
	assert( "100.100.100.146:34" == addr5.to_string() );

	return 0;
}

