
#ifndef _to_string_
#define _to_string_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#ifdef BOOST

#pragma warning(push,3)
 #pragma warning(disable: 4819)
#include <boost/type_traits.hpp>
  #pragma warning(default: 4819)
#pragma warning(pop)

#endif

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

#ifdef BOOST

template< typename T >
inline tstring toString( T t )
{
   return detail::to_stringer< ::boost::is_class<T>::value
		>::toString( t );
}

#else

template< typename T >
inline tstring toString( const T& t )
{
	return detail::to_string_t( t );
}

#endif

#endif // _to_string_
