
#ifndef _trim_functions_hpp_
#define _trim_functions_hpp_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

# include "Platform/os_string.h"

template<typename S>
inline S &trim_left_impl(S &str, typename S::value_type const *trimChars , typename S::size_type _count )
{
	typename S::size_type p = str.find_first_not_of( trimChars, 0 , _count );
	if( typename S::npos == p )
	{
		str.clear();
	}
	else //if( 0 != p )
	{
		str.erase(  0, p );
	}
	return str;
}


template<typename S>
inline S &trim_left(S &str)
{
	typename string_traits<S>::char_type  s_trimChars[] =
    {
            _T( ' ' )
        ,   _T( '\n' )
        ,   _T( '\r' )
        ,   _T( '\t' )
        ,   _T( '\v' )
        ,   _T( '\0' )
    };

    return trim_left_impl(str, s_trimChars );
}

template<   typename S0
        ,   typename S1
        >
inline S0 &trim_left(S0 &str, S1 const &trimChars)
{
    return trim_left_impl(str, c_str_ptr(trimChars) );
}

template<typename S>
inline S &trim_right_impl(S &str, typename S::value_type const *trimChars)
{
	typename S::size_type i = str.find_last_not_of (t);
	if (typename S::npos == i)
		return _T("");
	else
		return str.erase ( i + 1) ;
}

template<typename S>
inline S &trim_right(S &str)
{
	typename string_traits<S>::char_type  s_trimChars[] =
    {
            _T( ' ' )
        ,   _T( '\n' )
        ,   _T( '\r' )
        ,   _T( '\t' )
        ,   _T( '\v' )
        ,   _T( '\0' )
    };

    return trim_right_impl(str, s_trimChars );
}

template<   typename S0
        ,   typename S1
        >
inline S0 &trim_right(S0 &str, S1 const &trimChars)
{
    return trim_right_impl(str, c_str_ptr(trimChars) );
}

template<typename S>
inline S &trim_all_impl(S &str, typename string_traits<S>::char_type const *trimChars)
{
    return trim_left_impl( trim_right_impl(str, trimChars ), trimChars );
}

template<typename S>
inline S &trim_all(S &str)
{
	typename string_traits<S>::char_type  s_trimChars[] =
    {
            _T( ' ' )
        ,   _T( '\n' )
        ,   _T( '\r' )
        ,   _T( '\t' )
        ,   _T( '\v' )
        ,   _T( '\0' )
    };

    return trim_all_impl(str, s_trimChars );
}

//template<   typename S0
//        ,   typename S1
//        >
//inline S0 &trim_all(S0 &str, S1 const &trimChars)
//{
//    return trim_all(str, c_str_ptr(trimChars) );
//}
//
//template<typename S>
//inline S &remove_all_impl(S &str, typename S::value_type const *removeChars)
//{
//}
//
//template<typename S>
//inline S &remove_all(S &str);
//
//template<   typename S0
//        ,   typename S1
//        >
//inline S0 &remove_all(S0 &str, S1 const &removeChars);

#endif /* _trim_functions_hpp_ */
