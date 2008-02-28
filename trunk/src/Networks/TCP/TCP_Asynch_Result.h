

#ifndef Hazel_TCP_ASYNCH_RESULT_H
#define Hazel_TCP_ASYNCH_RESULT_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "../WIN32OperationOverlapped.H"
//#include "Instance_TCP.H"
#include "../include/Transport.H"
#include <vector>


_networks_begin

class Instance_TCP;
class TcpTransport;

class TCP_Asynch_Result : public WIN32_Operation_Result
{
public:

	TCP_Asynch_Result( );

	virtual ~TCP_Asynch_Result();

	void init( Instance_TCP* instance ,Hazel_HANDLE handle , void * act );

	void fini( );

	/**
	* 取得实际发送的数据大小
	* @return 实际发送的数据大小
	*/
	size_t bytes_to_transferred() const;

	/**
	* 本次操作的key
	*/
	void* act();

	/**
	* 本次操步操作是否成功
	* @return 返回true表示本次是成功的，否则不失败的
	*/
	bool success() const;

	/**
	* 取得错误原因
	* @return 返回0表示没有错误，否则返回错误号
	*/
	int error() const;

	/**
	 * 取得重叠I0结构的引用
	 */
	Hazel_OVERLAPPED& getOverlapped(); 

protected:

	DECLARE_NO_COPY_CLASS( TCP_Asynch_Result );

	Instance_TCP* instance_;

	void * m_act_;

	size_t m_bytes_transferred_;

	int m_success_;

	u_long m_error_;
};

_networks_end

#endif // Hazel_TCP_ASYNCH_RESULT_H