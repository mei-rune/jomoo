
/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ¤╭⌒╮ ╭⌒╮						_utf8encoding.h,v 1.0 2008/05/15 21:11:54
*  ╱◥██◣ ╭╭ ⌒╮
* ︱田︱田田| ╰------
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

MakeException( EncodingException , _T("编码错误:") );

inline void to_wstring( int code, const char* from, size_t len, std::wstring& to )
{
	to.resize( 2 * len + 100 );
	int wLen = MultiByteToWideChar(code, MB_PRECOMPOSED, from,len, ( wchar_t* )to.c_str(), to.size() );
	if( 0 != wLen )
	{
		to.resize( wLen );
		return;
	}

	DWORD err = ::GetLastError();
	if( ERROR_INSUFFICIENT_BUFFER != err )
		ThrowException1( EncodingException, lastError( err ) );

	// 计算长度
	wLen = MultiByteToWideChar(code, MB_PRECOMPOSED, from,len, NULL, 0 );
	if( 0 == wLen )
		ThrowException1( EncodingException, lastError( ) );

	to.resize( wLen + 10 );
	wLen = MultiByteToWideChar(code, MB_PRECOMPOSED, from,len, ( wchar_t* )to.c_str(), to.size() );
	if( 0 == wLen )
		ThrowException1( EncodingException, lastError( ) );

	to.resize( wLen );
}

inline void from_wstring(int code, const wchar_t* from, size_t len, std::string& to )
{
	to.resize( 3 * len + 100 );
	int wLen = WideCharToMultiByte(code, MB_PRECOMPOSED, from,len, ( char* )to.c_str(), to.size() );
	if( 0 != wLen )
	{
		to.resize( wLen );
		return;
	}

	DWORD err = ::GetLastError();
	if( ERROR_INSUFFICIENT_BUFFER != err )
		ThrowException1( EncodingException, lastError( err ) );

	// 计算长度
	wLen = WideCharToMultiByte(code, MB_PRECOMPOSED, from,len, NULL, 0 );
	if( 0 == wLen )
		ThrowException1( EncodingException, lastError( ) );

	to.resize( wLen + 100 );
	wLen = WideCharToMultiByte(code, MB_PRECOMPOSED, from,len, ( char* )to.c_str(), to.size() );
	if( 0 == wLen )
		ThrowException1( EncodingException, lastError( ) );

	to.resize( wLen );
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

inline void from_utf8( const char* from, size_t len, std::string& to )
{
	std::wstring unicode_string;
	utf8_to_wstring(  from, len, unicode_string );
	from_unicode( unicode_string.c_str(), unicode_string.size(), to );
}

_jomoo_end

#endif /* _utf8encoding_h_ */
