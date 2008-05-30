
/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - °Ë®q°–®r ®q°–®r						_utf8encoding.h,v 1.0 2008/05/15 21:11:54
*  ®u®ê®Ä®Ä®é ®q®q °–®r
* ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
* -------------------------------------------------------------------------------
*/

# ifndef _utf8encoding_h_
# define _utf8encoding_h_


# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
#  pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

# include "jomoo/exception.hpp"

_jomoo_begin

MakeException( EncodingException , _T("±‡¬Î¥ÌŒÛ:") );


inline bool try_to_wstring( int code, const char* from, size_t len, wchar_t* to, size_t toLen, size_t& transform_length )
{
	transform_length =( size_t ) MultiByteToWideChar(code, MB_PRECOMPOSED, from,len, to, toLen );
	if( 0 != transform_length )
		return true;

	DWORD err = ::GetLastError();
	if( ERROR_INSUFFICIENT_BUFFER != err )
		return false;
	(size_t) transform_length = MultiByteToWideChar(code, MB_PRECOMPOSED, from,len, NULL, 0 );
	return false;
}

inline bool try_from_wstring( int code, const wchar_t* from, size_t len, char_t* to, size_t toLen, size_t& transform_length )
{
	transform_length = (size_t) WideCharToMultiByte(code, MB_PRECOMPOSED, from,len, to, toLen, NULL, NULL );
	if( 0 != transform_length )
		return true;

	DWORD err = ::GetLastError();
	if( ERROR_INSUFFICIENT_BUFFER != err )
		return false;

	transform_length = (size_t) WideCharToMultiByte(code, MB_PRECOMPOSED, from,len, NULL, 0, NULL, NULL );
	return false;
}

inline void to_wstring( int code, const char* from, size_t len, std::wstring& to )
{
	to.resize( 2 * len + 100 );
	size_t wLen = 0;
	if( try_to_wstring( code, from, len, ( wchar_t*)to.c_str(), to.size(), wLen ) )
		return;
	if( 0 == wLen )
		ThrowException1( EncodingException, lastError( ) );

	to.resize( wLen + 10 );
	wLen = (size_t) MultiByteToWideChar(code, MB_PRECOMPOSED, from,len, ( wchar_t* )to.c_str(), to.size() );
	if( 0 == wLen )
		ThrowException1( EncodingException, lastError( ) );

	to.resize( wLen );
}

inline void from_wstring(int code, const wchar_t* from, size_t len, std::string& to )
{
	to.resize( 3 * len + 100 );
	size_t mLen = 0;
	if( try_from_wstring( code, from, len, ( char* )to.c_str(), to.size(), mLen ) )
		return;
	if( 0 == mLen )
		ThrowException1( EncodingException, lastError( ) );

	to.resize( mLen + 100 );
	mLen = (size_t) WideCharToMultiByte(code, MB_PRECOMPOSED, from, len, ( char* )to.c_str(), to.size(), NULL, NULL );
	if( 0 == mLen )
		ThrowException1( EncodingException, lastError( ) );
	to.resize( mLen );
}

inline void to_unicode( const char* from, size_t len, std::wstring& to )
{
	to_wstring( CP_ACP, from, len, to );
}

inline void to_unicode( const std::string& from, std::wstring& to )
{
	to_wstring( CP_ACP, from.c_str(), from.size(), to );
}

inline void from_unicode( const wchar_t* from, size_t len, std::string& to )
{
	from_wstring( CP_ACP, from, len, to );
}

inline void from_unicode( const std::wstring& from, std::string& to )
{
	from_wstring( CP_ACP, from.c_str(), from.size(), to );
}

inline bool try_from_unicode( const wchar_t* from, size_t len, char* to, size_t toLen, size_t& transform_length )
{
	return try_from_wstring( CP_ACP, from, len, to, toLen, transform_length );
}

inline void wstring_to_utf8( const wchar_t* from, size_t len, std::string& to )
{
	from_wstring( CP_UTF8, from, len, to );
}

inline void utf8_to_wstring( const char* from, size_t len, std::wstring& to )
{
	to_wstring( CP_UTF8, from, len, to );
}

inline void to_utf8( const char* from, size_t len, std::string& to )
{
	std::wstring unicode_string;
	to_unicode(  from, len, unicode_string );
	wstring_to_utf8( unicode_string.c_str(), unicode_string.size(), to );
}

inline std::string to_utf8( const char* from, size_t len )
{
	std::string result;
	to_utf8( from, len , result );
	return result;
}

inline void from_utf8( const char* from, size_t len, std::string& to )
{
	std::wstring unicode_string;
	utf8_to_wstring(  from, len, unicode_string );
	from_unicode( unicode_string.c_str(), unicode_string.size(), to );
}

inline std::string from_utf8( const char* from, size_t len )
{
	std::string result;
	from_utf8( from, len , result );
	return result;
}

inline bool try_from_utf8( const char* from, size_t len, char* to, size_t toLen, size_t& transform_length )
{
	std::wstring unicode_string;
	utf8_to_wstring(  from, len, unicode_string );
	return try_from_unicode( unicode_string.c_str(), unicode_string.size(), to, toLen, transform_length );
}

_jomoo_end

#endif /* _utf8encoding_h_ */
