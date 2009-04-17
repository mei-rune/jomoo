
#ifndef tcp_server_h
#define tcp_server_h

#include "jingxian/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "jingxian/networks/inet_address.h"
# include "jingxian/networks/sockets/tcp_client.h"

_jingxian_begin

class tcp_server
{
public:

  tcp_server (void);

  ~tcp_server (void);

  /**
   * 取得socket对象
   */
  base_socket& socket();

  /**
   * 取得socket对象
   */
  const base_socket& socket() const;

  /**
   * 取得监听的端口
   */
  const inet_address& bind_addr() const;

  /**
   * socket是否有效
   */
  bool is_good() const;

  /**
   * 绑定到指定的端口
   */
  bool bind( const inet_address& addr);

  /**
   * 启动监听
   */
  bool listen( int backlog = SOMAXCONN );

  /**
   * 获取一个连接
   */
  bool accept( tcp_client& accepted );

  /**
   * 异步获取一个连接
   */
  bool accept( tcp_client& accepted
						, void* data_buffer
						, size_t data_len
						, size_t local_addr_len
						, size_t remote_addr_len
						, OVERLAPPED& overlapped);

  void swap( tcp_server& r);

  /**
   * 返回一个人可读的字符串
   */
  const tstring& toString() const;

private:
	NOCOPY( tcp_server );
	inet_address bind_addr_;
	base_socket socket_;
	mutable tstring toString_;
};


inline tostream& operator<<( tostream& target, const tcp_server& server )
{
  if( server.is_good() )
  {
	  target << _T("tcp_server[ ")
		  <<  server.socket().get_handle() 
		  << _T(":") << server.bind_addr()
		  << _T("]" );
  }
  else
  {
	  target << _T("tcp_client[ no listen ]" );
  }
  
  return target;
}

#if defined (OS_HAS_INLINED)
#include "jingxian/networks/sockets/tcp_server.inl"
#endif

_jingxian_end

#endif /* tcp_server_h */
