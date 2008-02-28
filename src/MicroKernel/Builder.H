//#ifndef BUILDER_H
//# define BUILDER_H
//
//#include "config.h"
//
//#if !defined (BOE_LACKS_PRAGMA_ONCE)
//# pragma once
//#endif /* BOE_LACKS_PRAGMA_ONCE */
//
//// Include files
//# include "config_MicroKernel.h"
//# include "MicroKernel.h"
//# include "BOE.Base/Memory/memory.h"
//
//_micro_kernel_begin
//
//template< typename B
//		, typename T
//		, typename D
//		, typename TR 
//		, typename POOL = _memory pool
//		>
//class Builder : public D
//{
//public :
//	typedef _memory Pool_T< T , POOL > pool_type;
//	Builder( typename pool_type::pool_ptr_type _pool , const tstring& name )
//		: pool_( _pool , name )
//	{
//	}
//
//	virtual ~Builder()
//	{
//	}
//
//	template< typename P >
//	B* create( P p )
//	{
//		_memory auto_ptr< T, pool_type > handler( pool_.malloc() , pool_ );
//		TR::init( get_ptr( handler ) , p );
//		return handler.release();
//	}
//	template< typename P1 ,typename P2 >
//	B* create( P1 p1 ,P2 p2 )
//	{
//		_memory auto_ptr< T, pool_type > handler( pool_.malloc() , pool_ );
//		TR::init( get_ptr( handler ) , p1, p2 );
//		return handler.release();
//	}
//
//	virtual void release( B* h )
//	{
//		if( h == 0 )
//			return ;
//		_memory auto_ptr< T, pool_type > handler( dynamicCast< T, B >( h ), pool_  );
//		if( !isNone( handler ) )
//			TR::fini( get_ptr( handler ) );
//	}
//private:
//	pool_type pool_;
//};
//
//_micro_kernel_end
//
//#endif // BUILDER_H
