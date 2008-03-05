
/**
 * -*- C++ -*-
 * -------------------------------------------------------------------------------
 * - °Ë®q°–®r ®q°–®r		                       Def.h,v 1.0 2004/12/09 16:01:34
 *  ®u®ê®Ä®Ä®é ®q®q °–®r
 * ¶ÚÃÔ¶ÚÃÔÃÔ| ®t------
 * -------------------------------------------------------------------------------
 */

#ifndef _config_H_
#define _config_H_


#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

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

#define _JOMOO_begin 
#define _JOMOO_end 
#define _hazel 
#define use_hazel 


#define HAVE_ITERATOR

#define DECLARE_NO_COPY_CLASS( CLASS ) CLASS( const CLASS & ); CLASS& operator=( const CLASS & )



#define JOMOO_TEMPLATES_REQUIRE_SOURCE 1
#define JOMOO_TEMPLATE_SPECIALIZATION template< >
//#define JOMOO_MT

#define OS_HAS_INLINED 1

#ifdef OS_HAS_INLINED
#define OS_INLINE inline
#define JOMOO_NAMESPACE_INLINE_FUNCTION inline
#endif //OS_HAS_INLINED


#define JOMOO_HAS_INLINED 1

#ifdef JOMOO_HAS_INLINED
#define JOMOO_INLINE inline
#endif //JOMOO_HAS_INLINED

#define KB_SIZE	1024

#define JOMOO_TM sizeof( void* )
#define JOMOO_LCD_DEF( SIZE , TM ) ( ( (SIZE/ TM ) + (( SIZE%TM ) ? 1 : 0) ) * TM )

inline size_t JOMOO_LCD( size_t SIZE , size_t TM )
{
	return ( ( (SIZE/ TM ) + (( SIZE%TM ) ? 1 : 0) ) * TM );
}

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

#define JOMOO_INTERFACE( X ) 


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

#define JOMOO_BIT_ENABLED( V , F ) ( V&F )

#define JOMOO_WIN32 1

#define JOMOO_UNUSED_ARG( X )

#define MAKE_STRING( X ) #X
#define ASSERT assert



#define null_ptr 0
#endif // _config_H_
