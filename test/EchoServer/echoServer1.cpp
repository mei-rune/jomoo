// HelloServer.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <list>
#include <boost/shared_ptr.hpp>
#include "networks/socket/tcp_socket.h"


class session;

typedef boost::shared_ptr<session> sessionPtr;

class session_manager
{
public:
	std::list< sessionPtr > sessions;
	bool stoped;
	_networks tcp_socket listenSocket;
};

class session
{
public:
	session( session_manager& manager )
		: manager_( manager )
	{
	}

	void svc()
	{
		while(! manager_.stoped )
		{
			
		}

		manager_.sessions.remove_if( std::bind1st( std::ptr_fun( &equels), this) );
	}

	static bool equels( session* s1, sessionPtr s2 )
	{
		return s1 == s2.get();
	}
private:
	_networks tcp_socket socket_;
	session_manager& manager_;
};

int main(int argc, tchar* argv[])
{



	return 0;
}

