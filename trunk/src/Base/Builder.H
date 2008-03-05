#ifndef BUILDER_H
# define BUILDER_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "Memory/memory.h"
# include "macro/macro_params.hpp"

_JOMOO_begin

template< typename B
		>
class BuilderOP
{
public :

	static void Init( B b )
	{
		b->init( );
	}

	template< JOMOO_MAKE_PARAMS1( 1, typename T) >
	static void Init( B* b, JOMOO_MAKE_PARAMS2( 1, T, a) )
	{
		b->init( JOMOO_MAKE_PARAMS1( 1, a) );
	}

	template< JOMOO_MAKE_PARAMS1( 2, typename T) >
	static void Init( B* b, JOMOO_MAKE_PARAMS2( 2, T, a) )
	{

		b->init( JOMOO_MAKE_PARAMS1( 2, a) );

	}

	template< JOMOO_MAKE_PARAMS1( 3, typename T) >
	static void Init( B* b, JOMOO_MAKE_PARAMS2( 3, T, a) )
	{

		b->init( JOMOO_MAKE_PARAMS1( 3, a) );

	}

	template< JOMOO_MAKE_PARAMS1( 4, typename T) >
	static void Init( B* b, JOMOO_MAKE_PARAMS2( 4, T, a) )
	{

		b->init( JOMOO_MAKE_PARAMS1( 4, a) );

	}

		template< JOMOO_MAKE_PARAMS1( 5, typename T) >
	static void Init( B* b, JOMOO_MAKE_PARAMS2( 5, T, a) )
	{

		b->init( JOMOO_MAKE_PARAMS1( 5, a) );

	}

	template< JOMOO_MAKE_PARAMS1( 6, typename T) >
	static void Init( B* b, JOMOO_MAKE_PARAMS2( 6, T, a) )
	{

		b->init( JOMOO_MAKE_PARAMS1( 6, a) );

	}
	
	template< JOMOO_MAKE_PARAMS1( 7, typename T) >
	static void Init( B* b, JOMOO_MAKE_PARAMS2( 7, T, a) )
	{

		b->init( JOMOO_MAKE_PARAMS1( 7, a) );

	}

	template< JOMOO_MAKE_PARAMS1( 8, typename T) >
	static void Init( B* b, JOMOO_MAKE_PARAMS2( 8, T, a) )
	{

		b->init( JOMOO_MAKE_PARAMS1( 8, a) );

	}

	template< JOMOO_MAKE_PARAMS1( 9, typename T) >
	static void Init( B* b, JOMOO_MAKE_PARAMS2( 9, T, a) )
	{

		b->init( JOMOO_MAKE_PARAMS1( 9, a) );

	}

	template< JOMOO_MAKE_PARAMS1( 10, typename T) >
	static void Init( B* b, JOMOO_MAKE_PARAMS2( 10, T, a) )
	{

		b->init( JOMOO_MAKE_PARAMS1( 10, a) );
	}

	static void Fini( B* h )
	{
		h->fini();
	}
};



template< typename B
		, typename R
		, typename D
		, typename P = _memory pool
		, typename POOL = _memory Pool_T< R , P >
		, template< typename S > class OP = BuilderOP
		>
class Builder : public D
{
public :

	class AutoFree
	{
	public:
		template< typename T, typename A >
			static void free( A* a, T* t )
		{
			a->release( t );
		}
	};

	typedef Builder< B,R,D,P,POOL, OP > this_type;
	typedef _memory auto_ptr< B, this_type, AutoFree > auto_ptr;

	typedef POOL pool_type;

	Builder( typename pool_type::pool_ptr_type _pool , const tstring& name )
		: pool_( _pool , name )
	{
	}

	virtual ~Builder()
	{
	}

	B* create( )
	{
		_memory auto_ptr< R, pool_type > handler( pool_.malloc() , pool_ );
		OP< R >::Init( handler.get() );
		return handler.release();
	}

	template< JOMOO_MAKE_PARAMS1( 1, typename T) >
	B* create( JOMOO_MAKE_PARAMS2( 1, T, a) )
	{
		_memory auto_ptr< R, pool_type > handler( pool_.malloc() , pool_ );
		OP< R >::Init( handler.get() , JOMOO_MAKE_PARAMS1( 1, a) );
		return handler.release();
	}

	template< JOMOO_MAKE_PARAMS1( 2, typename T) >
	B* create( JOMOO_MAKE_PARAMS2( 2, T, a) )
	{
		_memory auto_ptr< R, pool_type > handler( pool_.malloc() , pool_ );
		OP< R >::Init( handler.get() , JOMOO_MAKE_PARAMS1( 2, a) );
		return handler.release();
	}

	template< JOMOO_MAKE_PARAMS1( 3, typename T) >
	B* create( JOMOO_MAKE_PARAMS2( 3, T, a) )
	{
		_memory auto_ptr< R, pool_type > handler( pool_.malloc() , pool_ );
		OP< R >::Init( handler.get() , JOMOO_MAKE_PARAMS1( 3, a) );
		return handler.release();
	}

	template< JOMOO_MAKE_PARAMS1( 4, typename T) >
	B* create( JOMOO_MAKE_PARAMS2( 4, T, a) )
	{
		_memory auto_ptr< R, pool_type > handler( pool_.malloc() , pool_ );
		OP< R >::Init( handler.get() , JOMOO_MAKE_PARAMS1( 4, a) );
		return handler.release();
	}

		template< JOMOO_MAKE_PARAMS1( 5, typename T) >
	B* create( JOMOO_MAKE_PARAMS2( 5, T, a) )
	{
		_memory auto_ptr< R, pool_type > handler( pool_.malloc() , pool_ );
		OP< R >::Init( handler.get() , JOMOO_MAKE_PARAMS1( 5, a) );
		return handler.release();
	}

	template< JOMOO_MAKE_PARAMS1( 6, typename T) >
	B* create( JOMOO_MAKE_PARAMS2( 6, T, a) )
	{
		_memory auto_ptr< R, pool_type > handler( pool_.malloc() , pool_ );
		OP< R >::Init( handler.get() , JOMOO_MAKE_PARAMS1( 6, a) );
		return handler.release();
	}
	
	template< JOMOO_MAKE_PARAMS1( 7, typename T) >
	B* create( JOMOO_MAKE_PARAMS2( 7, T, a) )
	{
		_memory auto_ptr< R, pool_type > handler( pool_.malloc() , pool_ );
		OP< R >::Init( handler.get() , JOMOO_MAKE_PARAMS1( 7, a) );
		return handler.release();
	}

	template< JOMOO_MAKE_PARAMS1( 8, typename T) >
	B* create( JOMOO_MAKE_PARAMS2( 8, T, a) )
	{
		_memory auto_ptr< R, pool_type > handler( pool_.malloc() , pool_ );
		OP< R >::Init( handler.get() , JOMOO_MAKE_PARAMS1( 8, a) );
		return handler.release();
	}

	template< JOMOO_MAKE_PARAMS1( 9, typename T) >
	B* create( JOMOO_MAKE_PARAMS2( 9, T, a) )
	{
		_memory auto_ptr< R, pool_type > handler( pool_.malloc() , pool_ );
		OP< R >::Init( handler.get() , JOMOO_MAKE_PARAMS1( 9, a) );
		return handler.release();
	}

	template< JOMOO_MAKE_PARAMS1( 10, typename T) >
	B* create( JOMOO_MAKE_PARAMS2( 10, T, a) )
	{
		_memory auto_ptr< R, pool_type > handler( pool_.malloc() , pool_ );
		OP< R >::Init( handler.get() , JOMOO_MAKE_PARAMS1( 10, a) );
		return handler.release();
	}

	virtual void release( B* h )
	{
		if( h == 0 )
			return ;
		_memory auto_ptr< R, pool_type > handler( dynamicCast< R, B >( h ), pool_  );
		if( handler.get() != NULL )
			OP< R >::Fini( handler.get() );
	}
private:
	pool_type pool_;
};


_JOMOO_end

#endif // NETWORKS_BUILDER_H
