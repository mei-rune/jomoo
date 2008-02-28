

#ifndef Hazel_TCP_ASYNCH_TRANSMIT_RESULT_H
#ifndef ___iopack___
#define Hazel_TCP_ASYNCH_TRANSMIT_RESULT_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "TCP_Asynch_Result.H"

_networks_begin


class TCP_Transmit_Result : /*public WIN32OperationOverlapped
	,*/ public TCP_Asynch_Result
{
public:
	typedef TCP_Transport_Handler handler_type;
	TCP_Transmit_Result( );

	void init( Instance_TCP* instance
		, TcpTransport* channel
		, handler_type* handle
		, const iopack* data
		, size_t length
		, void * act );

	void fini();

	/**
	* ȡ�����ݿ�Ļ���
	* @return ���ݻ����ָ��
	*/
	const iopack* data() const;

	/**
	* ȡ�����ݻ���Ĵ�С
	* @return ���ݻ���Ĵ�С
	*/
	size_t size() const;

	/**
	* �����첽�����Ļص����
	*/
	handler_type& handle();

	/**
	* �����첽������channel���
	*/
	TcpTransport& native_transport();

	Hazel_Transport& transport();

	void complete (size_t bytes_transferred,
		int success,
		const void *completion_key,
		u_long error = 0);

private:

	TcpTransport* m_channel_;

	handler_type* m_handle_;

	const iopack* m_data_;

	size_t m_size_;

};

_networks_end

#endif
#endif // Hazel_TCP_ASYNCH_TRANSMIT_RESULT_H