// Communication


#ifndef __CONNECTOR_T__
#define __CONNECTOR_T__

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"

_networks_begin

#define Connect_Result_T_1 typename T, typename B
#define Connect_Result_T_2 T, B

template< Connect_Result_T_1 >
class Connect_Result_T : public B  //: public WIN32OperationOverlapped
	//, public Hazel_Connect_Result
{
public:
	typedef typename T result_type;
	typedef typename B::transportptr transportptr;
	typedef typename B::transport_type transport_type;
	typedef typename B::handler_type handler_type;
	typedef typename B::connector_type connector_type;

	Connect_Result_T( result_type& result,handler_type& handler,connector_type& connector );

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
	 * 取得新建立的channel句柄
	 * @return 新建立的channel句柄
	 */
	transportptr new_channel();

//	TcpTransport* new_TcpTransport();

	/**
	 * 本次异步操作的回调句柄
	 */
	handler_type& handle();

	/**
	 * 本次异步操作的connector句柄
	 */
	connector_type& connector();

private:

	result_type& result_;

	handler_type& handler_;
	connector_type& connector_;
};

#define Connect_Handler_T_1 typename T, typename B
#define Connect_Handler_T_2 T, B

template< Connect_Handler_T_1 >
class Connect_Handler_T : public B
{
public:

	typedef typename B::result_type result_type;
	typedef typename T::result_type::connector_type connector_type;
	typedef T handler_type;

	Connect_Handler_T( handler_type& handler ,connector_type& connector );

	void onConnect(result_type& result);

	const tstring& toString() const;

private:

	handler_type& handler_;
	connector_type& connector_;

};// END CLASS DEFINITION Connect_Handler_T


#define Connector_T_1 typename T, typename B
#define Connector_T_2 T, B

template< Connector_T_1 >
class Connector_T  : public B
	// : public Hazel_Acceptor
{
public:	

	typedef typename B::handler_type handler_type;

	/**
	 * Hazel_TCP_Acceptor constructor
	 */
	Connector_T( T* ptr );

	bool connect( handler_type& handle
						, void* act );

	bool cancel();

	const tstring& toString() const ;

	template< typename S >
	bool open( S s )
	{
		return ptr_->open( s );
	}

	bool isOpen()
	{
		return ptr_->isOpen( );
	}

private:
	
	std::auto_ptr< T > ptr_;
};

_networks_end

#if defined (Hazel_TEMPLATES_REQUIRE_SOURCE)
#include "Connector.T"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (Hazel_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Connector.T")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#endif // __ACCEPTOR_T__