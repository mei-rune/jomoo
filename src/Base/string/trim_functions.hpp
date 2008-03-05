
#ifndef _trim_functions_hpp_
#define _trim_functions_hpp_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

# include "Platform/os_string.h"
//
//template <typename C>
//inline C const *default_trim_chars(C const *, ss_size_t &n)
//{
//    static const C  s_trimChars[] =
//    {
//            ' '
//        ,   '\n'
//        ,   '\r'
//        ,   '\t'
//        ,   '\v'
//        ,   '\0'
//    };
//
//    n = sizeof(s_trimChars) - 1;
//
//    return &s_trimChars[0];
//}
//
//
//
//template<typename S>
//inline S &trim_left_impl(S &str, typename S::value_type const *trimChars , typename S::size_type _count )
//{
//	typename S::size_type p = str.find_first_not_of( trimChars, 0 , _count );
//	if( typename S::npos == p )
//	{
//		str.clear();
//	}
//	else
//	{
//		str.erase(  0, p );
//	}
//	return str;
//}
//
//
//template<typename S>
//inline S &trim_left(S &str);
//template<   typename S0
//        ,   typename S1
//        >
//inline S0 &trim_left(S0 &str, S1 const &trimChars)
//{
//    return trim_left_impl(str, stlsoft_ns_qual(c_str_ptr)(trimChars));
//}
//template<typename S>
//inline S &trim_right_impl(S &str, typename string_traits<S>::char_type const *trimChars);
//template<typename S>
//inline S &trim_right(S &str);
//template<   typename S0
//        ,   typename S1
//        >
//inline S0 &trim_right(S0 &str, S1 const &trimChars);
//
//template<typename S>
//inline S &trim_all_impl(S &str, typename string_traits<S>::char_type const *trimChars);
//template<typename S>
//inline S &trim_all(S &str);
//template<   typename S0
//        ,   typename S1
//        >
//inline S0 &trim_all(S0 &str, S1 const &trimChars);
//template<typename S>
//inline S &remove_all_impl(S &str, typename S::value_type const *removeChars)
//template<typename S>
//inline S &remove_all(S &str);
//
//template<   typename S0
//        ,   typename S1
//        >
//inline S0 &remove_all(S0 &str, S1 const &removeChars);

#endif /* _trim_functions_hpp_ */
