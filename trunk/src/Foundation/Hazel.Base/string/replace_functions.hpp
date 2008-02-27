
#ifndef _replace_functions_hpp_
#define _replace_functions_hpp_

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

# include "Hazel.Platform/os_string.h"

namespace String
{

/**
 * 在指定字符串忽略大小查找字符串
 * @param[ in ] s 字符串
 * @param[ in ] what 字符串
 * @param[ in ] len what字符串的长度
 * @param[ in ] offest 偏移，以0开始
 * @return 找到返回它以0开始的位置，没有返回npos
 * @remark 如果what字空时返回npos
 */

template<typename stringT>
inline typename stringT::size_type case_find (const stringT	&s,
											 typename stringT::value_type const *what,
											 typename stringT::size_type		len,
											 typename stringT::size_type		offset /* = 0 */ )
{
    if ( (s.size () - offset) < len)
		return stringT::npos;

    if ( NULL == what )
		return stringT::npos;

    typename stringT::value_type const *begin = s.c_str ();
    typename stringT::value_type const *end = begin + s.size ();
    typename stringT::value_type const *p = begin + offset;

	for ( ; p <= end-len; ++p)
		if (! string_traits<typename stringT::value_type>::strnicmp(p, what, len))
		return p - begin;

	return stringT::npos;
}

/**
 * 用with子字符串替换s字符串中指定偏移后的所有指定的what子字符串
 * @param[ in ] s 字符串
 * @param[ in ] offset 偏移量
 * @param[ in ] what 子字符串
 * @param[ in ] with 子字符串
 * @param[ in ] Casesensitive 是否区分大小写，( true 区分， false 不区分 )
 * @return 返回替换后的字符串。
 */
template<typename stringT>
inline stringT& replace (stringT	&s,
						 typename stringT::size_type			offset,
						 const typename stringT::value_type*	what,
						 typename stringT::size_type	whatlen,
						 const typename stringT::value_type* with,
						 typename stringT::size_type withlen,
						 bool Casesensitive = true )
{
	if( Casesensitive )
	{
		while ( stringT::npos != (offset = case_find( what, offset, whatlen ) ))
		{
			s.replace( offset, whatlen, with , with + withlen );
			offset += ( withlen + 1 );
		}
	}
	else
	{
		while ( stringT::npos != (offset = s.find( what, offset, whatlen ) ))
		{
			s.replace( offset, whatlen, with , with + withlen );
			offset += ( withlen + 1 );
		}
	}
    return s;
}

template<typename stringT>
inline stringT& replace (stringT	&s,
			typename stringT::size_type			offset,
		    typename stringT::value_type		what,
		    typename stringT::value_type const * with,
			typename stringT::size_type len,
			bool Casesensitive = true )
{
	return replace( s, offset, &what, 1, with, len, Casesensitive );
}

template<typename stringT>
inline stringT& replace (stringT	&s,
			typename stringT::size_type			offset,
		    typename stringT::value_type		what,
		    typename stringT::value_type const * with,
			bool Casesensitive )
{
	return replace( s, offset,
		&what, 1,
		with, string_traits<typename stringT::value_type>::strlen( with ),
		Casesensitive );
}

template<typename stringT>
inline stringT& replace (stringT	&s,
			stringT::size_type			offset,
		    typename stringT::value_type what,
		    const stringT	&with,
			bool Casesensitive )
{
	return replace( s, offset,
		what,
		with.c_str(),with.size(),
		Casesensitive );
}

template<typename stringT>
inline stringT& replace (stringT	&s,
			typename stringT::size_type			offset,
		    typename stringT::value_type const * what,
		    typename stringT::value_type const * with,
			bool Casesensitive )
{
	return replace( s, offset,
		what,string_traits<typename stringT::value_type>::strlen( what ),
		with, string_traits<typename stringT::value_type>::strlen( with ),
		Casesensitive );
}

template<typename stringT>
inline stringT& replace (stringT	&s,
			typename stringT::size_type			offset,
		    const stringT& what,
		    const stringT& with,
			bool Casesensitive )
{
	return replace( s, offset,
		what.c_str(),what.size( ),
		with.c_str(), with.size( ),
		Casesensitive );
}

template<typename stringT>
inline stringT& replace (stringT	&s,
		    typename stringT::value_type const * what,
		    typename stringT::value_type const * with,
			bool Casesensitive )
{
	return replace( s, 0,
		what,string_traits<typename stringT::value_type>::strlen( what ),
		with, string_traits<typename stringT::value_type>::strlen( with ),
		Casesensitive );
}

template<typename stringT>
inline stringT& replace (stringT	&s,
		    const stringT	&what,
		    const stringT	&with,
			bool Casesensitive )
{
	return replace (s, 0,
		what.c_str(), what.size(),
		with.c_str(), with.size(),
		Casesensitive );
}

#endif /* _replace_functions_hpp_ */
