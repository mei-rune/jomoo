
#include "connector.H"

#ifndef CONNECTORT_TEMPL
#define CONNECTORT_TEMPL

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "Transport.H"

_networks_begin

template< Connect_Result_T_1 >
Connect_Result_T< Connect_Result_T_2 >::Connect_Result_T( result_type& result,handler_type& handler,connector_type& connector )
: result_( result )
, handler_( handler )
, connector_( connector )
{
}

//template< Connect_Result_T_1 >
//size_t Connect_Result_T< Connect_Result_T_2 >::bytes_to_transferred() const
//{
//	return result_.bytes_to_transferred();
//}

template< Connect_Result_T_1 >
void* Connect_Result_T< Connect_Result_T_2 >::act()
{
	return result_.act();
}

template< Connect_Result_T_1 >
bool Connect_Result_T< Connect_Result_T_2 >::success() const
{
	return result_.success();
}

template< Connect_Result_T_1 >
int Connect_Result_T< Connect_Result_T_2 >::error() const
{
	return result_.error();
}


template< Connect_Result_T_1 >
typename Connect_Result_T< Connect_Result_T_2 >::transportptr Connect_Result_T< Connect_Result_T_2 >::new_channel()
{
	return result_.new_channel();
	//return transportptr( new Transport_T< typename result_type::transport_type ,transport_type >( result_.new_channel() ) );
}

template< Connect_Result_T_1 >
typename Connect_Result_T< Connect_Result_T_2 >::handler_type& Connect_Result_T< Connect_Result_T_2 >::handle()
{
	return handler_;
}

template< Connect_Result_T_1 >
typename Connect_Result_T< Connect_Result_T_2 >::connector_type& Connect_Result_T< Connect_Result_T_2 >::connector()
{
	return connector_;
}

template< Connect_Handler_T_1 >
Connect_Handler_T< Connect_Handler_T_2 >::Connect_Handler_T( handler_type& handler, connector_type& connector )
: handler_( handler )
, connector_( connector )
{
}

template< Connect_Handler_T_1 >
void Connect_Handler_T< Connect_Handler_T_2 >::onConnect(result_type& result)
{
	std::auto_ptr< Connect_Handler_T< Connect_Handler_T_2 > > guard( this );
	Connect_Result_T< result_type, handler_type::result_type > r( result , handler_, connector_ );
	handler_.onConnect( r );
}

template< Connect_Handler_T_1 >
const tstring& Connect_Handler_T< Connect_Handler_T_2 >::toString() const
{
	return handler_.toString();
}


template< Connector_T_1 >
Connector_T< Connector_T_2 >::Connector_T( T* ptr )
: ptr_( ptr )
{
}

template< Connector_T_1 >
bool Connector_T< Connector_T_2 >::connect( handler_type& handle
						, void* act )
{

	std::auto_ptr< Connect_Handler_T< handler_type, T::handler_type > > 
	p( new Connect_Handler_T< handler_type, T::handler_type >( handle , *this ) );
	if( ! ptr_->connect( *p, act ) )
		return false;
	p.release();
	return true;
}

template< Connector_T_1 >
bool Connector_T< Connector_T_2 >::cancel()
{
	return ptr_->cancel();
}

template< Connector_T_1 >
const tstring& Connector_T< Connector_T_2 >::toString() const
{
	return ptr_->toString();
}

_networks_end

#endif //CONNECTORT_TEMPL