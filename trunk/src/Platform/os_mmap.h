

#ifndef OS_MMAP_H
#define OS_MMAP_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include <errno.h>
#include "os.h"
#include <tchar.h>
#include "os_string.h"


#if defined (JOMOO_LACKS_SYS_MMAN_H) && !defined (JOMOO_WIN32)
#  define PROT_READ 0
#  define PROT_WRITE 0
#  define PROT_EXEC 0
#  define PROT_NONE 0
#  define PROT_RDWR 0
#  define MAP_PRIVATE 0
#  define MAP_SHARED 0
#  define MAP_FIXED 0
#elif defined (JOMOO_WIN32)
   // These two may be used for internal flags soon:
#  define MAP_PRIVATE 1
#  define MAP_SHARED  2
#  define MAP_FIXED   4
   // MMAP БъзЈ
#  define PROT_READ PAGE_READONLY
#  define PROT_WRITE PAGE_READWRITE
#  define PROT_RDWR PAGE_READWRITE
/* 
PAGE_WRITECOPY
PAGE_EXECUTE
PAGE_EXECUTE_READ
PAGE_EXECUTE_READWRITE
PAGE_EXECUTE_WRITECOPY
PAGE_GUARD
PAGE_NOACCESS
PAGE_NOCACHE  */
#endif 

# if !defined (JOMOO_MAP_PRIVATE)
#   define JOMOO_MAP_PRIVATE MAP_PRIVATE
# endif /* ! ACE_MAP_PRIVATE */

# if !defined (JOMOO_MAP_SHARED)
#   define JOMOO_MAP_SHARED MAP_SHARED
# endif /* ! ACE_MAP_SHARED */

# if !defined (JOMOO_MAP_FIXED)
#   define JOMOO_MAP_FIXED MAP_FIXED
# endif /* ! ACE_MAP_FIXED */

#if !defined (PROT_RDWR)
#  define PROT_RDWR (PROT_READ|PROT_WRITE)
#endif /* PROT_RDWR */

# if defined (JOMOO_WIN32)
    // Needed to map calls to NT transparently.
#   define MS_ASYNC 0
#   define MS_INVALIDATE 0
# endif /* ACE_WIN32 */

# if !defined (MS_SYNC)
#   define MS_SYNC 0x0
# endif /* !MS_SYNC */


namespace OS
{
  OS_INLINE
  int madvise (void* addr,
               size_t len,
               int map_advice);

  OS_INLINE
  void *mmap (void *addr,
              size_t len,
              int prot,
              int flags,
              JOMOO_HANDLE handle,
              off_t off ,
              JOMOO_HANDLE& file_mapping,
              LPSECURITY_ATTRIBUTES sa = 0,
              const tchar *file_mapping_name = 0);

  OS_INLINE
  int mprotect (void *addr,
                size_t len,
                int prot);

  OS_INLINE
  int msync (void *addr,
             size_t len,
             int sync);

  OS_INLINE
  int munmap (void *addr,
              size_t len);

  OS_INLINE
  JOMOO_HANDLE shm_open (const tchar *filename,
	  int prot,
	  int flags,
	  LPSECURITY_ATTRIBUTES sa = 0);

  OS_INLINE
  int shm_unlink (const tchar *path);

# if defined (OS_HAS_INLINED)
#   include "OS_mmap.inl"
# endif /* OS_HAS_INLINED */

};



#endif // OS_MMAP_H