
#ifndef _case_functions_hpp_
#define _case_functions_hpp_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

# include "Platform/os_string.h"
# include "ctype_traits.hpp"
# include <algorithm>

template<   typename S
        ,   typename F
        >
inline S &transform_impl(S &s, F f)
{
	std::transform(s.begin(), s.end(), s.begin(), f);
    return s;
}

template <typename S>
inline S &make_upper(S &s)
{
	typedef ctype_traits< typename S::value_type >   ctype_traits_t;
    return transform_impl(s, &ctype_traits_t::to_upper);
}

template <typename S>
inline S &make_lower(S &s)
{
	typedef ctype_traits<typename S::value_type>   ctype_traits_t;
    return transform_impl(s, &ctype_traits_t::to_lower);
}

template <typename S>
inline S to_upper(S const &s)
{
    S   r(s);

    make_upper(r);

    return r;
}

template <typename S>
inline S to_lower(S const &s)
{
    S   r(s);

    make_lower(r);

    return r;
}


#endif /* _case_functions_hpp_ */
