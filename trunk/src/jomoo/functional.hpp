#ifndef functional_hpp
# define functional_hpp

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include <functional>
# ifdef HAS_BOOST
# include "boost/tr1/memory.hpp"
# else
# include <tr1/memory>
# endif

_jomoo_begin

template<class _Result,
	class _Ty>
	class mem_fun_t
		: public std::unary_function<_Ty *, _Result>
	{	// functor adapter (*p->*pfunc)(), non-const *pfunc
public:
	explicit mem_fun_t(_Result (_Ty::*_Pm)())
		: _Pmemfun(_Pm)
		{	// construct from pointer
		}

	template< class T>
	_Result operator()(T _Pleft) const
		{	// call function
			return ( (_Pleft->*_Pmemfun)());
		}

	template< class T>
	_Result operator()(std::tr1::shared_ptr<T> _Pleft) const
		{	// call function
			return ( (_Pleft.get()->*_Pmemfun)());
		}

private:
	_Result (_Ty::*_Pmemfun)();	// the member function pointer
	};

		// TEMPLATE CLASS mem_fun1_t
template<class _Result,
	class _Ty,
	class _Arg>
	class mem_fun1_t
		: public std::binary_function<_Ty *, _Arg, _Result>
	{	// functor adapter (*p->*pfunc)(val), non-const *pfunc
public:
	explicit mem_fun1_t(_Result (_Ty::*_Pm)(_Arg))
		: _Pmemfun(_Pm)
		{	// construct from pointer
		}

	template< class T >
	_Result operator()(T _Pleft, _Arg _Right) const
		{	// call function with operand
		return ((_Pleft->*_Pmemfun)(_Right));
		}

	template< class T >
	_Result operator()(std::tr1::shared_ptr<T> _Pleft, _Arg _Right) const
		{	// call function with operand
		return ((_Pleft.get()->*_Pmemfun)(_Right));
		}

private:
	_Result (_Ty::*_Pmemfun)(_Arg);	// the member function pointer
	};

	

		// TEMPLATE CLASS mem_fun1_t
template<class _Result,
	class _Ty,
	class _Arg1,
	class _Arg2>
	class mem_fun2_t
	{	// functor adapter (*p->*pfunc)(val), non-const *pfunc
public:
	explicit mem_fun2_t(_Result (_Ty::*_Pm)(_Arg1,_Arg2))
		: _Pmemfun(_Pm)
		{	// construct from pointer
		}

	template< class T >
	_Result operator()(T _Pleft, _Arg1 _Right1, _Arg2 _Right2) const
		{	// call function with operand
		return ((_Pleft->*_Pmemfun)(_Right1,_Right2));
		}

	template< class T >
	_Result operator()(std::tr1::shared_ptr<T> _Pleft, _Arg1 _Right1, _Arg2 _Right2) const
		{	// call function with operand
		return ((_Pleft.get()->*_Pmemfun)(_Right1,_Right2));
		}

private:
	_Result (_Ty::*_Pmemfun)(_Arg1,_Arg2);	// the member function pointer
	};

	template<class _Result,
class _Ty> inline
mem_fun_t<_Result, _Ty> mem_fun(_Result (_Ty::*_Pm)())
{	// return a mem_fun_t functor adapter
	return (mem_fun_t<_Result, _Ty>(_Pm));
}

template<class _Result,
	class _Ty,
	class _Arg> inline
mem_fun1_t<_Result, _Ty, _Arg> mem_fun(_Result (_Ty::*_Pm)(_Arg))
{	// return a mem_fun1_t functor adapter
	return (mem_fun1_t<_Result, _Ty, _Arg>(_Pm));
}

template<class _Result,
	class _Ty,
	class _Arg1,
	class _Arg2> inline
mem_fun2_t<_Result, _Ty, _Arg1, _Arg2> mem_fun(_Result (_Ty::*_Pm)(_Arg1,_Arg2))
{	// return a mem_fun1_t functor adapter
	return (mem_fun2_t<_Result, _Ty, _Arg1, _Arg2>(_Pm));
}


	// TEMPLATE CLASS pointer_to_binary_function
template<class _Arg1,
	class _Arg2,
	class _Arg3,
	class _Result,
	class _Fn = _Result (*)(_Arg1, _Arg2, _Arg3)>
	class pointer_function3_t
	{	// functor adapter (*pfunc)(left, right)
public:
	explicit pointer_function3_t(_Fn _Left)
		: _Pfun(_Left)
		{	// construct from pointer
		}

	_Result operator()(_Arg1 _x1, _Arg2 _x2, _Arg3 _x3) const
		{	// call function with operands
		return (_Pfun(_x1, _x2, _x3));
		}

protected:
	_Fn _Pfun;	// the function pointer
	};

		// TEMPLATE FUNCTION ptr_fun
template<class _Arg1,
	class _Arg2,
	class _Arg3,
	class _Result> inline
	pointer_function3_t<_Arg1, _Arg2, _Arg3, _Result, _Result(__cdecl *)(_Arg1, _Arg2, _Arg3)>
		ptr_fun(_Result (__cdecl *_Left)(_Arg1, _Arg2, _Arg3))
	{	// return pointer_to_binary_function functor adapter
	return (pointer_function3_t<_Arg1, _Arg2, _Arg3, _Result, _Result (__cdecl *)(_Arg1, _Arg2, _Arg3)>(_Left));
	}

_jomoo_end

#endif // functional_hpp
