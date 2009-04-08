

#ifndef JOMOO_GET_LAST_ERROR_H
#define JOMOO_GET_LAST_ERROR_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include <tchar.h>
#include <string.h>

inline tstring get_last_error( DWORD code )
{
	LPVOID lpMsgBuf = 0;
	DWORD ret = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL );
	if ( ret <= 0 )
	{
		return tstring(_T("<²»ÖªµÀ>") );
	}

	LPTSTR s = (LPTSTR)lpMsgBuf;
	s[ ret ] = 0;
	if( s[ret - 1 ] == _T('\r') || s[ ret - 1 ] == _T('\n'))
		s[ret - 1 ] = 0;
	if( s[ret - 2 ] == _T('\r') || s[ ret - 2 ] == _T('\n'))
		s[ret - 2 ] = 0;

	tstring str( _T("[") );

	tchar tmp[110] = _T("");
	string_traits<tchar>::ultoa( code, tmp,110, 10 );
	str += ( const tchar* )tmp;
	str += ( const tchar* )_T("],");
	str += (LPTSTR)lpMsgBuf;
	// Free the buffer.
	LocalFree( lpMsgBuf );

	return str;
}

inline tstring get_last_error( )
{
	return get_last_error( ::GetLastError() );
}

inline tstring lastError( DWORD code )
{
	return get_last_error( code );
}

inline tstring lastError( )
{
	return get_last_error( ::GetLastError() );
}


inline tstring get_c_error( int e )
{
#ifndef _UNICODE
	tstring err( 1024, ' ' );

	if( 0 == strerror_s( ( tstring::value_type*) err.c_str(), 1024 , e ) )
	{
		err.resize( string_traits<tstring::value_type>::strlen( err.c_str() ) );
	}
	else
	{
		err = "<<unkown error>>";
	}
	return err;
#else
	tstring err( 1024, L' ' );

	if( 0 == _wcserror_s( ( tstring::value_type*) err.c_str(), 1024 , e ) )
	{
		err.resize( string_traits<tstring::value_type>::strlen( err.c_str() ) );
	}
	else
	{
		err = L"<<unkown error>>";
	}
	return err;
#endif
}

inline tstring get_c_error()
{
	return get_c_error( errno );
}


#endif //JOMOO_GET_LAST_ERROR_H
