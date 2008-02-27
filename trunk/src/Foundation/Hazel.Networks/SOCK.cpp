// IPC_SAP.cpp,v 4.33 2003/11/01 11:15:13 dhinton Exp

#include "hazel_sap.h"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

#if defined (Hazel_LACKS_INLINE_FUNCTIONS)
#include "hazel_sap.inl"
#endif


hazel_sap::hazel_sap (void)
  : handle_ (INVALID_SOCKET )
{
}

int
hazel_sap::enable (int value) const
{
  switch (value)
    {
    case Hazel_NONBLOCK:
      {
        u_long nonblock = 1;
		return ::ioctlsocket (this->handle_,
                              FIONBIO,
                              &nonblock);
      }
    default:
      return (-1);
    }
}

int
hazel_sap::disable (int value) const
{
  switch (value)
    {
    case Hazel_NONBLOCK:
      {
        u_long nonblock = 0;
        return ioctlsocket (this->handle_,
                              FIONBIO,
                              &nonblock);
      }
    default:
       return (-1);
    }
}


int
hazel_sap::get_remote_addr (Hazel_INET_Addr &sa) const
{
  int len = sa.get_size ();
  sockaddr *addr = reinterpret_cast< sockaddr * >( sa.get_addr ());

  if ( getpeername (this->get_handle (),
                           addr,
                           &len) == -1)
    return -1;
  
  sa.set_size (len);
  return 0;
}

int
hazel_sap::get_local_addr (Hazel_INET_Addr &sa) const
{
  int len = sa.get_size ();
  sockaddr *addr = reinterpret_cast< sockaddr * >( sa.get_addr ());

  if ( getsockname (this->get_handle (),
                           addr,
                           &len) == -1)
    return -1;

  sa.set_size (len);
  return 0;
}

// Close down a hazel_sap.

int
hazel_sap::close (void)
{
  int result = 0;

  if (this->get_handle () != INVALID_SOCKET )
    {
      result = closesocket (this->get_handle ());
      this->set_handle (INVALID_SOCKET );
    }
  return result;
}

int
hazel_sap::open (int type, 
                int protocol_family, 
                int protocol,
                int reuse_addr)
{
int one = 1;

  this->set_handle (socket (protocol_family,
                                    type,
                                    protocol));

  if (this->get_handle () == INVALID_SOCKET )
    return -1;
  else if (protocol_family != PF_UNIX 
           && reuse_addr 
           && this->set_option (SOL_SOCKET,
                                SO_REUSEADDR,
                                &one,
                                sizeof one) == -1)
    {
      this->close ();
      return -1;
    }
  return 0;
}

hazel_sap::hazel_sap (int type, 
                    int protocol_family, 
                    int protocol,
                    int reuse_addr)
{
  if (this->open (type,
                  protocol_family, 
                  protocol,
                  reuse_addr) == -1)
				  ThrowException1( NetworkException, ",创建socket出错!" );
}

int
hazel_sap::open (int type, 
                int protocol_family, 
                int protocol,
                WSAPROTOCOL_INFO *protocolinfo,
                hazel_sap_GROUP g,
                u_long flags,
                int reuse_addr)
{
  this->set_handle (::WSASocket (protocol_family,
                                    type,
                                    protocol,
                                    protocolinfo,
                                    g,
                                    flags));
  int one = 1;

  if (this->get_handle () == INVALID_SOCKET )
    return -1;
  else if (reuse_addr 
           && this->set_option (SOL_SOCKET,
                                SO_REUSEADDR,
                                &one,
                                sizeof one) == -1)
    {
      this->close ();
	return -1;
    }
  else
    return 0;
}
      
hazel_sap::hazel_sap (int type, 
                    int protocol_family, 
                    int protocol,
                    WSAPROTOCOL_INFO *protocolinfo,
                    hazel_sap_GROUP g,
                    u_long flags,
                    int reuse_addr)
{
  if (this->open (type,
                  protocol_family,
                  protocol,
                  protocolinfo,
                  g,
                  flags,
                  reuse_addr) == -1)
				  ThrowException1( NetworkException, ",创建socket出错!" );
}

int hazel_sap::initsocket()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		return -1;
	}

	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */

	if ( LOBYTE( wsaData.wVersion ) != 2 ||
		HIBYTE( wsaData.wVersion ) != 2 ) {
			/* Tell the user that we could not find a usable */
			/* WinSock DLL.                                  */
			WSACleanup( );
			return -1; 
		}
		return 0;
}

void hazel_sap::shutdownsock()
{
	WSACleanup( );
}

_networks_end