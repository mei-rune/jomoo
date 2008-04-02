

#ifndef JOMOO_sap_H
#define JOMOO_sap_H

#include "jomoo/config.h"

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
   * �Ƿ񴴽���Ч
   */
  bool is_good() const;

  /**
   * ����˫�����ڲ�ֵ
   */
  void swap( base_socket& r );

  /**
   * ȡ��socket����
   */
  SOCKET get_handle (void) const;

  /**
   * ����socket����
   */
  void set_handle (SOCKET handle);

  /**
   * ����socketѡ����setsockopt
   */
  bool set_option (int level,
                  int option,
                  void *optval,
                  int optlen) const;
  /**
   * ���socketѡ����getsockopt
   */
  bool get_option (int level,
                  int option,
                  void *optval,
                  int *optlen) const;

  /**
   * �ر�socket
   */
  void close (void);
  
  /**
   * �жϲ��ȴ�ֱ��socket���Խ��ж�(д)�������������ʱ
   * @params[ in ] timval ��ʱʱ��
   * @params[ in ] mode �жϵĵĲ������ͣ����select_modeö��
   * @return ���Բ�������true
   */
  bool poll( const TIMEVAL& timeval, int select_mode);

  /**
   * ����һ���˿ɶ����ַ���
   */
  const tstring& toString() const;

  /**
   * ��ʼ��socket����
   */
  static bool initsocket();

  /**
   * �ر�socket����
   */
  static void shutdownsock();

  base_socket (void);

  base_socket ( int protocol_family,
			int type,
            int protocol = 0,
            int reuse_addr = 0);

  base_socket ( int protocol_family,
			int type,
            int protocol,
            WSAPROTOCOL_INFO *protocolinfo,
            JOMOO_SOCK_GROUP g,
             u_long flags,
            int reuse_addr);

  /**
   * ����socket��ѡ��
   * @params[ in ] value ��ȡֵ���ioctlsocket
   */
  bool enable (int value);

  /**
   * ����socket��ѡ��
   * @params[ in ] value ��ȡֵ���ioctlsocket
   */
  bool disable (int value);

  bool open (int protocol_family = AF_INET,
			int type = SOCK_STREAM,
            int protocol = IPPROTO_TCP,
            int reuse_addr = 0 );

  bool open (int protocol_family,
			int type,
            int protocol,
            WSAPROTOCOL_INFO *protocolinfo,
            JOMOO_SOCK_GROUP g,
            u_long flags,
            int reuse_addr);

private:
  DECLARE_NO_COPY_CLASS( base_socket );

  SOCKET handle_;
  mutable tstring toString_;

public:
	static LPFN_TRANSMITFILE __transmitfile;
	static LPFN_ACCEPTEX __acceptex;
	static LPFN_TRANSMITPACKETS __transmitpackets;
	static LPFN_CONNECTEX __connectex;
	static LPFN_DISCONNECTEX __disconnectex;
	static LPFN_GETACCEPTEXSOCKADDRS __getacceptexsockaddrs;
};

#if defined (JOMOO_INLINE_FUNCTIONS)
#include "base_socket.inl"
#endif /* JOMOO_INLINE_FUNCTIONS */

_networks_end

#endif /* JOMOO_sap_H */
