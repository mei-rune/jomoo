
#ifndef _os_string_h_
#define _os_string_h_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "TCHAR.H"
#include <string>
#include <sstream>
typedef char char_t;

#ifdef  _UNICODE
typedef std::wstring tstring;
typedef std::wstringstream tstringstream;
typedef wchar_t tchar;
#else
typedef std::string tstring;
typedef std::stringstream tstringstream;
typedef char_t tchar;
#endif

typedef std::stringstream StringStream;
//#define _T __T
//template < typename T >
//inline T c_str_ptr( T t )

inline const tchar* c_str_ptr( const tchar* t )
{
	return t;
}

inline tstring::const_pointer c_str_ptr( const tstring& t )
{
	return t.c_str();
}


inline tstring::const_pointer c_str_ptr( const tstring* t )
{
	return t->c_str();
}

#endif // LOG4CPLUS_TSTRING_HEADER_

