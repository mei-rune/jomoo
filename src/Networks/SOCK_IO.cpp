

#include "sock_io.h"
#include <vector>

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

#if defined (JOMOO_LACKS_INLINE_FUNCTIONS)
#include "JOMOO_socket.inl"
#endif /* JOMOO_LACKS_INLINE_FUNCTIONS */

ssize_t
JOMOO_socket::send (size_t n, ...) const
{
  va_list argp;
  int total_tuples = static_cast< int >( n) / 2;
  std::vector< iovec > iovp( total_tuples );

  va_start (argp, n);

  for (int i = 0; i < total_tuples; i++)
    {
      iovp[i].buf = va_arg (argp, char *);
      iovp[i].len = va_arg (argp, int);
    }

  ssize_t result = sendv ( &iovp[0],
                                  total_tuples);
  va_end (argp);
  return result;
}


ssize_t
JOMOO_socket::recv (size_t n, ...) const
{
	va_list argp;
	int total_tuples = static_cast< int >(n / 2);
	std::vector< iovec > iovp( total_tuples );
	va_start (argp, n);

	for (int i = 0; i < total_tuples; i++)
	{
		iovp[i].buf = va_arg (argp, char *);
		iovp[i].len = va_arg (argp, int);
	}

	ssize_t result = recvv ( &iovp[ 0 ],
		total_tuples);
	va_end (argp);
	return result;
}

_networks_end