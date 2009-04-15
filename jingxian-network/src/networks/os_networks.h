

# ifndef _OS_NETWORKS_H
# define _OS_NETWORKS_H

# include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

# include "Winsock2.h"
# include "Mswsock.h"

typedef WSABUF iovec;

# ifndef ___iopack___
# define ___iopack___
 typedef TRANSMIT_PACKETS_ELEMENT iopack;
# endif // ___iopack___

 # ifndef ___iofile___
# define ___iopack___
 typedef TRANSMIT_FILE_BUFFERS io_file_buf;
# endif // ___iopack___

#endif // _OS_NETWORKS_H