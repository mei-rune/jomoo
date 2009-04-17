
#ifndef tcp_client_h
#define tcp_client_h

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "jingxian/networks/inet_address.h"
# include "jingxian/networks/sockets/base_socket.h"

_jingxian_begin

class tcp_client
{
public:
  tcp_client (void);

  ~tcp_client (void);

  /**
   * 是否可以读数据
   */
  bool readable();

  /**
   * 是否可以写数据
   */
  bool writable();

  /**
   * 设置socket为阻塞或非阻塞
   */
  void blocking(bool val);

  /**
   * 取得本socket是阻塞还是非阻塞
   */
  bool blocking() const;
  
  /**
   * 取得本机地址
   */
  const inet_address& local_addr () const;

  /**
   * 取得远程机地址
   */
  const inet_address& remote_addr () const;

  /**
   * 取得socket对象
   */
  base_socket& socket();
	
  /**
   * 取得socket对象
   */
  const base_socket& socket() const;

  /**
   * 将r与本对象的值交换
   */
  void swap( tcp_client& r );

  /**
   * socket是否有效
   */
  bool is_good() const;

  /**
   * 读数据
   * @param[ in,out ] buf 数据缓冲区
   * @param[ in ] n 数据缓冲区大小
   * @param[ in ] flags 用于控制本函数的行为
   * @return 成功返回读取的字节数，发生错误返回SOCKET_ERROR
   */
  ssize_t recv ( void *buf, size_t n, int flags = 0 );

  /**
   * 发送数据
   * @param[ in,out ] buf 数据缓冲区
   * @param[ in ] n 数据缓冲区大小
   * @param[ in ] flags 用于控制本函数的行为
   * @return 成功返回发送的字节数，发生错误返回SOCKET_ERROR
   */
  ssize_t send (const void *buf, size_t n, int flags = 0 );

  /**
   * 读数据
   * @param[ in,out ] iov 数据缓冲区数组
   * @param[ in ] n 数据缓冲区数组长度
   * @return 成功返回读取的字节数，发生错误返回SOCKET_ERROR
   */
  ssize_t recvv (iovec* iov, size_t n );

  /**
   * 发送数据
   * @param[ in ] iov 数据缓冲区数组
   * @param[ in ] n 数据缓冲区数组长度
   * @return 成功返回发送的字节数，发生错误返回SOCKET_ERROR
   */
  ssize_t sendv (const iovec* iov, size_t n );

  /**
   * 读数据,与recv不同的是它必须在读到length指定的长度后才返回
   * @param[ in,out ] buf 数据缓冲区
   * @param[ in ] n 数据缓冲区大小
   */
  bool recv_n( char* buf, size_t length);
  
  /**
   * 发送数据,与send不同的是它必须在读到length指定的长度后才返回
   * @param[ in,out ] buf 数据缓冲区
   * @param[ in ] n 数据缓冲区大小
   */
  bool send_n( const char* buf, size_t length);

  /**
   * 读数据,与recvv不同的是它必须在读到length指定的长度后才返回
   * @param[ in,out ] iov 数据缓冲区数组
   * @param[ in ] n 数据缓冲区数组长度
   */
  bool recvv_n( iovec* wsaBuf, size_t size);

  /**
   * 发送数据,与sendv不同的是它必须在读到length指定的长度后才返回
   * @param[ in ] iov 数据缓冲区数组
   * @param[ in ] n 数据缓冲区数组长度
   */
  bool sendv_n( const iovec* wsaBuf, size_t size);

  /**
   * 异步方式读取数据
   * @param[ in,out ] buf 数据缓冲区
   * @param[ in ] n 数据缓冲区大小
   * @param[ in ] overlapped 重叠IO数据指针
   */
  bool recv (void *buf, size_t n,
                OVERLAPPED& overlapped);
  /**
   * 异步方式发送数据
   * @param[ in,out ] buf 数据缓冲区
   * @param[ in ] n 数据缓冲区大小
   * @param[ in ] overlapped 重叠IO数据指针
   */
  bool send (const void *buf, size_t n,
                OVERLAPPED& overlapped);

  /**
   * 异步方式读取数据
   * @param[ in,out ] iov 数据缓冲区数组
   * @param[ in ] n 数据缓冲区数组长度
   * @param[ in ] overlapped 重叠IO数据指针
   */
  bool recvv (iovec* iov, size_t n,
                OVERLAPPED& overlapped);

  /**
   * 异步方式发送数据
   * @param[ in ] iov 数据缓冲区数组
   * @param[ in ] n 数据缓冲区数组长度
   * @param[ in ] overlapped 重叠IO数据指针
   */
  bool sendv (const iovec* iov, size_t n,
                 OVERLAPPED& overlapped);

  /**
   * 发送一个文件
   */
  bool transmit (const iopack* iov, size_t n );

  /**
   * 发送一个文件
   */
  bool transmit (const iopack* iov, size_t n
                , OVERLAPPED& overlapped);

  /**
   * 发送一个文件
   */
  bool transmit ( HANDLE hFile
				, size_t nNumberOfBytesToWrite
				, size_t nNumberOfBytesPerSend
				, io_file_buf* transmitBuffers );
  /**
   * 发送一个文件
   */
  bool transmit ( HANDLE hFile
				, size_t nNumberOfBytesToWrite
				, size_t nNumberOfBytesPerSend
				, io_file_buf* transmitBuffers
                , OVERLAPPED& overlapped);

  /**
   * 连接到远程主机
   */
  bool connect( const inet_address& addr );

  /**
   * 异步连接到远程主机
   */
  bool connect( const inet_address& addr, OVERLAPPED& overlapped );

  /**
   * 异步连接到远程主机，并发送数据（仅用于 ATM ）
   */
  bool tcp_client::connect( const inet_address& addr
									  , const void* send_buffer
									  , size_t send_data_len
									  , OVERLAPPED& overlapped );

private:
  NOCOPY( tcp_client );
  inet_address local_addr_;
  inet_address remote_addr_;
  bool blocking_;
  base_socket socket_;
};

inline tostream& operator<<( tostream& target, const tcp_client& client )
{
  if( client.is_good() )
  {
	  target << _T("tcp_client[ ")
		  <<  client.socket().get_handle() 
		  << _T(":") << client.local_addr()
		  << _T("<==>")<< client.remote_addr()
		  << _T("|blocking=") << client.blocking()
		  << _T("]" );
  }
  else
  {
	  target << _T("tcp_client[ disconnect ]" );
  }
  
  return target;
}

#if defined (OS_HAS_INLINED)
#include "jingxian/networks/sockets/tcp_client.inl"
#endif

_jingxian_end

#endif /* tcp_client_h */
