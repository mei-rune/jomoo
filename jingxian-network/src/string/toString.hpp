
#ifndef _to_string_
#define _to_string_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "string_traits.hpp"

_jingxian_begin

namespace detail
{

inline const tstring& to_string_t( const tstring& value ) 
{
	return value;
}

inline tstring to_string_t( bool value ) 
{
	return ( value ? _T("true") : _T("false") );
}

inline tstring to_string_t( tchar value ) 
{
	return tstring( 1,value );
}

inline tstring to_string_t( short value ) 
{
	tstringstream stream;
	stream << value;
	return stream.str();
}

inline tstring to_string_t( int value ) 
{
	tstringstream stream;
	stream << value;
	return stream.str();
}

inline tstring to_string_t( long value ) 
{
	tstringstream stream;
	stream << value;
	return stream.str();
}

inline tstring to_string_t( __int64 value ) 
{
	tstringstream stream;
	stream << value;
	return stream.str();
}

inline tstring to_string_t( unsigned char value ) 
{
	tstringstream stream;
	stream << value;
	return stream.str();
}

inline tstring to_string_t( unsigned short value ) 
{
	tstringstream stream;
	stream << value;
	return stream.str();
}

inline tstring to_string_t( unsigned int value ) 
{
	tstringstream stream;
	stream << value;
	return stream.str();
}

inline tstring to_string_t( unsigned long value ) 
{
	tstringstream stream;
	stream << value;
	return stream.str();
}

inline tstring to_string_t( unsigned __int64 value ) 
{
	tstringstream stream;
	stream << value;
	return stream.str();
}

inline tstring to_string_t( double value ) 
{
	tstringstream stream;
	stream << value;
	return stream.str();
}

inline tstring to_string_t( float value ) 
{
	tstringstream stream;
	stream << value;
	return stream.str();
}

template <bool b>
struct to_stringer
{
#pragma warning(push,3)
 #pragma warning(disable: 4267)
   template<typename T >
   static tstring toString( T t )
   { return to_string_t( t ); }
     #pragma warning(default: 4267)
#pragma warning(pop)
};


template < >
struct to_stringer< true >
{
   template<typename T >
   static tstring toString( T t )
   { return t.toString(); }
};

}

template< typename T >
inline tstring toString( const T& t )
{
 #pragma warning(disable: 4267)
 #pragma warning(disable: 4244)
	return detail::to_string_t( t );
 #pragma warning(default: 4244)
 #pragma warning(default: 4267)
}

_jingxian_end

#endif // _to_string_
