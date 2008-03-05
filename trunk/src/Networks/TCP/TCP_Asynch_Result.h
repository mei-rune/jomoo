

#ifndef JOMOO_TCP_ASYNCH_RESULT_H
#define JOMOO_TCP_ASYNCH_RESULT_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

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

	void init( Instance_TCP* instance ,JOMOO_HANDLE handle , void * act );

	void fini( );

	/**
	* ȡ��ʵ�ʷ��͵����ݴ�С
	* @return ʵ�ʷ��͵����ݴ�С
	*/
	size_t bytes_to_transferred() const;

	/**
	* ���β�����key
	*/
	void* act();

	/**
	* ���βٲ������Ƿ�ɹ�
	* @return ����true��ʾ�����ǳɹ��ģ�����ʧ�ܵ�
	*/
	bool success() const;

	/**
	* ȡ�ô���ԭ��
	* @return ����0��ʾû�д��󣬷��򷵻ش����
	*/
	int error() const;

	/**
	 * ȡ���ص�I0�ṹ������
	 */
	JOMOO_OVERLAPPED& getOverlapped(); 

protected:

	DECLARE_NO_COPY_CLASS( TCP_Asynch_Result );

	Instance_TCP* instance_;

	void * m_act_;

	size_t m_bytes_transferred_;

	int m_success_;

	u_long m_error_;
};

_networks_end

#endif // JOMOO_TCP_ASYNCH_RESULT_H