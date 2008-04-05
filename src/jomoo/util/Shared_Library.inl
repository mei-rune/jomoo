
#include "Shared_Library.h"

#ifndef _Shared_Library_Cpp_
#define _Shared_Library_Cpp_

_jomoo_begin

inline shared_library::shared_library( const tchar* name ,int close_on_destruction )
: dll_handle_( NULL )
, close_on_destruction_( close_on_destruction )
, lpMsgBuf( 0 )
{
	if( !open( name,close_on_destruction ) )
	{
		if( error( ) != 0 )
		{
			tstring err = ( const char* )lpMsgBuf;
			LocalFree( lpMsgBuf );
			throw std::runtime_error( "打开动态库失败[" + err + "]" );
		}
		throw std::runtime_error( "打开动态库失败" );
	}
}


inline shared_library::shared_library( const tstring& name ,int close_on_destruction )
: dll_handle_( NULL )
, close_on_destruction_( close_on_destruction )
, lpMsgBuf( 0 )
{
	if( !open( name,close_on_destruction ) )
	{
		if( error( ) != 0 )
		{
			tstring err = ( const char* )lpMsgBuf;
			LocalFree( lpMsgBuf );
			throw std::runtime_error( "打开动态库失败[" + err + "]" );
		}
		throw std::runtime_error( "打开动态库失败" );
	}
}

inline shared_library::shared_library( int close_on_destruction )
: dll_handle_( NULL )
, close_on_destruction_( close_on_destruction )
, lpMsgBuf( 0 )
{
}

inline shared_library::~shared_library(void)
{
	close();
	if( lpMsgBuf != 0 )
		LocalFree( lpMsgBuf );
}

inline int shared_library::open( const tchar* name ,int close_on_destruction )
{
	dll_handle_ = LoadLibrary( name );
	if( dll_handle_ == NULL )
		return -1;
	close_on_destruction_ = close_on_destruction;
	return 0;
}

inline int shared_library::open( const tstring& name ,int close_on_destruction )
{
	dll_handle_ = LoadLibrary( name.c_str() );
	if( dll_handle_ == NULL )
		return -1;
	close_on_destruction_ = close_on_destruction;
	return 0;
}


inline int shared_library::close (void)
{
	if( close_on_destruction_ == 0 )
		return 0;

	if( FreeLibrary( dll_handle_ ) )
		return 0;
	return -1;
}

inline void *shared_library::symbol (const tchar *symbol_name, int ignore_errors )
{
	if( dll_handle_ == NULL )
		return 0;

	return GetProcAddress( dll_handle_,symbol_name );
}

inline void *shared_library::symbol (const tstring& symbol_name, int ignore_errors )
{
	if( dll_handle_ == NULL )
		return 0;

	return GetProcAddress( dll_handle_,symbol_name.c_str() );
}

inline const tchar *shared_library::error (void) const
{
	if( lpMsgBuf != 0 )
		LocalFree( lpMsgBuf );
	lpMsgBuf = 0;
	if (!FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL ))
	{
		// Handle the error.
		return 0 ;
	}

	return (const char* ) lpMsgBuf;
}

inline BT_SHLIB_HANDLE shared_library::get_handle ( ) const
{
	return dll_handle_;
}

inline void shared_library::set_handle (BT_SHLIB_HANDLE handle, int close_on_destruction )
{
	close();
	dll_handle_ = handle;
	close_on_destruction_ = close_on_destruction;
}

_jomoo_end

#endif // _Shared_Library_Cpp_