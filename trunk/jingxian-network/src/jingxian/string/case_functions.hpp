
#ifndef _CASE_FUNCTIONS_HPP_
#define _CASE_FUNCTIONS_HPP_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include <algorithm>
# include "jingxian/string/ctype_traits.hpp"

template<   typename S
        ,   typename F
        >
inline S &transform_impl(S &s, F f)
{
	std::transform(s.begin(), s.end(), s.begin(), f);
    return s;
}

template <typename S>
inline S &transform_upper(S &s)
{
	typedef ctype_traits< typename S::value_type >   ctype_traits_t;
    return transform_impl(s, &ctype_traits_t::to_upper);
}

template <typename S>
inline S &transform_lower(S &s)
{
	typedef ctype_traits<typename S::value_type>   ctype_traits_t;
    return transform_impl(s, &ctype_traits_t::to_lower);
}

template <typename S>
inline S to_upper(S const &s)
{
    S   r(s);

    transform_upper(r);

    return r;
}

template <typename S>
inline S to_lower(S const &s)
{
    S   r(s);

    transform_lower(r);

    return r;
}


#endif /* _CASE_FUNCTIONS_HPP_ */
