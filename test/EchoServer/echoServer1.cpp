// HelloServer.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <list>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include "networks/socket/tcp_server.h"
#include "base/threading/thread.h"


class session;

typedef boost::shared_ptr<session> sessionPtr;

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

class session : _thread thread::Runnable
{
public:
	session( session_manager& manager )
		: manager_( manager )
	{
	}

	void Start()
	{
		_stoped = false;
		thread_.reset( new _thread thread( *this, "test" ) );
	}

	void Stop()
	{
		_stoped = true;
		if( 0 != thread_.get() )
			thread_->join();
	}

	void run()
	{
		TIMEVAL timeout;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		char buf[1024];

		while(! manager_.stoped && !_stoped )
		{
			if( !socket_.socket().poll( timeout, select_mode::select_read ) )
				continue;
			ssize_t size = socket_.recv( buf, 1024 );
			if( 0 >= size )
				break;

			if(! socket_.send_n( buf, size ) )
				break;
		}
		
		std::cout << "来自" << socket_.remote_addr() << "的连接断开,剩余" << manager_.sessions.size() - 1 << "个连接!" << std::endl;
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
	std::auto_ptr< _thread thread  > thread_;
};

int main(int argc, tchar* argv[])
{
	_networks base_socket::initsocket();
	_networks tcp_server srv;

	if( !srv.is_good() )
	{
		std::cout << "创建socket失败 - " << lastError() << "!" << std::endl;
		return -1;
	}

	inet_address addr( "0.0.0.0", ( u_short )30000 );

	if( argc >= 2 )
		addr.ip( argv[ 1] );
	if( argc >= 3 )
		addr.port( argv[ 2 ] );

	if( !srv.bind( addr ) )
	{
		std::cout << "绑定到 " << addr << " 失败 - " << lastError() << "!" << std::endl;
		return -1;
	}

	if( !srv.listen() )
	{
		std::cout << "监听 " << addr << " 失败!" << std::endl;
		return -1;
	}
	
	std::cout << "监听 " << addr << " 成功!" << std::endl;

	session_manager manager;
	while( 1 )
	{
		sessionPtr p( new session( manager ) );
		if( !srv.accept( p->socket_ ) )
			continue;

		p->Start();
		manager.sessions.push_back( p );
		
		std::cout << "接收来自" << socket_.remote_addr() << "的连接断开,共有" << manager_.sessions.size() << "个连接!" << std::endl;
	}

	for( std::list<sessionPtr>::iterator it = manager.sessions.begin();
		it != manager.sessions.end();
		it ++ )
		(*it)->Stop();

	return 0;
}

