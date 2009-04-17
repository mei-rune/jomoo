
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		                       Def.h,v 1.0 2004/12/09 16:01:34
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _config_h_
#define _config_h_


#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_   /* Prevent inclusion of winsock.h in windows.h */
#endif // _WINSOCKAPI_

#include "windows.h"

#ifndef _u_char_
#define _u_char_
typedef unsigned char u_char;
#endif // _u_char_

#ifndef _u_short_
#define _u_short_
typedef unsigned short u_short;
#endif // _u_short_

#ifndef _n_short_
#define _n_short_
typedef short n_short;
#endif // n_short

#ifndef _n_time_
#define _n_time_
typedef unsigned long n_time;
#endif //_n_time_

#ifndef _u_long_
#define _u_long_
typedef unsigned long u_long;
#endif // _u_long_

#ifndef _u_int_
#define _u_int_
typedef unsigned int  u_int;
#endif // _u_int_

#ifndef _u_char_t_
#define _u_char_t_
typedef unsigned char u_char_t;
#endif //_u_char_t_

#ifndef _u_short_t_
#define _u_short_t_
typedef unsigned short u_short_t;
#endif // _u_short_t_

#ifndef _n_short_t_
#define _n_short_t_
typedef short n_short_t;
#endif // n_short_t

#ifndef _u_int_t_
#define _u_int_t_
typedef unsigned int  u_int_t;
#endif // u_int_t

#ifndef _u_int8_t_
#define _u_int8_t_
typedef unsigned char u_int8_t;
#endif // _u_int16_t_

#ifndef _u_int16_t_
#define _u_int16_t_
typedef unsigned short u_int16_t;
#endif // _u_int16_t_

#ifndef _u_int32_t_
#define _u_int32_t_
typedef unsigned int u_int32_t;
#endif // _u_int16_t_

#ifndef _u_int64_t_
#define _u_int64_t_
typedef unsigned __int64 u_int64_t;
#endif // _u_int16_t_

#ifndef __GNUG__

#ifndef _ssize_t_
#define _ssize_t_
typedef int ssize_t;
#endif // _ssize_t_


#ifndef _int8_t_
#define _int8_t_
typedef char int8_t;
#endif // _int16_t_

#ifndef _int16_t_
#define _int16_t_
typedef short int16_t;
#endif // _int16_t_

#ifndef _int32_t_
#define _int32_t_
typedef int int32_t;
#endif // _int32_t_

#ifndef _int64_t_
#define _int64_t_
typedef  __int64 int64_t;
#endif // _u_int64_t_

#endif

#ifndef _Byte_
#define _Byte_
typedef char Byte;
#endif // _Byte_

#ifndef _Int16_
#define _Int16_
typedef short Int16;
#endif //_Int16_

#ifndef _Int32_
#define _Int32_
typedef int Int32;
#endif // Int32

#ifndef _Int64_
#define _Int64_
typedef __int64 Int64;
#endif //

#ifndef _Float_
#define _Float_
typedef float Float;
#endif // _Float_

#ifndef _Double_
#define _Double_
typedef double Double;
#endif //

#ifndef _off_t
typedef long _off_t;
#endif //


#ifndef off_t
typedef _off_t off_t;
#endif //

#define _jingxian_begin
#define _jingxian_end
#define _jingxian
#define use_jingxian


#define HAVE_ITERATOR

#define NOCOPY( CLASS ) CLASS( const CLASS & ); CLASS& operator=( const CLASS & )


# ifdef HAVE_ITERATOR
#  define ITERATOR_BASE(cat,val,diff)	: public std::iterator<std::cat##_tag,val,diff>
# elif HAVE_ITERATOR_TRAITS
#  define ITERATOR_BASE(cat,val,diff)
# else
#  define ITERATOR_BASE(cat,val,diff)	: public std::cat<val,diff>
# endif

# ifdef HAVE_REVERSE_ITERATOR_STYLE
#  define REVERSE_ITERATOR(tname,tag,iter,value,reference,pointer,difference) \
	std::reverse_iterator<iter>
# elif HAVE_REVERSE_ITERATOR_STYLE == 2
#  define REVERSE_ITERATOR(tname,tag,iter,value,reference,pointer,difference) \
	std::reverse_iterator<iter,std::tag,value,reference,pointer,difference>
# elif HAVE_REVERSE_ITERATOR_STYLE == 3
#  define REVERSE_ITERATOR(tname,tag,iter,value,reference,pointer,difference) \
	std::tname<iter,value,reference,pointer,difference>
# elif HAVE_REVERSE_ITERATOR_STYLE == 4
#  define REVERSE_ITERATOR(tname,tag,iter,value,reference,pointer,difference) \
	std::os_##tname<iter,value,reference,pointer,difference>
# else
#  define REVERSE_ITERATOR(tname,tag,iter,value,reference,pointer,difference) \
	I_don_t_know_how_to_define_reverse_iterator
# endif


template< typename T >
inline bool is_null( T t )
{
	return ( NULL == t );
}

template< typename T >
inline T get_ptr( T t )
{
	return t;
}

#define JINGXIAN_BIT_ENABLED( V , F ) ( V&F )

#define JINGXIAN_WIN32 1

#define JINGXIAN_UNUSED_ARG( X )

#define MAKE_STRING( X ) #X
#define ASSERT assert

#define OS_HAS_INLINED 1

#if defined (OS_HAS_INLINED)
#define OS_INLINE inline
#else
#define OS_INLINE
#endif

//#define JINGXIAN_HAS_INLINED 1

#if defined (JINGXIAN_HAS_INLINED)
#define JINGXIAN_INLINE inline
#else
#define JINGXIAN_INLINE
#endif

#define jingxian_assert assert

#define null_ptr NULL

#ifdef __GNUG__
#define _T L
#endif

typedef  int errno_t;

#ifdef __GNUG__
#define _THROW0() throw()
#endif

#ifdef __GNUG__
#define __MSVCRT_VERSION__ 0x0700
#endif

#endif // _config_h_
