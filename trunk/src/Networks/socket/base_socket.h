

#ifndef JOMOO_sap_H
#define JOMOO_sap_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "inet_address.h"
# include "os_networks.h"

_networks_begin

enum select_mode
{
	  select_read = 1
	, select_write = 2
	, select_error = 4
};

class base_socket
{
public:

  ~base_socket (void);

  /**
   * 是否创建有效
   */
  bool is_good() const;

  /**
   * 交换双方的内部值
   */
  void swap( base_socket& r );

  /**
   * 取得socket对象
   */
  SOCKET get_handle (void) const;

  /**
   * 设置socket对象
   */
  void set_handle (SOCKET handle);

  /**
   * 设置socket选项，请见setsockopt
   */
  int set_option (int level,
                  int option,
                  void *optval,
                  int optlen) const;
  /**
   * 获得socket选项，请见getsockopt
   */
  int get_option (int level,
                  int option,
                  void *optval,
                  int *optlen) const;

  /**
   * 关闭socket
   */
  void close (void);

  /**
   * 取得本机地址
   */
  const inet_address& local_addr () const;

  /**
   * 取得远程机地址
   */
  const inet_address& remote_addr () const;
  
  /**
   * 判断并等待直到socket可以进行读(写)操作，或出错，或超时
   * @params[ in ] timval 超时时间
   * @params[ in ] mode 判断的的操作类型，请见select_mode枚举
   * @return 可以操作返回true
   */
  bool poll( const TIMEVAL& timeval, int select_mode);

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

  static bool initsocket();

  static void shutdownsock();

protected:

  base_socket (void);

  base_socket (int type,
            int protocol_family,
            int protocol = 0,
            int reuse_addr = 0);

  base_socket (int type,
            int protocol_family,
            int protocol,
            WSAPROTOCOL_INFO *protocolinfo,
            JOMOO_SOCK_GROUP g,
             u_long flags,
            int reuse_addr);

  /**
   * 启动socket的选项
   * @params[ in ] value 可取值请见ioctlsocket
   */
  bool enable (int value);

  /**
   * 启动socket的选项
   * @params[ in ] value 可取值请见ioctlsocket
   */
  bool disable (int value);

private:
  DECLARE_NO_COPY_CLASS( base_socket );

  int open (int type = SOCK_STREAM,
            int protocol_family = AF_INET,
            int protocol = IPPROTO_TCP,
            int reuse_addr = 0 );

  int open (int type,
            int protocol_family,
            int protocol,
            WSAPROTOCOL_INFO *protocolinfo,
            JOMOO_SOCK_GROUP g,
            u_long flags,
            int reuse_addr);

  SOCKET handle_;
  bool blocking_;

protected:
  inet_address local_addr_;
  inet_address remote_addr_;
	static LPFN_TRANSMITFILE _transmitfile;
	static LPFN_ACCEPTEX _acceptex;
	static LPFN_TRANSMITPACKETS _transmitpackets;
	static LPFN_CONNECTEX _connectex;
	static LPFN_DISCONNECTEX _disconnectex;
	static LPFN_GETACCEPTEXSOCKADDRS _getacceptexsockaddrs;
};

#if !defined (JOMOO_LACKS_INLINE_FUNCTIONS)
#include "base_socket.inl"
#endif /* JOMOO_LACKS_INLINE_FUNCTIONS */

_networks_end

#endif /* JOMOO_sap_H */
