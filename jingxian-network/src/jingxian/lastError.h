#ifndef _lastError_H
#define _lastError_H

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

# include "jingxian/string/string.hpp"

_jingxian_begin

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
	tstring s(1024, ' ' );
	if( 0 == strerror_s( (char*)s.c_str(), 1024, e ) )
		s.resize( strlen( s.c_str() ) );
	else
		s.resize(0);
    return s;
#else
	wchar_t buf[ 1024 + 10 ];
	if( 0 == _wcserror_s( buf, 1024, e ) )
		return buf;
	return L"";
#endif
}

inline tstring get_c_error()
{
	return get_c_error( errno );
}

_jingxian_end

#endif //_lastError_H
