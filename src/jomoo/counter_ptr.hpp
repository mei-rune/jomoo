

#ifndef COUNTER_PTR_H
#define COUNTER_PTR_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "boost/smart_ptr.hpp"
# include "jomoo/exception.hpp"
#include "Platform/OS.H"

#define counter_ptr boost::shared_ptr


template< typename T >
inline bool is_null( const counter_ptr< T >& t )
{
	return ( t.get() == 0 );
}

template< typename T >
inline bool is_null( const std::auto_ptr< T >& t )
{
	return ( t.get() == 0 );
}

template< typename T >
inline T* get_ptr( counter_ptr< T >& t )
{
	return t.get();
}

template< typename T >
inline T* get_ptr( std::auto_ptr< T >& t )
{
	return t.get();
}

class counter
{
public:
	counter( long value = 0 )
		: counter_( value )
	{
	}

	long increment( )
	{
		return OS::InterlockedIncrement( counter_ );
	}
	
	long decrement( )
	{
		return OS::InterlockedDecrement( counter_ );
	}

private:
	DECLARE_NO_COPY_CLASS( counter );
	long counter_;
};

class jomoo_shared
{
public:
	virtual ~jomoo_shared(){}
    virtual void incRef() = 0;
    virtual void decRef() = 0;
};

#define DECLARE_SHARED( )		public:			\
    virtual void incRef();						\
    virtual void decRef();						\
	private:									\
		counter counter_


#define DEFINE_SHARED( X )		void X :: incRef(){ counter_.increment( ); }					\
								void X :: decRef()												\
								{																\
									long r = counter_.decrement( );								\
									if( r <= 0 ) delete this;									\
								}

inline      void intrusive_ptr_add_ref( jomoo_shared * p)
{
	if( p == 0 )
		ThrowException( InvalidPointerException );
	p->incRef();
}

inline      void intrusive_ptr_release( jomoo_shared * p)
{
	if( p == 0 )
		ThrowException( InvalidPointerException );
	p->decRef();
}


#define intrusive_ptr boost::intrusive_ptr

template< typename T >
inline bool is_null( const intrusive_ptr< T >& t )
{
	return ( t.get() == 0 );
}

template< typename T >
inline T* get_ptr( intrusive_ptr< T >& t )
{
	return t.get();
}

template< typename T , typename B >
inline counter_ptr< T > dynamicCast( counter_ptr< B >const& p )
{
	return counter_ptr< T >( p , boost::detail::dynamic_cast_tag() );
}

template< typename T , typename B >
inline intrusive_ptr< T > dynamicCast( intrusive_ptr< B >const& p )
{
	return intrusive_ptr< T >( p , boost::detail::dynamic_cast_tag() );
}

template< typename T , typename B >
inline std::auto_ptr< T > dynamicCast( std::auto_ptr< B >const& p )
{
	T* t = dynamic_cast< T*>( p );
	if( t == 0 )
		ThrowException1( CastException , ",dynamicCast" ); 
	return std::auto_ptr< T >( t );
}

template< typename T , typename B >
inline T* dynamicCast( B* p )
{
	T* t = dynamic_cast< T* >( p );
	if( t == 0 )
		ThrowException1( CastException , ",dynamicCast" ); 
	return t;
}

#endif //COUNTER_PTR_H