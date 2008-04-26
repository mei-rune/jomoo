// HelloServer.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <list>
#include <iostream>
#include <boost/tr1/memory.hpp>
#include <boost/tr1/functional.hpp>
#include <jomoo/functional.hpp>
#include "jomoo/networks/sockets/tcp_server.h"
#include "jomoo/threading.hpp"


class session;

typedef std::tr1::shared_ptr<session> sessionPtr;

class session_manager
{
public:
	std::list< sessionPtr > sessions;
	bool stoped;
	session_manager()
		: stoped( false )
	{
	}
};

class session
{
public:
	session( session_manager& manager )
		: manager_( manager )
	{
	}

	void run()
	{
		TIMEVAL timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		char buf[1024];

		while(! manager_.stoped )
		{
			if( !socket_.socket().poll( timeout, select_mode::select_read ) )
				continue;
			ssize_t size = socket_.recv( buf, 1024 );
			if( 0 >= size )
				break;

			if(! socket_.send_n( buf, size ) )
				break;
		}
		
		std::cout << "����" << socket_.remote_addr() << "�����ӶϿ�,ʣ��" << manager_.sessions.size() - 1 << "������!" << std::endl;

		cleanup();
	}

	void cleanup()
	{
		
		manager_.sessions.remove_if( std::bind1st( std::ptr_fun( &equels), this) );		
	}

	static bool equels( session* s1, sessionPtr s2 )
	{
		return s1 == s2.get();
	}

	_networks tcp_client socket_;
private:
	bool _stoped;
	session_manager& manager_;
};

int main(int argc, tchar* argv[])
{
	_networks base_socket::initsocket();
	_networks tcp_server srv;

	if( !srv.is_good() )
	{
		std::cout << "����socketʧ�� - " << lastError() << "!" << std::endl;
		return -1;
	}

	inet_address addr( "0.0.0.0", ( u_short )30000 );

	if( argc >= 2 )
		addr.ip( argv[ 1] );
	if( argc >= 3 )
		addr.port( argv[ 2 ] );

	if( !srv.bind( addr ) )
	{
		std::cout << "�󶨵� " << addr << " ʧ�� - " << lastError() << "!" << std::endl;
		return -1;
	}

	if( !srv.listen() )
	{
		std::cout << "���� " << addr << " ʧ��!" << std::endl;
		return -1;
	}
	
	std::cout << "���� " << addr << " �ɹ�!" << std::endl;

	
	session_manager manager;
	while( 1 )
	{
		sessionPtr p( new session( manager ) );
		if( !srv.accept( p->socket_ ) )
			continue;

		manager.sessions.push_back( p );
		std::cout << "��������" << p->socket_.remote_addr() << "������,����" << manager.sessions.size() << "������!" << std::endl;

		_jomoo_thread create_thread( _jomoo mem_fun( &session::run), p , "aa" );
		//boost::thread t( std::tr1::function< void(void) >( &session::run, p ) );

	}

	//for( std::list<sessionPtr>::iterator it = manager.sessions.begin();
	//	it != manager.sessions.end();
	//	it ++ )
	//	(*it)->Stop();

	return 0;
}

