
#ifndef _STRINGOPS_H_
#define _STRINGOPS_H_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "jingxian/string/os_string.hpp"

_jingxian_begin

/**
* symbol[var]
*/
inline bool square_pattern( const tstring& src , tstring& symbol , tstring& var )
{
	if( src.size() < 2 )
		return false;

	tstring::size_type square_start = src.find( '[' );

	if( tstring::npos == square_start )
	{
		symbol = src;
		return true;
	}

	tstring::size_type square_end = src.find( ']' , square_start );
	if( tstring::npos == square_end )
	{
		symbol = src.substr( 0,square_start );
		return true;
	}
	symbol = src.substr( 0,square_start );
	var = src.substr( square_start + 1, square_end - square_start - 1 );
	return true;
}

///**
// * 在指定字符串忽略大小查找字符
// * @param[ in ] s 字符串
// * @param[ in ] what 字符
// * @param[ in ] offest 偏移，以0开始
// * @return 找到返回它以0开始的位置，没有返回npos
// */
//inline
//tstring::size_type
//casefind (const tstring	&s,
//		    tchar		what,
//		    tstring::size_type			offset /* = 0 */ )
//{
//    ASSERT (offset >= 0);
//    ASSERT ((size_t) offset <= s.size ());
//
//    const tchar *begin = s.c_str ();
//
//    
//	const tchar *end = begin + s.size ();
//	const tchar *p = begin + offset;
//
//	for (tstring::size_type ch = _totlower ( what ); p != end; ++p)
//	    if (_totlower ( *p) == ch )
//		return p - begin;
//	return tstring::npos;
// }
//
///**
// * 在指定字符串忽略大小查找字符串
// * @param[ in ] s 字符串
// * @param[ in ] what 字符串
// * @param[ in ] len what字符串的长度
// * @param[ in ] offest 偏移，以0开始
// * @return 找到返回它以0开始的位置，没有返回npos
// */
//inline
//tstring::size_type
//casefind (const tstring	&s,
//		    const tchar		*what,
//		    tstring::size_type		len,
//		    tstring::size_type			offset /* = 0 */ )
//{
//    ASSERT ((size_t) offset <= s.size ());
//    ASSERT (what || !len);
//
//    if (s.size () - offset < len)
//		return tstring::npos;
//
//    if (! what )
//	return offset;
//
//    const tchar *begin = s.c_str ();
//    const tchar *end = begin + s.size ();
//    const tchar *p = begin + offset;
//
//	for ( ; p <= end-len; ++p)
//	    if (! _tcsnicmp (p, what, len))
//		return p - begin;
//	return tstring::npos;
//}
//
///**
// * 在指定字符串的指定的偏处向左忽略大小查找字符
// * @param[ in ] s 字符串
// * @param[ in ] what 字符
// * @param[ in ] offest 偏移，以0开始
// * @return 找到返回它以0开始的位置，没有返回npos
// */
//inline
//tstring::size_type
//caserfind (const tstring	&s,
//		     tchar		what,
//		     tstring::size_type		offset /* = tstring::npos*/)
//{
//    ASSERT ((size_t) offset <= s.size ());
//
//    const tchar *begin = s.c_str ();
//    const tchar *p = begin + offset + 1;
//	for (tstring::size_type ch = _totlower ( what); p != begin; --p)
//	    if (_totlower ( p[tstring::npos]) == ch)
//		return p - begin - 1;
//    return tstring::npos;
//}
//
///**
// * 在指定字符串的指定的偏处向左忽略大小查找字符串
// * @param[ in ] s 字符串
// * @param[ in ] what 字符串
// * @param[ in ] len what字符串的长度
// * @param[ in ] offest 偏移，以0开始
// * @return 找到返回它以0开始的位置，没有返回npos
// */
//inline
//tstring::size_type
//caserfind (const tstring	&s,
//		     const tchar		*what,
//		     tstring::size_type		len,
//		     tstring::size_type		offset /* = tstring::npos*/)
//{
//    ASSERT ((size_t) offset <= s.size ());
//    ASSERT (!what || !len);
//
//    if (s.size () < len)
//		return tstring::npos;
//
//    if (s.size () - len < (size_t) offset)
//	offset = s.size () - len;
//
//    if (! what)
//	return offset;
//
//    const char *begin = s.c_str ();
//    const char *p = begin + offset + 1;
//
//	for ( ; p != begin; --p)
//	    if (! _tcsnicmp ( p, what, len))
//		return p - begin - 1;
//    return tstring::npos;
//}
//
///**
// * 找出包含指定字符串的所有字符串
// * @param[ in ] items 字符串数组
// * @param[ in ] what 字符串
// * @param[ in ] Casesensitive 是否区分大小写，( true 区分， false 不区分 )
// * @return 返回所有包含what字符串的字符串。
// */
//inline
//StringList
//grep (const StringList	&items,
//		 const tstring	&what,
//		 bool			CaseInsensitive /* = false */)
//{
//    StringList result;
//	if( CaseInsensitive )
//	{
//		for (size_t i = 0; i < items.size (); ++i)
//			if (casefind (items [i], what.c_str (), what.size () ,0 ) != tstring::npos )
//				result.push_back (items [i]);
//	}
//	else
//	{
//	for (size_t i = 0; i < items.size (); ++i)
//	if (items[i].find ( what ) != tstring::npos )
//	    result.push_back (items [i]);
//	}
//	
//	return result;
//}
//
///**
// * 计算指定字符在指定字符串中出现的次数
// * @param[ in ] s 字符串
// * @param[ in ] what 字符
// * @param[ in ] Casesensitive 是否区分大小写，( true 区分， false 不区分 )
// * @return 返回所有包含what字符串的字符串。
// */
//inline
//tstring::size_type
//contains (const tstring	&s,
//		     tchar		what,
//		     bool		Casesensitive /* = false */)
//{
//    tstring::size_type n = 0;
//    tstring::size_type index = 0;
//	if( Casesensitive )
//	{
//    while ((index = casefind (s, what, index )) != tstring::npos )
//	++n, ++index;
//	}
//	else
//	{
//	while ((index = s.find ( what, index )) != tstring::npos )
//	++n, ++index;
//	}
//    return n;
//}
//
///**
// * 计算指定子字符串在指定字符串中出现的次数
// * @param[ in ] s 字符串
// * @param[ in ] what 子字符串
// * @param[ in ] len 子字符串的长度
// * @param[ in ] Casesensitive 是否区分大小写，( true 区分， false 不区分 )
// * @return 返回所有包含what字符串的字符串。
// */
//inline
//tstring::size_type
//contains (const tstring	&s,
//		     const tchar		*what,
//			 tstring::size_type	len,
//		     bool		Casesensitive /* = false */)
//{
//	ASSERT( what != 0 );
//	ASSERT( *what != 0 );
//    tstring::size_type		n = 0;
//    tstring::size_type		index = 0;
//	if( Casesensitive )
//	{
//    while ((index = casefind (s, what, len, index )) != tstring::npos )
//	++n, ++index;
//	}
//	else
//	{
//	while ((index = s.find ( what, len, index )) != tstring::npos )
//	++n, ++index;
//	}
//    return n;
//}
//
///**
// * 计算指定子字符串在指定字符串中出现的次数
// * @param[ in ] s 字符串
// * @param[ in ] what 子字符串
// * @param[ in ] Casesensitive 是否区分大小写，( true 区分， false 不区分 )
// * @return 返回所有包含what字符串的字符串。
// */
//inline
//tstring::size_type
//contains (const tstring	&s,
//		     const tchar		*what,
//		     bool		Casesensitive /* = false */)
//{
//    size_t	len = strlen (what);
//    return contains( s,what,len,Casesensitive);
//}
//
///**
// * 计算指定子字符串在指定字符串中出现的次数
// * @param[ in ] s 字符串
// * @param[ in ] what 子字符串
// * @param[ in ] Casesensitive 是否区分大小写，( true 区分， false 不区分 )
// * @return 返回所有包含what字符串的字符串。
// */
//inline tstring::size_type
//contains (const tstring	&s,
//		     const tstring	&what,
//		     bool Casesensitive /* = false */)
//{
//    return contains( s, what.c_str(), what.size(), Casesensitive );
//}
//
/////**
//// * 用with子字符串替换s字符串中指定偏移后的所有指定的what子字符串
//// * @param[ in ] s 字符串
//// * @param[ in ] offset 偏移量
//// * @param[ in ] what 子字符串
//// * @param[ in ] with 子字符串
//// * @param[ in ] Casesensitive 是否区分大小写，( true 区分， false 不区分 )
//// * @return 返回替换后的字符串。
//// */
////inline
////tstring
////replace (const tstring	&s,
////		 tstring::size_type			offset,
////		    const tchar*	what,
////			tstring::size_type	whatlen,
////		    const tchar* with,
////			tstring::size_type withlen,
////			bool Casesensitive )
////{
////    tstring result (s);
////	if( Casesensitive )
////	{
////		while (true)
////		{
////			if ((offset = casefind( result, what, whatlen, offset) ) == tstring::npos )
////				break;
////			result.replace( offset, whatlen, with , with + withlen );
////			offset += ( withlen + 1 );
////		}
////	}
////	else
////	{
////		while (true)
////		{
////			if ((offset = result.find( what, offset, whatlen ) ) == tstring::npos )
////				break;
////			result.replace( offset, whatlen, with , with + withlen );
////			offset += ( withlen + 1 );
////		}
////	}
////    return result;
////}
////
////inline
////tstring
////replace (const tstring	&s,
////		 tstring::size_type			offset,
////		    tchar		what,
////		    const tchar* with,
////			tstring::size_type len,
////			bool Casesensitive )
////{
////	return replace( s, offset, &what, 1, with, len, Casesensitive );
////}
////
////inline
////tstring
////replace (const tstring	&s,
////		 tstring::size_type			offset,
////		    tchar		what,
////		    const tchar* with,
////			bool Casesensitive )
////{
////	return replace( s, offset,
////		&what, 1,
////		with, _tcslen( with ),
////		Casesensitive );
////}
////
////inline
////tstring
////replace (const tstring	&s,
////		 tstring::size_type			offset,
////		    tchar		what,
////		    const tstring	&with,
////			bool Casesensitive )
////{
////	return replace( s, offset,
////		what,
////		with.c_str(),with.size(),
////		Casesensitive );
////}
////
////inline
////tstring
////replace (const tstring	&s,
////		 tstring::size_type			offset,
////		    const tchar* what,
////		    const tchar* with,
////			bool Casesensitive )
////{
////	return replace( s, offset,
////		what,_tcslen( what ),
////		with, _tcslen( with ),
////		Casesensitive );
////}
////
////inline
////tstring
////replace (const tstring	&s,
////		 tstring::size_type			offset,
////		    const tstring& what,
////		    const tstring& with,
////			bool Casesensitive )
////{
////	return replace( s, offset,
////		what.c_str(),what.size( ),
////		with.c_str(), with.size( ),
////		Casesensitive );
////}
////
////inline
////tstring
////replace (const tstring	&s,
////		    const tchar* what,
////		    const tchar* with,
////			bool Casesensitive )
////{
////	return replace( s, 0,
////		what,_tcslen( what ),
////		with, _tcslen( with ),
////		Casesensitive );
////}
////
////inline
////tstring
////replace (const tstring	&s,
////		    const tstring	&what,
////		    const tstring	&with,
////			bool Casesensitive )
////{
////	return replace (s, 0,
////		what.c_str(), what.size(),
////		with.c_str(), with.size(),
////		Casesensitive );
////}
//
///**
// * 删除字符串中指定偏移后的所有指定的字符
// * @param[ in ] s 字符串
// * @param[ in ] what 字符
// * @param[ in ] Casesensitive 是否区分大小写，( true 区分， false 不区分 )
// * @return 返回所有包含what字符串的字符串。
// */
////inline
////tstring
////remove (const tstring	&s,
////		   tchar			what,
////		   tstring::size_type			offset /* = 0 */)
////{ return replace (s, offset, what, "",0); }
////
////tstring
////remove (const tstring	&s,
////		   const tstring	&what,
////		   tstring::size_type			offset /* = 0 */)
////{ return replace (s, offset, what.c_str(),what.size(), "",0); }
//
//inline
//bool startwith( const tchar* str, const tchar* with )
//{
//	if( str == 0 || *str == 0 )
//		return false;
//	if(  with == 0 || *with == 0  )
//		return true;
//
//	while( *with == *str )
//	{
//		if( *with == 0 )
//			return true;
//		if( *str == 0 )
//			return false;
//		with ++;
//		str ++;
//	}
//	return false;
//}
//
//inline
//bool endwith( const tchar* str, const tchar* with )
//{
//	if( str == 0 || *str == 0 )
//		return false;
//	if(  with == 0 || *with == 0  )
//		return true;
//
//	const char* s = str;
//	while( *s != 0 ) s ++;
//	const char* w = with;
//	while( *w != 0 ) w ++;
//
//	while( *w == *s )
//	{
//		if( w == with )
//			return true;
//		if( str == s )
//			return false;
//		w --;
//		s --;
//	}
//	return false;
//}

_jingxian_end

#endif // _STRINGOPS_H_