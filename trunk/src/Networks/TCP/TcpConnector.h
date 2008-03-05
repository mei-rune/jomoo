// Communication


#ifndef __JOMOO_TCP_CHANNEL_CONNECTOR__
#define __JOMOO_TCP_CHANNEL_CONNECTOR__

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "../WIN32OperationOverlapped.H"
#include "../JOMOO_socket.h"
#include "../JOMOO_INET_Addr.H"
#include "TcpTransport.H"
#include "../include/JOMOO_Connector.H"

_networks_begin

class TcpConnector;

class TCP_Connect_Result : public TCP_Asynch_Result
	//, public JOMOO_Connect_Result
{
public:

	typedef TcpTransport transport_type;
	typedef TCP_Connect_Handler handler_type;

	TCP_Connect_Result( );

	/**
	* virtual destructor
	*/
	virtual ~TCP_Connect_Result();

	void init( Instance_TCP* instance
		, TcpConnector* channel
		, handler_type* handle
		, TcpTransportPtr newchannel
		, void * act );

	void fini( );

	/**
	 * ȡ���½�����channel���
	 * @return �½�����channel���
	 */
	TcpTransportPtr new_native_channel();

	/**
	 * �����첽������connector���
	 */
	TcpConnector& native_connector();

	/**
	 * �����첽�����Ļص����
	 */
	handler_type& handle();

	JOMOO_Transport_Ptr new_channel();

	/**
	 * �����첽������connector���
	 */
	JOMOO_Connector& connector();

	void complete (size_t bytes_transferred,
		int success,
		const void *completion_key,
		u_long error = 0);

private:

	DECLARE_NO_COPY_CLASS( TCP_Connect_Result );

	TcpConnector* m_channel_;

	handler_type* m_handle_;

	TcpTransportPtr m_Transport_;
};

class TcpConnector
	 : public JOMOO_Connector
{
public:

	typedef TCP_Connect_Handler handler_type;
	typedef TcpTransport::LoggerPtr LoggerPtr;

	/**
	 * TcpConnector constructor
	 */
	TcpConnector( Instance_TCP& instance , const tchar* name = 0 );

	~TcpConnector();

	bool connect(handler_type& handle
		, void* act );

	/**
	 * ȡ������һ��channel
	 * @return �ɹ�ȡ���򷵻�true,���򷵻�false
	 * @see handler_type
	 */
	bool cancel();

	/**
	 * ��������
	 * @param[ in ] addr ���ӵĵ�ַ
	 * @return �ɹ��򷵻�true,���򷵻�false
	 */
	bool open( const JOMOO_INET_Addr& addr );
	
	/**
	 * �رս�������ֹͣ����
	 */
	void close( );

	bool isOpen( );

	LoggerPtr getLogger();

	/**
	 * ȡ��ʵ��������
	 */
    virtual const std::string& toString() const;

	/**
	 * ȡ�ñ��ص�ַ
	 * @return ���ص�ַ
	 */
	const JOMOO_INET_Addr& getRemoteAddr() const;

private:

	DECLARE_NO_COPY_CLASS( TcpConnector );

	TcpTransportPtr createTransport();

	Instance_TCP& instance_;

	JOMOO_INET_Addr m_remoteaddr_;

	tstring toString_;
};

_networks_end

#endif // __JOMOO_TCP_CHANNEL_CONNECTOR__