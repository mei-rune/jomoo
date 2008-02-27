// Server.cpp : 实现文件
//

#include "stdafx.h"
#include "DowLoadServer.h"
#include "Server.h"
#include "BOE/BT_Log_Cxx.cpp"


// CServer
CDownLoadServer::CDownLoadServer( );
: stop_( false )
{
}

int CDownLoadServer::start( int argc, char* argv[] )
{
	communicator__ = initializeCommunicator( argc, argv );

	if( communicator_.get() ==0 )
		return -1;

	init_BT_Log_Cxx(  );

	communicator_->setLogger( new BT_Log_Cxx( 0 ) );

	stop_ = 0;

	return 0;
}

void CDownLoadServer::stop()
{
	shutdown_BT_Log_Cxx(  );

}

void CDownLoadServer::run()
{
	while( !stop_ )
		communicator_->run( 1000 );
}


// CServer 消息处理程序
