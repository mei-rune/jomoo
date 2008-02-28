// TCP_Scan.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "communication/TCPScan.H"


void TCP_ConnectedHandler( int result ,u_long ip , u_short port )
{
	switch( result )
	{
	case Tcp_success:
		std::cout << port << "\t\t" << "��" << std::endl;
		break;
	//case Tcp_error:
	//	std::cout << port << "\t\t" << "�ر�" << std::endl;
	//	break;
	//default:
	//	std::cout << port << "\t\t" << "��ʱ" << std::endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if( argc < 4 )
	{
		std::cout << "��������" << std::endl;
		std::cout << argv[0] << " ��ַ ��ʼ�˿� �����˿�" << std::endl;
		//std::cout << "ע�⣬�˿��������ܳ�256��" << std::endl;
		return -1;

	}
	init_TCPack( );

	TCPackPtr ptr = createTCPack();
	setTCPConnectedHandler(  ptr ,TCP_ConnectedHandler );

	int s = atoi( argv[2] );
	int e = atoi( argv[ 3 ] );
	//if( ( e - s ) > 256 )
	//{
	//	std::cout << "ע�⣬�˿��������ܳ�256��" << std::endl;
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

