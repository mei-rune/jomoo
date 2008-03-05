

#ifndef JOMOO_TCP_ASYNCH_READ_ARRAY_RESULT_H
#define JOMOO_TCP_ASYNCH_READ_ARRAY_RESULT_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "TCP_Asynch_Result.H"


_networks_begin

class TCP_Read_Array_Result :  public TCP_Asynch_Result
{
public:
	typedef JOMOO_Transport_Handler handler_type;
	TCP_Read_Array_Result( );

	void init( Instance_TCP* instance
		, TcpTransport* channel
		, handler_type* handle
		, iovec* data
		, size_t length
		, void * act );

	void fini();

	/**
	* 取得数据缓冲数据组
	* @return 成功返回数据缓冲数据组的指针，失败返回0
	*/
	iovec* data();

	/**
	* 取得数据缓冲数据组大小
	* @return 数据缓冲数据组大小
	*/
	size_t size() const;

	/**
	* 本次异步操作的回调句柄
	*/
	handler_type& handle();

	/**
	* 本次异步操作的channel句柄
	*/
	TcpTransport& native_transport();

	JOMOO_Transport& transport();

	void complete (size_t bytes_transferred,
		int success,
		const void *completion_key,
		u_long error = 0);

private:

	DECLARE_NO_COPY_CLASS( TCP_Read_Array_Result );

	TcpTransport* m_channel_;

	handler_type* m_handle_;

	WSABUF* m_data_;

	size_t m_size_;
};

_networks_end

#endif // JOMOO_TCP_ASYNCH_READ_ARRAY_RESULT_H