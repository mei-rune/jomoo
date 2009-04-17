// HelloServer.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <list>
#include <iostream>
#include "jomoo/networks/IOCPServe.h"


class EchoProtocol : IProtocol
{
public:
	void OnReceived(const ProtocolContext& context, Buffer data)
	{
		tcp::send( context.transport(), data );
	}

	void OnConnection(const ProtocolContext& context)
	{
		std::count << "INFO: [tcp] ���� " << context.transport().remoteAddr() << " ������!" << std::endl;
	}

	void OnDisconnection(const ProtocolContext& context, const Exception& reason)
	{
		std::count << "INFO: [tcp] ���� " << context.transport().remoteAddr() << " �Ͽ��� - "<< reason <<" !" << std::endl;
	}

	public void OnTimeout(ProtocolContext context)
	{
		context.transport().disconnection();
	}
};

int main(int argc, tchar* argv[])
{
	_networks base_socket::initsocket();
	
	inet_address addr( "0.0.0.0", ( u_short )30000 );

	IOCPServe tcpServer();
	ProtocolFactory<EchoProtocol> echoFactory( );

	tcpService.listenWith(addr, &echoFactory );
	return tcpServer.runForever();
}

