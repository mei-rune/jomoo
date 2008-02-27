#include "StdAfx.h"
#include "Message_Transport_Endpoint.h"

_im_begin

Message_Transport_Endpoint::Message_Transport_Endpoint( Instance_IM& instance , const std::string & addr )
: instance_( instance )
, addr_( addr )
{
	toString_ = "通信端节点[";
	toString_ += addr;
	toString_ += "]";
}

const tstring& Message_Transport_Endpoint::toString( ) const
{
	return toString_;
}

Message_Transport_Endpoint::connector_ptr Message_Transport_Endpoint::connector( ) const
{
	return instance_.createConnector( addr_ );
}

Message_Transport_Endpoint::acceptor_ptr Message_Transport_Endpoint::acceptor( ) const
{
	return instance_.createAcceptor( addr_ );
}

_im_end