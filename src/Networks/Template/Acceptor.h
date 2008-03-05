// Communication


#ifndef __ACCEPTOR_T__
#define __ACCEPTOR_T__

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"

_networks_begin

#define Accept_Result_T_1 typename T, typename B
#define Accept_Result_T_2 T, B

template< typename T, typename B >
class Accept_Result_T : public B
{
public:

	typedef typename T result_type;
	typedef typename B::transportptr transportptr;
	typedef typename B::handler_type handler_type;
	typedef typename B::acceptor_type acceptor_type;
	typedef typename B::transport_type transport_type;

	Accept_Result_T( result_type& ptr ,	handler_type& handle,acceptor_type& acceptor );

	/**
	* 取得实际读到的数据块大小
	* @return 实际读到的数据块大小
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
	 * 取得新建立的channel句柄
	 * @return 新建立的channel句柄
	 */
	transportptr new_channel();

	/**
	 * 本次异步操作的回调句柄
	 */
	handler_type& handle();

	/**
	 * 本次异步操作的acceptor句柄
	 */
	acceptor_type& acceptor();

private:

	DECLARE_NO_COPY_CLASS( Accept_Result_T );

	result_type& result_;

	handler_type& handle_;
	acceptor_type& acceptor_;
};

#define Accept_Handler_T_1 typename T, typename B
#define Accept_Handler_T_2 T, B

template< Accept_Handler_T_1 >
class Accept_Handler_T : public B
{
public:

	typedef typename B::result_type result_type;
	typedef typename T::result_type::acceptor_type acceptor_type;
	typedef T handler_type;


	Accept_Handler_T( handler_type& handler ,acceptor_type& acceptor );

	void onAccept(result_type& result);

	const tstring& toString() const;

private:

	handler_type& handler_;

	acceptor_type& acceptor_;

};// END CLASS DEFINITION Accept_Handler_T


#define Acceptor_T_1 typename T, typename B
#define Acceptor_T_2 T, B

template< Acceptor_T_1 >
class Acceptor_T  : public B
	// : public JOMOO_Acceptor
{
public:	

	typedef typename B::handler_type handler_type;

	/**
	 * JOMOO_TCP_Acceptor constructor
	 */
	Acceptor_T( T* ptr );

	bool accept( handler_type& handle
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

#if defined (JOMOO_TEMPLATES_REQUIRE_SOURCE)
#include "Acceptor.T"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (JOMOO_TEMPLATES_REQUIRE_PRAGMA)
#pragma implementation ("Acceptor.T")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#endif // __ACCEPTOR_T__
