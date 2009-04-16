
#ifndef _protocol_h_
#define _protocol_h_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "Winsock2.h"
# include "Mswsock.h"
# include "inet_address.h"

typedef WSABUF iovec;

# ifndef ___iopack___
# define ___iopack___
 typedef TRANSMIT_PACKETS_ELEMENT iopack;
# endif // ___iopack___

 # ifndef ___iofile___
# define ___iopack___
 typedef TRANSMIT_FILE_BUFFERS io_file_buf;
# endif // ___iopack___


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
  const string& toString() const;

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
  mutable string toString_;

public:
	static LPFN_TRANSMITFILE __transmitfile;
	static LPFN_ACCEPTEX __acceptex;
	static LPFN_TRANSMITPACKETS __transmitpackets;
	static LPFN_CONNECTEX __connectex;
	static LPFN_DISCONNECTEX __disconnectex;
	static LPFN_GETACCEPTEXSOCKADDRS __getacceptexsockaddrs;
};

inline tostream& operator<<( tostream& target, const base_socket& s )
{
  if( INVALID_SOCKET == s.get_handle())
  {
	  target << _T("INVALID_SOCKET" );
  }
  else
  {
	  target << s.get_handle() ;
  }
  
  return target;
}

#if defined (JOMOO_HAS_INLINED)
#include "base_socket.inl"
#endif /* JOMOO_HAS_INLINED */

_networks_end

#endif /* JOMOO_sap_H */
