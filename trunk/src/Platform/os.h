


#ifndef _os_h_
#define _os_h_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "windows.h"

typedef CRITICAL_SECTION critical_section;

typedef HANDLE JOMOO_HANDLE;

#define JOMOO_INVALID_HANDLE NULL

#define JOMOO_INVALID_HANDLE_VALUE INVALID_HANDLE_VALUE

typedef int ssize_t;
typedef OVERLAPPED JOMOO_OVERLAPPED ;

namespace OS
{
	OS_INLINE
		bool close_handle( JOMOO_HANDLE &handle );

	OS_INLINE
		bool dup_handle( JOMOO_HANDLE hSourceProcessHandle,
					JOMOO_HANDLE hSourceHandle,
					JOMOO_HANDLE hTargetProcessHandle,
					HANDLE& lpTargetHandle,
					DWORD dwDesiredAccess,
					bool bInheritHandle,
					DWORD dwOptions );

	OS_INLINE
		bool get_handle_info( JOMOO_HANDLE hObject,DWORD& dwFlags );


	OS_INLINE
		bool get_handle_info( JOMOO_HANDLE hObject, DWORD dwMask, DWORD dwFlags );


	OS_INLINE
		long InterlockedIncrement( long& v );
	OS_INLINE
		long InterlockedDecrement( long& v );

# if defined (OS_HAS_INLINED)
#   include "os.inl"
# endif /* OS_HAS_INLINED */

};



#endif // _os_h_

