#ifndef AUTO_PTR_H
#define AUTO_PTR_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_Memory.H"
# include "MemoryManager.H"
# include "../Collections/ThreadSafePtrQueue.HPP"

_memory_begin

class AutoFree
{
public:
	template< typename T, typename A >
	static void free( A* a, T* t )
	{
		a->free( t );
	}
};

template<class T, class A, class OP = AutoFree >
	class auto_ptr
		{
public:
	typedef T element_type;
    typedef A allocator_type;

	auto_ptr( ) _THROW0()
		: _Myptr( 0 )
		, alloc_( 0 )
		{
		}
		
	auto_ptr(T *_Ptr , A& _alloc ) _THROW0()
		: _Myptr(_Ptr)
		, alloc_( &_alloc )
		{
		}

	auto_ptr(auto_ptr<T,A>& _Right) _THROW0()
		: _Myptr(_Right._Myptr)
		, alloc_( _Right.alloc_ )
		{
			_Right.release();
		}

	~auto_ptr()
		{
			if( _Myptr != 0 )
				OP::free( alloc_, _Myptr );
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
		alloc_ = 0;
		return (_Tmp);
		}

	void reset( )
	{
		if( _Tmp != 0 )
			OP::free( alloc_, _Myptr );
	}

	void reset( T * p, A& alloc ) _THROW0()
	{
		T *_Tmp = _Myptr;	// the wrapped object pointer
		A *_alloc = alloc_;
		_Myptr = p;
		alloc_ = &alloc;

		if( _Tmp != 0 )
			OP::free( _alloc, _Tmp );
	}


private:
	auto_ptr< T,A > operator=( const auto_ptr<T,A>& _Right);

	T *_Myptr;	// the wrapped object pointer
	A *alloc_;
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

_memory_end

#endif // AUTO_PTR_H