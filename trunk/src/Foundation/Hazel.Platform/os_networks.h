

# ifndef _OS_NETWORKS_H
# define _OS_NETWORKS_H

# include "config.h"

# if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* Hazel_LACKS_PRAGMA_ONCE */

# include "OS.H"
# include "Winsock2.h"
# include "Mswsock.h"

 typedef SOCKET Hazel_SOCK_HANDLE;
# define Hazel_NONBLOCK 1
 typedef unsigned long Hazel_SOCK_GROUP;

typedef WSABUF iovec;

# ifndef ___iopack___
# define ___iopack___
 typedef TRANSMIT_PACKETS_ELEMENT iopack;
# endif // ___iopack___

namespace OS
{

# if defined (OS_HAS_INLINED)
#   include "os_networks.inl"
# endif /* Hazel_HAS_INLINED_OSCALLS */

};





#endif // _OS_NETWORKS_H