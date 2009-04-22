
#ifndef AUTO_PTR_H
#define AUTO_PTR_H

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files

_jingxian_begin


template <typename T>
class AutoFree
{
public:
	static void free( T* t )
	{
		T::release( t );
	}
};

template<class T, class A, class OP = AutoFree<T> >
class auto_ptr
{
public:
	typedef T element_type;

	auto_ptr( ) _THROW0()
		: _Myptr( 0 )
		{
		}
		
	explicit auto_ptr(T *_Ptr  ) _THROW0()
		: _Myptr(_Ptr)
		{
		}

	auto_ptr(auto_ptr<T,A>& _Right) _THROW0()
		: _Myptr( _Right.release() )
		{
		}

	~auto_ptr()
		{
			if( _Myptr != 0 )
				OP::free( _Myptr );
		}

	T& operator*() const _THROW0()
		{
		return (*_Myptr);
		}

	T *operator->() const _THROW0()
		{
		return (&**this);
		}

	T *get() const _THROW0()
		{
		return (_Myptr);
		}

	T *release() _THROW0()
		{	// return wrapped pointer and give up ownership
		T *_Tmp = _Myptr;
		_Myptr = 0;
		return (_Tmp);
		}

	void reset( )
	{
		if( _Tmp != 0 )
			OP::free( alloc_, _Myptr );
	}

	void reset( T * p ) _THROW0()
	{
		T *_Tmp = _Myptr;	// the wrapped object pointer
		_Myptr = p;

		if( _Tmp != 0 )
			OP::free( _Tmp );
	}


private:
	auto_ptr< T,A > operator=( const auto_ptr<T,A>& _Right);

	T *_Myptr;	// the wrapped object pointer
};

template< typename T , typename V >
inline bool is_null( const auto_ptr< T,V > p )
{
	return p.get() == 0;
}

template< typename T , typename V >
inline T* get_ptr( const auto_ptr< T,V > p )
{
	return p.get();
}

_jingxian_end

#endif // AUTO_PTR_H