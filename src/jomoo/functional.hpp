#ifndef functional_hpp
# define functional_hpp

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include <functional>

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
	_Result operator()(T& _Pleft, _Arg _Right) const
		{	// call function with operand
		return ((_Pleft.*_Pmemfun)(_Right));
		}

private:
	_Result (_Ty::*_Pmemfun)(_Arg);	// the member function pointer
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

_jomoo_end

#endif // functional_hpp
