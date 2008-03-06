

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
  int set_option (int level,
                  int option,
                  void *optval,
                  int optlen) const;
  /**
   * ���socketѡ����getsockopt
   */
  int get_option (int level,
                  int option,
                  void *optval,
                  int *optlen) const;

  /**
   * �ر�socket
   */
  void close (void);

  /**
   * ȡ�ñ�����ַ
   */
  const inet_address& local_addr () const;

  /**
   * ȡ��Զ�̻���ַ
   */
  const inet_address& remote_addr () const;
  
  /**
   * �жϲ��ȴ�ֱ��socket���Խ��ж�(д)�������������ʱ
   * @params[ in ] timval ��ʱʱ��
   * @params[ in ] mode �жϵĵĲ������ͣ����select_modeö��
   * @return ���Բ�������true
   */
  bool poll( const TIMEVAL& timeval, int select_mode);

  /**
   * �Ƿ���Զ�����
   */
  bool readable();

  /**
   * �Ƿ����д����
   */
  bool writable();

  /**
   * ����socketΪ�����������
   */
  void blocking(bool val);

  /**
   * ȡ�ñ�socket���������Ƿ�����
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
   * ����socket��ѡ��
   * @params[ in ] value ��ȡֵ���ioctlsocket
   */
  bool enable (int value);

  /**
   * ����socket��ѡ��
   * @params[ in ] value ��ȡֵ���ioctlsocket
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
