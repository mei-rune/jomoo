// TCP_Scan.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "communication/TCPScan.H"


void TCP_ConnectedHandler( int result ,u_long ip , u_short port )
{
	switch( result )
	{
	case Tcp_success:
		std::cout << port << "\t\t" << "打开" << std::endl;
		break;
	//case Tcp_error:
	//	std::cout << port << "\t\t" << "关闭" << std::endl;
	//	break;
	//default:
	//	std::cout << port << "\t\t" << "超时" << std::endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if( argc < 4 )
	{
		std::cout << "参数错误。" << std::endl;
		std::cout << argv[0] << " 地址 开始端口 结束端口" << std::endl;
		//std::cout << "注意，端口总数不能超256个" << std::endl;
		return -1;

	}
	init_TCPack( );

	TCPackPtr ptr = createTCPack();
	setTCPConnectedHandler(  ptr ,TCP_ConnectedHandler );

	int s = atoi( argv[2] );
	int e = atoi( argv[ 3 ] );
	//if( ( e - s ) > 256 )
	//{
	//	std::cout << "注意，端口总数不能超256个" << std::endl;
	//	return -1;
	//}
	for( int j = s; j < e; )
	{
		int i = j;
		for( ; j < e && ( j - i  ) <= 255; j ++ )
		{
			sendTCPConnectPack_str( ptr, argv[1], j );
		}
		while( getTCPConnectStatus( ptr, 30000 ) == 0 )
		;
	}
	

	freeTCPack( ptr );
	shutdown_TCPack( );
	return 0;
}

