

#ifndef JOMOO_TCP_ASYNCH_READ_RESULT_H
#define JOMOO_TCP_ASYNCH_READ_RESULT_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "TCP_Asynch_Result.H"

_networks_begin

class TCP_Read_Result : public TCP_Asynch_Result
{
public:
	typedef TCP_Transport_Handler handler_type;
	TCP_Read_Result(  );

	void init( Instance_TCP* instance
		, TcpTransport* channel
		, handler_type* handle
		, void* buffer
		, size_t length
		, void * act );

	void fini( );

	/**
	* ȡ�����ݿ�Ļ���
	* @return ���ݻ����ָ��
	*/
	void* buffer();

	/**
	 * ȡ�����ݿ�Ļ���
	 * @return ���ݻ����ָ��
	 */
	const void* buffer() const;

	/**
	* ȡ�����ݻ���Ĵ�С
	* @return ���ݻ���Ĵ�С
	*/
	size_t length() const;

	/**
	* �����첽�����Ļص����
	*/
	handler_type& handle();

	/**
	* �����첽������channel���
	*/
	TcpTransport& native_transport();

	JOMOO_Transport& transport();

	void complete (size_t bytes_transferred,
		int success,
		const void *completion_key,
		u_long error = 0);

private:

	DECLARE_NO_COPY_CLASS( TCP_Read_Result );

	TcpTransport* m_channel_;

	handler_type* m_handle_;

	void* m_buffer_;

	size_t m_length_;
};



_networks_end

#endif // JOMOO_TCP_ASYNCH_READ_RESULT_H