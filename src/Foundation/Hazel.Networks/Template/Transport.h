// Communication


#ifndef __TRANSPORT_T_H__
#define __TRANSPORT_T_H__

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"

_networks_begin

#define RESULT_DECLARE			typedef T result_type;			\
	typedef typename B::handler_type handler_type;				\
	typedef typename B::transport_type transport_type;			\
	void* act();												\
	bool success() const;										\
	int error() const;											\
	size_t bytes_to_transferred() const;						\
	handler_type& handle();										\
	transport_type& transport();								 


#define Read_Result_T_1 typename T , typename B
#define Read_Result_T_2 T , B

template< Read_Result_T_1 >
class Read_Result_T : public B
	//, public Hazel_Read_Result
{
public:
	typedef T result_type;
	typedef typename B::handler_type handler_type;
	typedef typename B::transport_type transport_type;

	Read_Result_T( result_type& result, handler_type& handler,transport_type& transport );

	void* act();

	bool success() const;

	int error() const;

	size_t bytes_to_transferred() const;

	handler_type& handle();

	transport_type& transport();

	void* buffer();

	const void* buffer() const;

	size_t length() const ;

private:

	result_type& result_;
	handler_type& handler_;
	transport_type& transport_;
};

#define Read_Array_Result_T_1 typename T , typename B
#define Read_Array_Result_T_2 T , B

template< Read_Array_Result_T_1 >
class Read_Array_Result_T : public B
	//, public Hazel_Read_Result
{
public:

	RESULT_DECLARE;

	Read_Array_Result_T( result_type& result, handler_type& handler,transport_type& transport );

	iovec* data();

	size_t size() const;

private:

	result_type& result_;
	handler_type& handler_;
	transport_type& transport_;
};

#define Write_Result_T_1 typename T , typename B
#define Write_Result_T_2 T , B

template< Write_Result_T_1 >
class Write_Result_T : public B
	//, public Hazel_Read_Result
{
public:

	RESULT_DECLARE;

	Write_Result_T( result_type& result, handler_type& handler,transport_type& transport );

	const void* buffer() const;

	size_t length() const;

private:

	result_type& result_;
	handler_type& handler_;
	transport_type& transport_;
};

#define Write_Array_Result_T_1 typename T , typename B
#define Write_Array_Result_T_2 T , B

template< Write_Array_Result_T_1 >
class Write_Array_Result_T : public B
	//, public Hazel_Read_Result
{
public:

	RESULT_DECLARE;

	Write_Array_Result_T( result_type& result, handler_type& handler,transport_type& transport );

	const iovec* data();

	size_t size() const;

private:

	result_type& result_;
	handler_type& handler_;
	transport_type& transport_;
};

#define Transmit_Result_T_1 typename T , typename B
#define Transmit_Result_T_2 T , B

template< Transmit_Result_T_1 >
class Transmit_Result_T : public B
	//, public Hazel_Read_Result
{
public:

	RESULT_DECLARE;

	Transmit_Result_T( result_type& result, handler_type& handler,transport_type& transport );

	const iopack* data();

	size_t size() const;

private:

	result_type& result_;
	handler_type& handler_;
	transport_type& transport_;
};


#define Transport_Handler_T_1 typename T , typename B
#define Transport_Handler_T_2 T , B

template< Transport_Handler_T_1 >
class Transport_Handler_T : public B
{

public:

	typedef typename T handler_type;
	typedef typename T::transport_type transport_type;
	typedef typename B::read_result_type read_result_type;
	typedef typename B::read_array_result_type read_array_result_type;
	typedef typename B::write_result_type write_result_type;
	typedef typename B::write_array_result_type write_array_result_type;
	typedef typename B::transmit_result_type transmit_result_type;


	Transport_Handler_T( handler_type& handler,transport_type& transport );

	void onRead(read_result_type& result);

	void onReadArray(read_array_result_type& result );

	void onWrite(write_result_type& result);

	void onWriteArray(write_array_result_type& result);

	void onTransmit(transmit_result_type& result );

	const tstring& toString() const;

private:

	transport_type& transport_;
	handler_type& handler_;

};// END CLASS DEFINITION Transport_Handler_T

#define Transport_T_1 typename T , typename B
#define Transport_T_2 T , B

template< Transport_T_1 >
class Transport_T : public B
{
public:

	typedef typename B::LoggerPtr LoggerPtr;
	typedef typename B::handler_type handler_type;
	typedef typename T::TransportPtr TransportPtr;

	Transport_T( TransportPtr t );

	bool write(handler_type& handle,
		   const void* buffer,
		   size_t length,
		   void* act );

	bool write(handler_type& handle,
			  const iovec* data,
			  size_t size,
		   void* act ) ;

	bool transmit(handler_type& handle,
			  const iopack* data,
			  size_t size,
		   void* act ) ;

	bool read(handler_type& handle,
		  void* buffer,
		  size_t length,
		   void* act ) ;

	bool read(handler_type& handle,
		  WSABUF* data,
		  size_t size,
		   void* act );

	int setFeature(const char* feature,
				bool value) ;

	int getFeature(const char* feature,
				bool& value) const ;

	int setOption(const char* option,
			   void* value,
			   size_t size) ;

	int getOption(const char* option,
			   void* value,
			   size_t& size) const ;

	bool cancel() ;

	LoggerPtr getLogger() ;

	const tstring& toString() const ;

private:

	TransportPtr t_;

};// END CLASS DEFINITION Transport_T

_networks_end

#if defined (Hazel_TEMPLATES_REQUIRE_SOURCE)
#include "Transport.T"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (Hazel_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Transport.T")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#endif // __TRANSPORT_T_H__