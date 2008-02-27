
#ifndef _to_string_
#define _to_string_

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#ifdef BOOST

#pragma warning(push,3)
 #pragma warning(disable: 4819)
#include <boost/type_traits.hpp>
  #pragma warning(default: 4819)
#pragma warning(pop)

#endif

namespace detail
{

template< typename stringT>
inline const stringT& to_string_t( const stringT& value ) 
{
	return value;
}

template< typename stringT>
inline stringT to_string_t( bool value ) 
{
	return ( value ? BT_TEXT("true") : BT_TEXT("false") );
}

template< typename stringT>
inline stringT to_string_t( tchar value ) 
{
	return stringT( 1,value );
}

template< typename stringT>
inline stringT to_string_t( short value ) 
{
	typename stringT::value_type buf[ 100];
	string_traits<typename stringT::value_type>::itoa( value, buf, 10 );
	return string( buf );
}

template< typename stringT>
inline stringT to_string_t( int value ) 
{
	typename stringT::value_type buf[ 100];
	string_traits<typename stringT::value_type>::itoa( value, buf, 10 );
	return string( buf );
}

template< typename stringT>
inline stringT to_string_t( long value ) 
{
	typename stringT::value_type buf[ 100];
	string_traits<typename stringT::value_type>::ltoa( value, buf, 10 );
	return string( buf );
}

template< typename stringT>
inline stringT to_string_t( __int64 value ) 
{
	typename stringT::value_type buf[ 100];
	string_traits<typename stringT::value_type>::i64toa( value, buf, 10 );
	return string( buf );
}

template< typename stringT>
inline stringT to_string_t( unsigned char value ) 
{
	typename stringT::value_type buf[ 100];
	string_traits<typename stringT::value_type>::uitoa( value, buf, 10 );
	return string( buf );
}
template< typename stringT>
inline stringT to_string_t( unsigned short value ) 
{
	typename stringT::value_type buf[ 100];
	string_traits<typename stringT::value_type>::uitoa( value, buf, 10 );
	return string( buf );
}
template< typename stringT>
inline stringT to_string_t( unsigned int value ) 
{
	typename stringT::value_type buf[ 100];
	string_traits<typename stringT::value_type>::uitoa( value, buf, 10 );
	return string( buf );
}
template< typename stringT>
inline stringT to_string_t( unsigned long value ) 
{
	typename stringT::value_type buf[ 100];
	string_traits<typename stringT::value_type>::ultoa( value, buf, 10 );
	return string( buf );
}
template< typename stringT>
inline stringT to_string_t( unsigned __int64 value ) 
{
	typename stringT::value_type buf[ 100];
	string_traits<typename stringT::value_type>::ui64toa( value, buf, 10 );
	return string( buf );
}
template< typename stringT>
inline stringT to_string_t( double value ) 
{
	Stringstream stream;
	stream << value;
	return stream.str();
}
template< typename stringT>
inline stringT to_string_t( float value ) 
{
	Stringstream stream;
	stream << value;
	return stream.str();
}

template <bool b>
struct to_stringer
{
#pragma warning(push,3)
 #pragma warning(disable: 4267)
   template<typename T >
   static stringT toString( T t )
   { return to_string_t( t ); }
     #pragma warning(default: 4267)
#pragma warning(pop)
};


template < >
struct to_stringer< true >
{
   template<typename T >
   static stringT toString( T t )
   { return t.toString(); }
};

}

#ifdef BOOST

template< typename T >
inline stringT toString( T t )
{
   return detail::to_stringer< ::boost::is_class<T>::value
		>::toString( t );
}

#else

template<typename stringT, typename T >
inline stringT toString( const T& t )
{
	return detail::to_string_t< stringT >( t );
}

#endif

#endif // _to_string_
