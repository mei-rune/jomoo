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
	 * 取得新建立的channel句柄
	 * @return 新建立的channel句柄
	 */
	TcpTransportPtr new_native_channel();

	/**
	 * 本次异步操作的connector句柄
	 */
	TcpConnector& native_connector();

	/**
	 * 本次异步操作的回调句柄
	 */
	handler_type& handle();

	JOMOO_Transport_Ptr new_channel();

	/**
	 * 本次异步操作的connector句柄
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
	 * 取消建立一个channel
	 * @return 成功取消则返回true,否则返回false
	 * @see handler_type
	 */
	bool cancel();

	/**
	 * 打开连接器
	 * @param[ in ] addr 连接的地址
	 * @return 成功则返回true,否则返回false
	 */
	bool open( const JOMOO_INET_Addr& addr );
	
	/**
	 * 关闭接收器，停止监听
	 */
	void close( );

	bool isOpen( );

	LoggerPtr getLogger();

	/**
	 * 取得实例的描述
	 */
    virtual const std::string& toString() const;

	/**
	 * 取得本地地址
	 * @return 本地地址
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