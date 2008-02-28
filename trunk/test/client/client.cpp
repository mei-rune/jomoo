// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BOE\IO\IO.h"
#include "BOE/BT_Log_Cxx.cpp"
#define MAX_SIZE 10

char  sbuf[] = "1234567890";

class Peer_Handler : public _io BOE_Transport_Handler
{
public:

	void open( _io BOE_Transport_Ptr connect )
	{
		connect_ = connect;
		if( ! connect->write( *this, sbuf, 10 , 0 ) )
			close();
	}

	void close( )
	{
		connect_.reset( ( _io BOE_Transport*) 0 ) ;
		delete this;
	}

	virtual void onRead( _io BOE_Read_Result& result)
	{
		if( !result.success() || result.bytes_to_transferred() == 0 )
			return close();
		if( ! result.transport().write( *this, buf, result.bytes_to_transferred(), 0 ) )
			close();
	}

	virtual void onReadArray( _io BOE_Read_Array_Result& result )
	{
		if( !result.success() || result.bytes_to_transferred() == 0 )
			return close();
	}

	virtual void onWrite( _io BOE_Write_Result& result)
	{
		if( !result.success() || result.bytes_to_transferred() == 0 )
			return close();
		std::vector< char > tmp( result.bytes_to_transferred() + 1 );
		memcpy( &tmp[0], result.buffer(),result.bytes_to_transferred() );
		buf[result.bytes_to_transferred() ] = 0;
		std::cout << &tmp[0] ;
		if( ! result.transport().read( *this, buf, MAX_SIZE, 0 ) )
			close();
	}

	virtual void onTransmit(BOE_Transmit_Result& result )
	{
		if( !result.success() || result.bytes_to_transferred() == 0 )
			return close();
	}

	const tstring& toString() const
	{
		return toString_;
	}
private:
	tstring toString_;

	BOE_Transport_Ptr connect_;

	char buf[ MAX_SIZE ];
};

class Connect_Handler : public BOE_Connect_Handler
{
public:

	Connect_Handler()
	{
		toString_ = "Connect";
		count_ =0;
	}

	virtual void onConnect(BOE_Connect_Result& result)
	{
		BOE_Transport_Ptr channel = result.new_channel();
		
		Peer_Handler* peer_handler = new Peer_Handler;
		peer_handler->open( channel );

		//count_ ++;
		//if( count_ < 10 )
		//result.connector().connect( *this, 0 ) ;
	}

	const tstring& toString() const
	{
		return toString_;
	}
private:
	tstring toString_;
	int count_;
};


int main(int argc, tchar* argv[])
{
	_io BOE_Communicator_Ptr communicator = initializeCommunicator( argc, argv );
	
	if( communicator.get() ==0 )
		return -1;

	 init_BT_Log_Cxx(  );

	 communicator->setLogger( new BT_Log_Cxx( 0 ) );

	_io BOE_Endpoint_Ptr endpoint = communicator->create( "tcp 127.0.0.1:30000" ) ;
	if( endpoint.get() == 0 )
		return -1;

	BOE_Connector_Ptr connector = endpoint->connector();

	Connect_Handler handler;
	if( !connector->connect( handler, 0 ) )
		return -1;

	int i = 0 ;
	while( true )
		communicator->run( 1000 ), i ++;

	shutdown_BT_Log_Cxx(  );

	return 0;
}


