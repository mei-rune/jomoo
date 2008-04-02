
#ifndef _with_functions_hpp_
#define _with_functions_hpp_

#include "jomoo/config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

# include "Hazel.Platform/os_string.h"
# include "string_traits.hpp"

namespace String
{

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
struct string_begin_with_function
	: public std::unary_function<C const*, bool>
{
public:

public:
    string_begin_with_function(C const *prefix)
        : m_prefix(prefix)
		, m_prefixLen( string_traits< C >::strlen(prefix))
    {}

	string_begin_with_function(C const *prefix , size_t prefixLen )
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
struct string_end_with_function
	: public std::unary_function<C const*, bool>
{
public:

public:
    string_end_with_function(C const *suffix)
        : m_suffix(suffix)
        , m_suffixLen(string_traits< C >::strlen(suffix))
    {}

	string_end_with_function(C const *suffix , size_t suffixLen )
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

template<typename char_type>
inline bool begin_with( const char_type* str, typename char_type const * prefix, size_t count)
{
    return 0 == string_traits< char_type >::strncmp( str, prefix, count);
}

template<typename char_type>
inline bool begin_with( const char_type* str, typename char_type const * prefix)
{
    return 0 == string_traits< char_type >::strcmp( str, prefix);
}

template<typename stringT>
inline bool begin_with( const stringT& str, typename stringT::value_type const * prefix, size_t count)
{
	return begin_with( c_str_ptr( str ), prefix, count );
}

template<typename stringT>
inline bool begin_with( const stringT& str, typename stringT::value_type const * prefix)
{
	return begin_with( c_str_ptr( str ), prefix);
}

template<typename stringT>
inline bool begin_with( const stringT& str, const stringT& prefix)
{
	return begin_with( c_str_ptr( str ), c_str_ptr(prefix), prefix.size() );
}

template<typename char_type>
inline bool end_with( const char_type* str, size_t length, const char_type * prefix, size_t count)
{
	if( count > length )
		return false;
    return 0 == ::strncmp(str+(len-length), prefix, count);
}

template<typename char_type>
inline bool end_with( const char_type* str, size_t length, const char_type * prefix)
{
	return end_with( str, length, string_traits< char_type >::strlen( prefix ) );
}

template<typename char_type>
inline bool end_with( const char_type* str, size_t length, const char_type * prefix)
{
	return end_with( str, length, prefix, string_traits< char_type >::strlen( prefix ) );
}

template<typename char_type>
inline bool end_with( const char_type* str, const char_type * prefix)
{
	return end_with( str, string_traits< char_type >::strlen( str ), prefix, string_traits< char_type >::strlen( prefix ) );
}

template<typename stringT>
inline bool end_with( const stringT& str, typename stringT::value_type const * prefix, typename stringT::size_type count)
{
	return end_with( c_str_ptr(str), str.size(), prefix, count );
}

template<typename stringT>
inline bool end_with( const stringT& str, typename stringT::value_type const * prefix)
{
	return end_with( c_str_ptr(str), str.size(), prefix, string_traits< typename stringT::value_type >::strlen( prefix ) );
}

template<typename stringT>
inline bool end_with( const stringT& str, const stringT& prefix)
{
	return end_with( c_str_ptr(str), str.size(), c_str_ptr( prefix ), prefix.size() );
}

}

#endif // _with_functions_hpp_