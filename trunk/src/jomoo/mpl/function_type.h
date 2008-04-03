#ifndef function_type_h
#define function_type_h

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

template< typename T>
struct function_type
{
};

template< typename T>
struct function_type<std::unary_function<T,void> >
{
	typedef T arg_type;
};


template<typename R, typename T>
struct function_type< R (T) >
{	
	typedef R result_type;
	typedef T arg_type;
};

template< typename R, typename T>
struct function_type<std::unary_function<T,R> >
{
	typedef R result_type;
	typedef T arg_type;
};

template<typename R, typename T1, typename T2>
struct function_type< R (T1,T2) >
{	
	typedef R result_type;
	typedef T1 arg1_type;
	typedef T2 arg2_type;
};

template<typename R, typename T1, typename T2>
struct function_type< std::binary_function<T1,T2,R> >
{	
	typedef R result_type;
	typedef T1 arg1_type;
	typedef T2 arg2_type;
};

template<typename R, typename T1, typename T2, typename T3>
struct function_type< R (T1,T2,T3) >
{
	typedef R result_type;
	typedef T1 arg1_type;
	typedef T2 arg2_type;
	typedef T3 arg3_type;
};

#endif