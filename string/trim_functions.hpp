
#ifndef _trim_functions_hpp_
#define _trim_functions_hpp_

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

# include "Hazel.Platform/os_string.h"

namespace String
{

template <typename char_type>
inline char_type const *default_trim_chars(char_type const *, size_t &n)
{
    static const char_type  s_trimChars[] =
    {
            ' '
        ,   '\n'
        ,   '\r'
        ,   '\t'
        ,   '\v'
        ,   '\0'
    };

    n = sizeof(s_trimChars) - 1;

    return &s_trimChars[0];
}

template<typename stringT>
inline stringT &trim_left(stringT &str, typename stringT::value_type const *trimChars , typename stringT::size_type _count )
{
	typename stringT::size_type p = str.find_first_not_of( trimChars, 0 , _count );
	if( typename stringT::npos == p )
	{
		str.clear();
	}
	else
	{
		str.erase(  0, p );
	}
	return str;
}

template<typename stringT>
inline stringT &trim_left(stringT &str, typename stringT::value_type const *trimChars )
{
	return trim_left( str, trimChars, char_traits<stringT::value_type>::strlen( trimChars ) );
}

template<typename stringT>
inline stringT &trim_right(stringT &str, typename stringT::value_type const *trimChars , typename stringT::size_type _count )
{
	typename stringT::size_type p = str.find_last_not_of( trimChars, 0 , _count );
	if( typename stringT::npos == p )
	{
		str.clear();
	}
	else
	{
		str.erase( p );
	}
	return str;
}

template<typename stringT>
inline stringT &trim_right(stringT &str, typename stringT::value_type const *trimChars )
{
	return trim_right( str, trimChars, char_traits<stringT::value_type>::strlen( trimChars ) );
}

template<typename stringT>
inline stringT &trim_all(stringT &str, typename stringT::value_type const *trimChars , typename stringT::size_type _count )
{
	return trim_left( trim_right( str, trimChars, _count ), trimChars, _count );
}

template<typename stringT>
inline stringT &trim_all(stringT &str, typename stringT::value_type const *trimChars )
{
	return trim_all( str, trimChars, char_traits<stringT::value_type>::strlen( trimChars ) );
}

}

#endif /* _trim_functions_hpp_ */
