


#include "BOE_WIN_Select_Reactor.h"
#include "BOE.Base/Threading/Threading.h"
#include <iostream>
#include "BOE.Base/get_last_error.h"

BOE_WIN_Select_Reactor::BOE_WIN_Select_Reactor( bool result_delete  )
: result_delete_( result_delete )
{

}

BOE_WIN_Select_Reactor::BOE_WIN_Select_Reactor( u_long milli_seconds , bool result_delete  )
: result_delete_( result_delete )
{
	if( open( milli_seconds ) != 0 )
		throw( std::runtime_error("创建完成端口失败"));
}

BOE_WIN_Select_Reactor::~BOE_WIN_Select_Reactor(void)
{
}

int BOE_WIN_Select_Reactor::open ( size_t number_of_threads )
{

	 FD_ZERO(&fdSet_);
   
	return 0;
}

void BOE_WIN_Select_Reactor::close (void)
{
	FD_ZERO(&fdSet_);
}


int BOE_WIN_Select_Reactor::register_handle ( BOE_WIN32_Select_Operation_Result* handle )
{
	if( handle == 0 )
		return -1;
	if( FD_SETSIZE <= container_.size() )
		return -1;

	container_.insert( handle );
	
	FD_SET( handle->getHandle() , &fdSet_);
	return 0;
}

int BOE_WIN_Select_Reactor::unregister_handle ( BOE_WIN32_Select_Operation_Result* handle )
{
	if( handle == 0 )
		return -1;
	container_.erase( handle );
	FD_CLR( handle->getHandle() , &fdSet_);
	if( container_.empty() )
		FD_ZERO(&fdSet_);

	return 0;
}

int BOE_WIN_Select_Reactor::handle_events (unsigned long milli_seconds)
{
	if( container_.empty() )
		return 1;

	fd_set xFdSet;
	fd_set wFdSet;
	memcpy( &xFdSet, &fdSet_, sizeof( fdSet_ ) );
	memcpy( &wFdSet, &fdSet_, sizeof( fdSet_ ) );
	struct timeval tv;
	tv.tv_sec = milli_seconds / 1000;
	tv.tv_usec = (milli_seconds - tv.tv_sec * 1000) * 1000;
	int ret = ::select( 1, 0, &wFdSet, &xFdSet, &tv);
	if( ret == SOCKET_ERROR )
	{
		std::cout << "error : " << get_last_error() << std::endl;
		return -1;
	}
	if( ret == 0 )
		return 1;

	std::set< BOE_WIN32_Select_Operation_Result* > tmp = container_;

	for( std::set< BOE_WIN32_Select_Operation_Result* >::iterator it = tmp.begin()
		 ; it != tmp.end()
		 ; it ++ )
	{
		if( FD_ISSET( (*it)->getHandle() , &wFdSet) )
		{
			application_specific_code( *it, 0, 0, TRUE );
		}
		else if( FD_ISSET( (*it)->getHandle() , &xFdSet) )
		{
			application_specific_code( *it, 0, 0, FALSE );
		}
	}
	return 0;

}

void BOE_WIN_Select_Reactor::application_specific_code (BOE_WIN32_Select_Operation_Result *asynch_result,
															   size_t bytes_transferred,
															   const void *completion_key,
															   BOOL success )
{
	try
	{
		// Call completion hook
		asynch_result->complete (bytes_transferred,
			success ? 0 : 1,
			(void *) completion_key,
			success);
	}
	catch( std::exception& e )
	{
		std::cout << "error :" << e.what() << std::endl;
	}
	catch( ... )
	{	
	}
	if( result_delete_ )
	delete asynch_result;
}


 BOE_WIN_Select_Reactor* BOE_WIN_Select_Reactor::get( BOE_WIN_Select_Reactor* proactor )
{
	static std::auto_ptr< BOE_WIN_Select_Reactor > g_proactor_ptr_;
	static BOE_WIN_Select_Reactor * g_proactor_ = NULL;
	BOE_MUTEX_STATIC( mutex_ );
	if( proactor != 0 )
	{
		if( g_proactor_ != 0 )
			return 0;
		BOE_GUARD( BOE_Mutex,guard, mutex_ );

		if( g_proactor_ != 0 )
			return 0;

		g_proactor_ = proactor;
	}
	else
	{
		if( g_proactor_ != 0 )
			return g_proactor_;

		BOE_GUARD( BOE_Mutex, guard, mutex_ );

		if( g_proactor_ != 0 )
			return g_proactor_;
		if( g_proactor_ptr_.get() == 0 )
		{
			g_proactor_ptr_ .reset( new BOE_WIN_Select_Reactor() );
			if( g_proactor_ptr_ ->open( 0 ) != 0 )
				g_proactor_ptr_.reset( 0 );
		}

		g_proactor_ = g_proactor_ptr_.get();
		
	}
	return g_proactor_;
}
