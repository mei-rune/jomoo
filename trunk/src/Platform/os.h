


#ifndef _os_h_
#define _os_h_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#ifndef _critical_section_
typedef CRITICAL_SECTION critical_section;
#endif // critical_section

#ifndef _JOMOO_HANDLE_
typedef HANDLE JOMOO_HANDLE;
#endif // _JOMOO_HANDLE_

#ifndef JOMOO_INVALID_HANDLE
#define JOMOO_INVALID_HANDLE NULL
#endif // JOMOO_INVALID_HANDLE_VALUE

#ifndef JOMOO_INVALID_HANDLE_VALUE
#define JOMOO_INVALID_HANDLE_VALUE INVALID_HANDLE_VALUE
#endif // JOMOO_INVALID_HANDLE_VALUE

typedef int ssize_t;
typedef OVERLAPPED JOMOO_OVERLAPPED ;


namespace OS
{
	inline
		bool close_handle( JOMOO_HANDLE &handle );

	inline
		bool dup_handle( JOMOO_HANDLE hSourceProcessHandle,
					JOMOO_HANDLE hSourceHandle,
					JOMOO_HANDLE hTargetProcessHandle,
					HANDLE& lpTargetHandle,
					DWORD dwDesiredAccess,
					bool bInheritHandle,
					DWORD dwOptions );

	inline
		bool get_handle_info( JOMOO_HANDLE hObject,DWORD& dwFlags );


	inline
		bool get_handle_info( JOMOO_HANDLE hObject, DWORD dwMask, DWORD dwFlags );


	inline
		long InterlockedIncrement( long& v );
	inline
		long InterlockedDecrement( long& v );

# if defined (OS_HAS_INLINED)
#   include "os.inl"
# endif /* JOMOO_HAS_INLINED_OSCALLS */

};



#endif // _os_h_

