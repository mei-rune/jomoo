

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
#include "../include/Hazel_Transport.H"
#include <vector>


_networks_begin

class Instance_TCP;
class TcpTransport;
typedef Hazel_Transport_Handler TCP_Transport_Handler;

class TCP_Asynch_Result : public Hazel_Operation_Result
	, public WIN32OperationOverlapped
//	, virtual public Hazel_Transport_Result
{
public:

	TCP_Asynch_Result( );

	virtual ~TCP_Asynch_Result();

	void init( Instance_TCP* instance ,Hazel_HANDLE handle , void * act );
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

	WIN32OperationOverlapped& getOverlapped(); 

protected:

	DECLARE_NO_COPY_CLASS( TCP_Asynch_Result );

	Instance_TCP* instance_;

	void * m_act_;

	size_t m_bytes_transferred_;

	int m_success_;

	u_long m_error_;
};


/**
 * @Brief TCP_Transport_Handler channel �첽�ص��ӿڣ�@see TcpTransport
 */
//class TCP_Transport_Handler
//{
//public:
//
//	typedef TCP_Read_Result read_result_type;
//	typedef TCP_Read_Array_Result read_array_result_type;
//	typedef TCP_Write_Result write_result_type;
//	typedef TCP_Write_Array_Result write_array_result_type;
//	typedef TCP_Transmit_Result transmit_result_type;
//
//	/**
//	 * virtual destructor
//	 */
//	virtual ~TCP_Transport_Handler(){}
//
//	/**
//	 * channel�������ص��ӿ�
//	 * @see TCP_Read_Result
//	 * @see TcpTransport::read
//	 */
//	virtual void onRead(TCP_Read_Result& result) = 0;
//
//	/**
//	 * channel�������ص��ӿ�
//	 * @see TCP_Read_Array_Result
//	 * @see TcpTransport::read
//	 */
//	virtual void onReadArray(TCP_Read_Array_Result& result ) = 0;
//
//	/**
//	 * channelд�����ص��ӿ�
//	 * @see TCP_Write_Result
//	 * @see TcpTransport::write
//	 */
//	virtual void onWrite(TCP_Write_Result& result) = 0;
//
//	/**
//	 * channelд�����ص��ӿ�
//	 * @see TCP_Write_Result
//	 * @see TcpTransport::write
//	 */
//	virtual void onWriteArray(TCP_Write_Array_Result& result) = 0;
//
//	/**
//	 * channelд�����ص��ӿ�
//	 * @see TCP_Transmit_Result
//	 * @see TcpTransport::transmit
//	 */
//	virtual void onTransmit(TCP_Transmit_Result& result ) = 0;
//
//	/**
//	 * ȡ��ʵ��������
//	 */
//	virtual const tstring& toString() const = 0;
//
//};// END CLASS DEFINITION Hazel_Transport_Handler

_networks_end

#endif // Hazel_TCP_ASYNCH_RESULT_H