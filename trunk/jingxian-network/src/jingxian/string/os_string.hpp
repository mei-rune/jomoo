
#ifndef os_string_h
#define os_string_h

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

#include <tchar.h>
#include <string.h>
#include <string>
#include <sstream>
typedef char char_t;

#ifdef  _UNICODE
typedef std::wstring tstring;
typedef std::wostream tostream;
typedef std::wstringstream tstringstream;
typedef std::wstringstream StringStream;
typedef wchar_t tchar;
#else
typedef std::string tstring;
typedef std::ostream tostream;
typedef std::stringstream tstringstream;
typedef std::stringstream StringStream;
typedef char_t tchar;
#endif

_jingxian_begin

template<typename charT>
struct stringData
{
	// 内存块大小（可选值，为0时为无效值）
	size_t capacity;
	// 字符串大小（可选值，为0或-1为无效值）
    size_t len;
    // 字符串指针
    charT* ptr;
};

inline const char* c_str_ptr( const char* t )
{
	return t;
}

inline std::string::const_pointer c_str_ptr( const std::string& t )
{
	return t.c_str();
}

inline std::string::const_pointer c_str_ptr( const std::string* t )
{
	return t->c_str();
}

inline const wchar_t* c_str_ptr( const wchar_t* t )
{
	return t;
}

inline std::wstring::const_pointer c_str_ptr( const std::wstring& t )
{
	return t.c_str();
}

inline std::wstring::const_pointer c_str_ptr( const std::wstring* t )
{
	return t->c_str();
}

#pragma warning(disable: 4267)
inline std::wstring toWideString( const char* pStr , size_t len=-1 )
{
    int nChars = MultiByteToWideChar( CP_ACP , 0 , pStr , len , NULL , 0 ) ;
    if ( (size_t)-1 == len )
        -- nChars;
    if ( nChars == 0 )
        return L"";

	std::wstring buf;
    buf.resize( nChars ) ;
    MultiByteToWideChar( CP_ACP , 0 , pStr , len ,
        const_cast<wchar_t*>(buf.c_str()) , nChars ) ;
    return buf ;
}
#pragma warning(default: 4267)

inline std::wstring toWideString( const std::string& str )
{
    return toWideString(str.c_str(),str.length()) ;
}

inline std::wstring toWideString( const wchar_t* pStr , size_t len=-1 )
{
    return ((size_t)-1 == len) ? pStr : std::wstring(pStr,len) ;
}

inline const std::wstring& toWideString( const std::wstring& str )
{
    return str ;
}

#pragma warning(disable: 4267)
inline std::string toNarrowString( const wchar_t* pStr , size_t len=-1 )
{
	int nChars = WideCharToMultiByte( CP_ACP , 0 ,
             pStr , len , NULL , 0 , NULL , NULL ) ;
    if ( (size_t)-1 == len )
        -- nChars ;

    if ( nChars == 0 )
        return "" ;

	std::string buf;
    buf.resize( nChars ) ;
    WideCharToMultiByte( CP_ACP , 0 , pStr , len ,
          const_cast<char*>(buf.c_str()) , nChars , NULL , NULL ) ;
    return buf ;
}
#pragma warning(default: 4267)

inline std::string toNarrowString( const std::wstring& str )
{
    return toNarrowString(str.c_str(),str.length()) ;
}

inline std::string toNarrowString( const char* pStr , size_t len=-1 )
{
    return ((size_t)-1 == len) ? pStr : std::string(pStr,len) ;
}
inline const std::string& toNarrowString( const std::string& str )
{
    return str ;
}

#ifdef _UNICODE
    inline tchar toTchar( char ch )
    {
        return (wchar_t)ch ;
    }

    inline tchar toTchar( wchar_t ch )
    {
        return ch ;
    }
    inline tstring toTstring( const std::string& s )
    {
        return toWideString(s) ;
    }

    inline const tstring& toTstring( const std::wstring& s )
    {
        return s;
    }

    inline tstring toTstring( const char* p , size_t len=-1 )
    {
        return toWideString(p,len);
    }

    inline tstring toTstring( const wchar_t* p , size_t len=-1 )
    {
        return (-1 == len) ? p : std::wstring(p,len) ;
    }

#else
    inline tchar toTchar( char ch )
    {
        return ch ;
    }
    inline tchar toTchar( wchar_t ch )
    {
        return (ch >= 0 && ch <= 0xFF) ? (char)ch : '?' ;
    }
    inline const tstring& toTstring( const std::string& s )
    {
        return s ;
    }
    inline tstring toTstring( const char* p , size_t len=-1 )
    {
        return ((size_t)-1 == len) ? p : std::string(p,len) ;
    }
    inline tstring toTstring( const std::wstring& s )
    {
        return toNarrowString(s) ;
    }
    inline tstring toTstring( const wchar_t* p , size_t len=-1 )
    {
        return toNarrowString(p,len) ;
    }
#endif // _UNICODE
    
_jingxian_end

#endif // LOG4CPLUS_TSTRING_HEADER_

