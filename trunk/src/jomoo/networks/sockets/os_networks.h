

# ifndef _OS_NETWORKS_H
# define _OS_NETWORKS_H

# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

# include "jomoo/platform/os.H"
# include "Winsock2.h"
# include "Mswsock.h"

 typedef SOCKET JOMOO_SOCK_HANDLE;
 typedef unsigned long JOMOO_SOCK_GROUP;

typedef WSABUF iovec;

# ifndef ___iopack___
# define ___iopack___
 typedef TRANSMIT_PACKETS_ELEMENT iopack;
# endif // ___iopack___

 # ifndef ___iofile___
# define ___iopack___
 typedef TRANSMIT_FILE_BUFFERS io_file_buf;
# endif // ___iopack___

namespace OS
{

# if defined (JOMOO_INLINE_FUNCTIONS)
#   include "os_networks.inl"
# endif /* JOMOO_HAS_INLINED_OSCALLS */

};





#endif // _OS_NETWORKS_H