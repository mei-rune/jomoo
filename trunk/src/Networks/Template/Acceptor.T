
#include "Acceptor.H"

#ifndef ACCEPTORT_TEMPL
#define ACCEPTORT_TEMPL

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */


_networks_begin

template< Accept_Result_T_1 >
Accept_Result_T< Accept_Result_T_2 >::Accept_Result_T( result_type& result ,handler_type& handle,acceptor_type& acceptor  )
: result_( result )
, handle_( handle )
, acceptor_( acceptor )
{
}

template< Accept_Result_T_1 >
size_t Accept_Result_T< Accept_Result_T_2 >::bytes_to_transferred() const
{
	return result_.bytes_to_transferred();
}

template< Accept_Result_T_1 >
void* Accept_Result_T< Accept_Result_T_2 >::act()
{
	return result_.act();
}

template< Accept_Result_T_1 >
bool Accept_Result_T< Accept_Result_T_2 >::success() const
{
	return result_.success();
}

template< Accept_Result_T_1 >
int Accept_Result_T< Accept_Result_T_2 >::error() const
{
	return result_.error();
}


template< Accept_Result_T_1 >
typename Accept_Result_T< Accept_Result_T_2 >::transportptr Accept_Result_T< Accept_Result_T_2 >::new_channel()
{
	return result_.new_channel();
	//return transportptr( new Transport_T< typename result_type::transport_type ,transport_type >( result_.new_channel() ) );
}

template< Accept_Result_T_1 >
typename Accept_Result_T< Accept_Result_T_2 >::handler_type& Accept_Result_T< Accept_Result_T_2 >::handle()
{
	return handle_;
}

template< Accept_Result_T_1 >
typename Accept_Result_T< Accept_Result_T_2 >::acceptor_type& Accept_Result_T< Accept_Result_T_2 >::acceptor()
{
	return acceptor_;
}

template< Accept_Handler_T_1 >
Accept_Handler_T< Accept_Handler_T_2 >::Accept_Handler_T( handler_type& handler ,acceptor_type& acceptor )
: handler_( handler )
, acceptor_( acceptor )
{
}

template< Accept_Handler_T_1 >
void Accept_Handler_T< Accept_Handler_T_2 >::onAccept(result_type& result)
{
	std::auto_ptr< Accept_Handler_T< Accept_Handler_T_2 > > guard( this );
	Accept_Result_T< result_type, handler_type::result_type > r( result , handler_,acceptor_ );
	handler_.onAccept( r );
}

template< Accept_Handler_T_1 >
const tstring& Accept_Handler_T< Accept_Handler_T_2 >::toString() const
{
	return handler_.toString();
}


template< Acceptor_T_1 >
Acceptor_T< Acceptor_T_2 >::Acceptor_T( T* ptr )
: ptr_( ptr )
{
}

template< Acceptor_T_1 >
bool Acceptor_T< Acceptor_T_2 >::accept( handler_type& handle
						, void* act )
{
	std::auto_ptr< Accept_Handler_T< handler_type, T::handler_type > >
	 p( new Accept_Handler_T< handler_type, T::handler_type >( handle, *this ) );
	if( ! ptr_->accept( *p, act ) )
		return false;
	p.release();
	return true;
}

template< Acceptor_T_1 >
bool Acceptor_T< Acceptor_T_2 >::cancel()
{
	return ptr_->cancel();
}

template< Acceptor_T_1 >
const tstring& Acceptor_T< Acceptor_T_2 >::toString() const
{
	return ptr_->toString();
}

_networks_end

#endif //ACCEPTORT_TEMPL