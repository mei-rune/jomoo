
#ifndef _functionals_hpp_
#define _functionals_hpp_

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

# include "Hazel.Platform/os_string.h"
# include "string_traits.hpp"

template <typename S>
struct quoter
	: public std::unary_function<char const*, void>
{
public:
    S operator()(S const &s) const
    {
        if(!is_null( ::strpbrk( c_str_ptr( s), " \t\"") ))
        {
            // Check whether it has quotes. If it does, we'll just assume it's ok
            if(!is_null( ::strchr(c_str_ptr( s), '"')))
            {
                return s;
            }
            else
            {
                return '"' + s + '"';
            }
        }
        else
        {
            return s;
        }
    }
};

template <typename C>
struct string_begins_with_function
	: public std::unary_function<C const*, bool>
{
public:

public:
    string_begins_with_function(C const *prefix)
        : m_prefix(prefix)
		, m_prefixLen( string_traits< C >::strlen(prefix))
    {}

	string_begins_with_function(C const *prefix , size_t prefixLen )
        : m_prefix(prefix)
        , m_prefixLen( prefixLen )
    {}

public:
    bool operator ()(C const *line) const
    {
        return 0 == string_traits< C >::strncmp(line, m_prefix, m_prefixLen);
    }
    template <typename S>
    bool operator ()(S const &line) const
    {
        return operator ()(c_str_ptr(line));
    }

private:
    C const *const  m_prefix;
    const size_t m_prefixLen;
};

template <typename C>
struct string_ends_with_function
	: public std::unary_function<C const*, bool>
{
public:

public:
    string_ends_with_function(C const *suffix)
        : m_suffix(suffix)
        , m_suffixLen(string_traits< C >::strlen(suffix))
    {}

	string_ends_with_function(C const *suffix , size_t suffixLen )
        : m_suffix(suffix)
        , m_suffixLen( suffixLen )
    {}

public:
    bool operator ()(C const *line) const
    {
		size_t len = string_traits< C >::strlen( line );
		if( m_suffixLen > len )
			return false;
        return 0 == ::strncmp(line+(len-m_suffixLen), m_suffix, m_suffixLen);
    }
    template <typename S>
    bool operator ()(S const &line) const
    {
        return operator ()(c_str_ptr(line));
    }

private:
    C const *const  m_suffix;
    const size_t m_suffixLen;
};


template <typename C>
inline string_begins_with_function<C> string_begins_with(C const *prefix)
{
    return string_begins_with_function<C>(prefix);
}

template <typename C>
inline string_ends_with_function<C> string_ends_with(C const *suffix)
{
    return string_ends_with_function<C>(suffix);
}

#endif // _functionals_hpp_