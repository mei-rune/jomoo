
#include "Transport.H"

#ifndef TRANSPORTT_TEMPL
#define TRANSPORTT_TEMPL

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */


_networks_begin

template< Read_Result_T_1 >
Read_Result_T< Read_Result_T_2 >::Read_Result_T( result_type& result , handler_type& handler ,transport_type& transport )
: result_( result )
, handler_( handler )
, transport_( transport )
{
}

template< Read_Result_T_1 >
void* Read_Result_T< Read_Result_T_2 >::act()
{
	return result_.act();
}

template< Read_Result_T_1 >
bool Read_Result_T< Read_Result_T_2 >::success() const
{
	return result_.success();
}

template< Read_Result_T_1 >
int Read_Result_T< Read_Result_T_2 >::error() const
{
	return result_.error();
}

template< Read_Result_T_1 >
size_t Read_Result_T< Read_Result_T_2 >::bytes_to_transferred() const
{
	return result_.bytes_to_transferred();
}

template< Read_Result_T_1 >
typename Read_Result_T< Read_Result_T_2 >::handler_type& Read_Result_T< Read_Result_T_2 >::handle()
{
	return handler_;
}

template< Read_Result_T_1 >
typename Read_Result_T< Read_Result_T_2 >::transport_type& Read_Result_T< Read_Result_T_2 >::transport()
{
	return transport_;
}


template< Read_Result_T_1 >
void* Read_Result_T< Read_Result_T_2 >::buffer()
{
	return result_.buffer();
}

template< Read_Result_T_1 >
const void* Read_Result_T< Read_Result_T_2 >::buffer() const
{
	return result_.buffer();
}

template< Read_Result_T_1 >
size_t Read_Result_T< Read_Result_T_2 >::length() const
{
	return result_.length();
}

#define RESULT_DEFINE( X )		template< X##_1 >								\
X< X##_2 >::X( result_type& result  , handler_type& handler, transport_type& transport )					\
: result_( result )																\
, handler_( handler )															\
, transport_( transport )														\
{																				\
}																				\
																				\
template< X##_1 >																\
void* X< X##_2 >::act()															\
{																				\
	return result_.act();														\
}																				\
																				\
template< X##_1 >																\
bool X< X##_2 >::success() const												\
{																				\
	return result_.success();													\
}																				\
																				\
template< X##_1 >																\
int X< X##_2 >::error() const													\
{																				\
	return result_.error();														\
}																				\
																				\
template< X##_1 >																\
size_t X< X##_2 >::bytes_to_transferred() const									\
{																				\
	return result_.bytes_to_transferred();										\
}																				\
																				\
template< X##_1 >																\
typename X< X##_2 >::handler_type& X< X##_2 >::handle()							\
{																				\
	return handler_;															\
}																				\
																				\
template< X##_1 >																\
typename X< X##_2 >::transport_type& X< X##_2 >::transport()					\
{																				\
	return transport_;															\
}

RESULT_DEFINE( Read_Array_Result_T );

template< Read_Array_Result_T_1 >
iovec* Read_Array_Result_T< Read_Array_Result_T_2 >::data()
{
	return result_.data();
}

template< Read_Array_Result_T_1 >
size_t Read_Array_Result_T< Read_Array_Result_T_2 >::size() const
{
	return result_.size();
}

RESULT_DEFINE( Write_Result_T );

template< Write_Result_T_1 >
const void* Write_Result_T< Write_Result_T_2 >::buffer() const
{
	return result_.buffer();
}

template< Write_Result_T_1 >
size_t Write_Result_T< Write_Result_T_2 >::length() const
{
	return result_.length();
}

RESULT_DEFINE( Write_Array_Result_T );

template< Write_Array_Result_T_1 >
const iovec* Write_Array_Result_T< Write_Array_Result_T_2 >::data()
{
	return result_.data();
}

template< Write_Array_Result_T_1 >
size_t Write_Array_Result_T< Write_Array_Result_T_2 >::size() const
{
	return result_.size();
}

RESULT_DEFINE( Transmit_Result_T );

template< Transmit_Result_T_1 >
const iopack* Transmit_Result_T< Transmit_Result_T_2 >::data()
{
	return result_.data();
}

template< Transmit_Result_T_1 >
size_t Transmit_Result_T< Transmit_Result_T_2 >::size() const
{
	return result_.size();
}

template< Transport_Handler_T_1 >
Transport_Handler_T< Transport_Handler_T_2 >::Transport_Handler_T( handler_type& handler,transport_type& transport )
: handler_( handler )
, transport_( transport )
{
}

template< Transport_Handler_T_1 >
void Transport_Handler_T< Transport_Handler_T_2 >::onRead(read_result_type& result)
{
	std::auto_ptr< Transport_Handler_T< Transport_Handler_T_2 > > guard( this );
	Read_Result_T< read_result_type, T::read_result_type > r( result , handler_,transport_ );
	handler_.onRead( r );
}

template< Transport_Handler_T_1 >
void Transport_Handler_T< Transport_Handler_T_2 >::onReadArray(read_array_result_type& result )
{
	std::auto_ptr< Transport_Handler_T< Transport_Handler_T_2 > > guard( this );
	Read_Array_Result_T< read_array_result_type, T::read_array_result_type > r( result , handler_,transport_ );
	handler_.onReadArray( r );
}

template< Transport_Handler_T_1 >
void Transport_Handler_T< Transport_Handler_T_2 >::onWrite(write_result_type& result)
{
	std::auto_ptr< Transport_Handler_T< Transport_Handler_T_2 > > guard( this );
	Write_Result_T< write_result_type, T::write_result_type > r( result , handler_,transport_ );
	handler_.onWrite( r );
}

template< Transport_Handler_T_1 >
void Transport_Handler_T< Transport_Handler_T_2 >::onWriteArray(write_array_result_type& result)
{
	std::auto_ptr< Transport_Handler_T< Transport_Handler_T_2 > > guard( this );
	Write_Array_Result_T< write_array_result_type, T::write_array_result_type > r( result , handler_,transport_ );
	handler_.onWriteArray( r );
}
template< Transport_Handler_T_1 >
void Transport_Handler_T< Transport_Handler_T_2 >::onTransmit(transmit_result_type& result )
{
	std::auto_ptr< Transport_Handler_T< Transport_Handler_T_2 > > guard( this );
	Transmit_Result_T< transmit_result_type, T::transmit_result_type > r( result , handler_,transport_ );
	handler_.onTransmit( r );
}

template< Transport_Handler_T_1 >
const tstring& Transport_Handler_T< Transport_Handler_T_2 >::toString() const
{
	return handler_.toString();
}
	
template< Transport_T_1 >
Transport_T< Transport_T_2 >::Transport_T( TransportPtr t )
: t_( t )
{
}

template< Transport_T_1 >
bool Transport_T< Transport_T_2 >::write(handler_type& handle,
	   const void* buffer,
	   size_t length,
	   void* act )
{
	std::auto_ptr< Transport_Handler_T< handler_type,T::handler_type > > 
	p( new Transport_Handler_T< handler_type,T::handler_type >( handle , *this ) );
	if( !t_->write( *p, buffer, length, act ) )
		return false;
	p.release();
	return true;
}

template< Transport_T_1 >
bool Transport_T< Transport_T_2 >::write(handler_type& handle,
		  const iovec* data,
		  size_t size,
	   void* act )
{
	std::auto_ptr< Transport_Handler_T< handler_type,T::handler_type > > 
	p( new Transport_Handler_T< handler_type,T::handler_type >( handle, *this ) );
	if( !t_->write( *p, data, size, act ) )
		return false;
	p.release();
	return true;
}

template< Transport_T_1 >
bool Transport_T< Transport_T_2 >::transmit(handler_type& handle,
		  const iopack* data,
		  size_t size,
	   void* act )
{
	std::auto_ptr< Transport_Handler_T< handler_type,T::handler_type > > 
	p( new Transport_Handler_T< handler_type,T::handler_type >( handle, *this ) );
	if( !t_->transmit( *p, data, size, act ) )
		return false;
	p.release();
	return true;
}

template< Transport_T_1 >
bool Transport_T< Transport_T_2 >::read(handler_type& handle,
	  void* buffer,
	  size_t length,
	   void* act )
{
	std::auto_ptr< Transport_Handler_T< handler_type,T::handler_type > > 
	p( new Transport_Handler_T< handler_type,T::handler_type >( handle , *this ) );
	if( !t_->read( *p, buffer, length, act ) )
		return false;
	p.release();
	return true;
}

template< Transport_T_1 >
bool Transport_T< Transport_T_2 >::read(handler_type& handle,
	  WSABUF* data,
	  size_t size,
	   void* act )
{
	std::auto_ptr< Transport_Handler_T< handler_type,T::handler_type > > 
	p( new Transport_Handler_T< handler_type,T::handler_type >( handle , *this ) );
	if( !t_->read( *p, data, size, act ) )
		return false;
	p.release();
	return true;
}

template< Transport_T_1 >
bool Transport_T< Transport_T_2 >::cancel()
{
	return t_->cancel();
}

template< Transport_T_1 >
int Transport_T< Transport_T_2 >::setFeature(const char* feature,
			bool value)
{
	return t_->setFeature( feature, value );
}


template< Transport_T_1 >
int Transport_T< Transport_T_2 >::getFeature(const char* feature,
			bool& value) const
{
	return t_->getFeature( feature, value );
}


template< Transport_T_1 >
int Transport_T< Transport_T_2 >::setOption(const char* option,
		   void* value,
		   size_t size)
{
	return t_->setOption( option, value, size );
}


template< Transport_T_1 >
int Transport_T< Transport_T_2 >::getOption(const char* option,
		   void* value,
		   size_t& size) const
{
	return t_->getOption( option, value, size );
}


template< Transport_T_1 >
typename Transport_T< Transport_T_2 >::LoggerPtr Transport_T< Transport_T_2 >::getLogger()
{
	return t_->getLogger();
}


template< Transport_T_1 >
const tstring& Transport_T< Transport_T_2 >::toString() const
{
	return t_->toString();
}

	
_networks_end

#endif //TRANSPORTT_TEMPL