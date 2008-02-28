// MessageTester.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BOE/IM/Instance_IM.H"
//#include "BOE/BT_Log_Cxx.cpp"
#include <vector>

class TestSt
{
public:

	Byte i1;
	Int16 i2 ;
	Int32 i3 ;
	Int64 i4 ;
	Float i5;
	Double i6;
	tstring s ;



	Byte r1 ;
	Int16 r2 ;
	Int32 r3 ;
	Int64 r4 ;
	Float r5 ;
	Double r6 ;
	std::vector< char > rs;

	TestSt()
	{
		i1 = 10;
		i2 = 20;
		i3 = 30;
		i4 = 40;
		i5 = 50.5;
		i6 = 60.6;
		s = "adfsdfsdfsadfasdfsadfsadfsadfsadfsdf";

		r1 = 0;
		r2 = 0;
		r3 = 0;
		r4 = 0;
		r5 = 0.5;
		r6 = 0.6;
	}

	void Assert( )
	{
		assert( i1 == r1 );
		assert( i2 == r2 );
		assert( i3 == r3 );
		assert( i4 == r4 );
		assert( i5 == r5 );
		assert( i6 == r6 );
		assert( memcmp( s.c_str(), &rs[0], s.size() ) == 0 );
	}

	void write( BOE_Message_Ptr msg )
	{
		msg->write( i1 );
		msg->write( i2 );
		msg->write( i3 );
		msg->write( i4 );
		msg->write( i5 );
		msg->write( i6 );

		msg->write( ( Int32 )s.size() );
		msg->write( s.c_str(), s.size() );
	}

	void read( BOE_Message_Ptr msg )
	{
		msg->read( r1 );
		msg->read( r2 );
		msg->read( r3 );
		msg->read( r4 );
		msg->read( r5 );
		msg->read( r6 );

		Int32 l = 0;
		msg->read( l );
		rs.resize( l );
		msg->read( &rs[ 0 ], l );
	}

};


int _tmain(int argc, _TCHAR* argv[])
{
	//_io BOE_IM_Server_Ptr communicator = initializeIM( argc, argv );
	//
	//if( communicator.get() ==0 )
	//	return -1;

	 //init_BT_Log_Cxx(  );

	 Instance_IM instance;
	 instance.open( _util createProperties( argc , argv ) );

	 //instance.setLogger( new BT_Log_Cxx( 0 ) );
	 {
		 BOE_Message_Ptr msg = instance.getMsgFactory().create();

	 TestSt s;
	 s.write( msg );
	 s.read( msg );
	 s.Assert();
	 }
	//shutdown_BT_Log_Cxx(  );
	return 0;
}

