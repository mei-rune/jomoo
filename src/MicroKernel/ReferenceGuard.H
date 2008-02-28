#ifndef ReferenceGuard_H
# define ReferenceGuard_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"

_micro_kernel_begin

template< typename T
		, typename A >
class GuardRelease
{
public:
	static void release( A& a, T* p )
	{
		a.release( p );
	}
};

template< typename T
		, typename A
		, typename C = GuardRelease< T,A> >
class ReferenceGuard
{
public:
	ReferenceGuard( )
		: p_( null_ptr )
		, a_( null_ptr )
	{
	}
	
	ReferenceGuard( T* p, A& a)
		: p_( p )
		, a_( &a )
	{
	}

	~ReferenceGuard()
	{
			if( 0 != p_ )
				C::release( *a_,p_ );
	}
	void reset( T* p )
	{
		if( !is_null( p_ ) )
				C::release( *a_,p) ;
		p_ = null_ptr;
		a_ = 0;
	}

	void reset( T* p, A& a )
	{
		T* Tmp = p_;
		A* At = a_;
		p_ = p;
		a_ = &a;

		if(! is_null( Tmp ) )
				C::release( *At,Tmp );
	}

	T& operator*() const
		{
		if( is_null( p_ ) )
			ThrowException1( NullException , BT_TEXT("p_") );

		return (*p_);
		}

	T *operator->() const _THROW0()
		{	// return pointer to class object
		return (&**this);
		}

	T *get() const _THROW0()
		{	// return wrapped pointer
		return (p_);
		}

	T *release() _THROW0()
		{	// return wrapped pointer and give up ownership
		T *_Tmp = p_;
		p_ = 0;
		return (_Tmp);
		}

private:
	ReferenceGuard< T,A,C > operator=( const ReferenceGuard< T,A,C >& _Right);

	T* p_;
	A* a_;
};

template< typename T , typename V , typename C >
inline bool is_null( const ReferenceGuard< T,V,C > p )
{
	return p.get() == 0;
}

template< typename T , typename V , typename C >
inline T* get_ptr( const ReferenceGuard< T,V,C > p )
{
	return p.get();
}

//template< typename T ,typename B typename V , typename C >
//inline ReferenceGuard< T,V,C > dynamicCast( ReferenceGuard< B,V,C >const& p )
//{
//	T* t = dynamic_cast< T*>( p );
//	if( t == 0 )
//		ThrowException1( CastException , ",dynamicCast" ); 
//	return std::auto_ptr< T >( t );
//}

_micro_kernel_end

#endif // ReferenceGuard_H
