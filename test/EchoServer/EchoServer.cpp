// HelloServer.cpp : 定义控制台应用程序的入口点。
//

#include "../BT_Server_Handler.H"
int main(int argc, tchar* argv[])
{
	_io BOE_Communicator_Ptr communicator = initializeCommunicator( );
	
	if( communicator.get() ==0 )
		return -1;
		_util PropertiesPtr config = createProperties( argc , argv );
		if( communicator->open( config ) != 0 )
			return -1;
	 //init_BT_Log_Cxx(  );

	 communicator->setLogger( new StdLogger( ) );

	_io BOE_Endpoint_Ptr endpoint = communicator->create( "tcp 127.0.0.1:30000" ) ;
	if( endpoint.get() == 0 )
		return -1;

	_io BOE_Acceptor_Ptr acceptor = endpoint->acceptor();
	_io BOE_Acceptor_Ptr acceptor1 = endpoint->acceptor();

	assert( acceptor.get() == acceptor1.get() );

	Accept_Handler handler;
	if( !acceptor->accept( handler, 0 ) )
		return -1;

	while( true )
		communicator->run( 1000 );

//	shutdown_BT_Log_Cxx(  );

	return 0;
}

