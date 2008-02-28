


#ifndef _os_h_
#define _os_h_

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#ifndef _critical_section_
typedef CRITICAL_SECTION critical_section;
#endif // critical_section

#ifndef _Hazel_HANDLE_
typedef HANDLE Hazel_HANDLE;
#endif // _Hazel_HANDLE_

#ifndef Hazel_INVALID_HANDLE
#define Hazel_INVALID_HANDLE NULL
#endif // Hazel_INVALID_HANDLE_VALUE

#ifndef Hazel_INVALID_HANDLE_VALUE
#define Hazel_INVALID_HANDLE_VALUE INVALID_HANDLE_VALUE
#endif // Hazel_INVALID_HANDLE_VALUE

typedef int ssize_t;
typedef OVERLAPPED Hazel_OVERLAPPED ;


namespace OS
{
	Hazel_NAMESPACE_INLINE_FUNCTION
		bool close_handle( Hazel_HANDLE &handle );

	Hazel_NAMESPACE_INLINE_FUNCTION
		bool dup_handle( Hazel_HANDLE hSourceProcessHandle,
					Hazel_HANDLE hSourceHandle,
					Hazel_HANDLE hTargetProcessHandle,
					HANDLE& lpTargetHandle,
					DWORD dwDesiredAccess,
					bool bInheritHandle,
					DWORD dwOptions );

	Hazel_NAMESPACE_INLINE_FUNCTION
		bool get_handle_info( Hazel_HANDLE hObject,DWORD& dwFlags );


	Hazel_NAMESPACE_INLINE_FUNCTION
		bool get_handle_info( Hazel_HANDLE hObject, DWORD dwMask, DWORD dwFlags );


	Hazel_NAMESPACE_INLINE_FUNCTION
		long InterlockedIncrement( long& v );
	Hazel_NAMESPACE_INLINE_FUNCTION
		long InterlockedDecrement( long& v );

# if defined (OS_HAS_INLINED)
#   include "os.inl"
# endif /* Hazel_HAS_INLINED_OSCALLS */

};



#endif // _os_h_

