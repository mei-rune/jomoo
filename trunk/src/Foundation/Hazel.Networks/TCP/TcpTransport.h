// Communication


#ifndef __TcpTransport__
#define __TcpTransport__

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "../hazel_socket.h"
#include "../Hazel_INET_Addr.H"
#include "Hazel.Base/Counter_Ptr.hpp"
#include "Tcp_Asynch_Read_Result.H"
#include "Tcp_Asynch_Read_Array_Result.H"
#include "Tcp_Asynch_Write_Result.H"
#include "Tcp_Asynch_Write_Array_Result.H"
#include "Tcp_Asynch_Transmit_Result.H"

_networks_begin

class TcpTransport 
	: 	public Hazel_Transport
{
public:

	typedef Hazel_Transport::LoggerPtr LoggerPtr;
	typedef TCP_Transport_Handler handler_type;
	typedef counter_ptr< TcpTransport > TransportPtr;
	typedef TransportPtr ptr_type;

	/**
	 * TcpTransport constructor
	 */
	TcpTransport(  );
	
	/**
	 * TcpTransport destructor
	 */
	~TcpTransport(void);

	void init( Instance_TCP* instance , const tchar* name );
	void fini();

	/**
	 * 打开通信器.
	 * @return 成功则返回true,否则返回false
	 */
	bool open( );

	void close( );

	/**
	 * 发送一块数据（注意它是异步的  )
	 * @param[ in ] handle 异步回调接口,当数据发送操作（不管成功，失败，撤消）
	 *				调用成功，都会回调handle的handle_writed接口
	 * @param[ in ] buffer 待发送的数据块指针
	 * @param[ in ] length 待发送的数据块大小
	 * @param[ in ] act 本次操作的的key
	 * @return 成功调用异步发送则返回true,否则返回false
	 * @remark 注意如果返回成功，并不代表数据被发送，也不代表数据一定会发送成
	 *		   功，但一定会回调handle的handle_writed接口，如果返回失败则一定不
	 *		   会调用handle的handle_writed接口
	 * @see Hazel_Transport_Handler
	 */
	bool write(handler_type& handle,
				   const void* buffer,
				   size_t length,
				   void* act ) ;
	/**
	 * 发送一块多块数据（注意它是异步的  )
	 * @param[ in ] handle 异步回调接口,当数据发送操作（不管成功，失败，撤消）
	 *				调用成功，都会回调handle的onTransmit接口
	 * @param[ in ] data 待发送的数据块指针
	 * @param[ in ] size 待发送的数据块个数
	 * @param[ in ] act 本次操作的的key
	 * @return 成功调用异步发送则返回true,否则返回false
	 * @remark 注意如果返回成功，并不代表数据被发送，也不代表数据一定会发送成
	 *		   功，但一定会回调handle的onTransmit接口，如果返回失败则一定
	 *		   不会调用handle的onTransmit接口
	 * @see Hazel_Transport_Handler
	 */
	bool write(handler_type& handle,
					  const iovec* data,
					  size_t size,
					  void* act );

	bool transmit(handler_type& handle,
					  const iopack* data,
					  size_t size,
					  void* act );

	bool transmit(handler_type& handle,
					  iopack* data,
					  size_t size,
					  void* act );

	bool read(handler_type& handle,
				  void* buffer,
				  size_t length,
				  void* act );

	bool read(handler_type& handle,
				  WSABUF* data,
				  size_t size,
				  void* act );

	virtual int setFeature(const char* feature,
						bool value);

	virtual int getFeature(const char* feature,
						bool& value) const;

	virtual int setOption(const char* option,
					   void* value,
					   size_t size);

	virtual int getOption(const char* option,
					   void* value,
					   size_t& size) const;

	bool cancel();

	const Hazel_INET_Addr& getRemoteAddr() const;

	const Hazel_INET_Addr& getLocalAddr() const;

	Hazel_INET_Addr& getRemoteAddr();

	Hazel_INET_Addr& getLocalAddr();

	LoggerPtr getLogger();

	const tstring& toString() const;

	hazel_socket& get_handle();

	void onAccept();

	void onConnect();

private:

	DECLARE_NO_COPY_CLASS( TcpTransport );

	Instance_TCP* instance_;

	hazel_socket m_handle_;

	tstring m_to_string_;

	Hazel_INET_Addr m_remoteaddr_;
	Hazel_INET_Addr m_localaddr_;

};// END CLASS DEFINITION TcpTransport


typedef TcpTransport::ptr_type TcpTransportPtr;

typedef TcpTransport::TransportPtr TcpTransportPtr;

_networks_end

#endif // __TcpTransport__