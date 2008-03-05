// Communication


#ifndef __JOMOO_TCP_CHANNEL_ACCEPTOR__
#define __JOMOO_TCP_CHANNEL_ACCEPTOR__

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "../JOMOO_socket.h"
#include "../JOMOO_INET_Addr.H"
#include "TCPAsynchResult.H"
#include "TcpTransport.H"
#include "../include/JOMOO_Acceptor.H"

_networks_begin

class TcpAcceptor;

class TCP_Accept_Result : public TCP_Asynch_Result
	//, public JOMOO_Accept_Result
{
public:

	typedef TcpTransport transport_type;
	typedef TCP_Accept_Handler handler_type;

	TCP_Accept_Result( );

	virtual ~TCP_Accept_Result();

	void init( Instance_TCP* instance
		, TcpAcceptor* channel
		, handler_type* handle
		, TcpTransportPtr newchannel
		, int recv_size
		, void * act );

	void fini( );

	TcpAcceptor& native_acceptor();

	TcpTransportPtr new_native_channel();

	handler_type& handle();

	JOMOO_Transport_Ptr new_channel();

	JOMOO_Acceptor& acceptor();

	void complete (size_t bytes_transferred,
		int success,
		const void *completion_key,
		u_long error = 0);

	char* getBuffer( );

	size_t getBufferLen() const;

private:

	DECLARE_NO_COPY_CLASS( TCP_Accept_Result );

	TcpAcceptor* m_acceptor_;

	handler_type* m_handle_;

	TcpTransportPtr m_new_channel_;

	char* m_buf_;

	size_t m_buf_len_;

	size_t m_bytes_transferred_;
};

class TcpAcceptor 
	 : public JOMOO_Acceptor
{
public:	

	typedef TcpTransport::LoggerPtr LoggerPtr;
	typedef TCP_Accept_Handler handler_type;

	/**
	 * JOMOO_TCP_Acceptor constructor
	 */
	TcpAcceptor( Instance_TCP& instance , const tchar* name = 0 );

	~TcpAcceptor(void);	

	bool accept( handler_type& handle
						/*	,JOMOO_Transport_Ptr new_channel*/
						, void* act );

	bool cancel();

	const tstring& toString() const ;

	bool open( const JOMOO_INET_Addr& addr );

	bool isOpen( );

	void close( );

	JOMOO_socket& get_handle();

	LoggerPtr getLogger();

private:
	
	DECLARE_NO_COPY_CLASS( TcpAcceptor );

	TcpTransportPtr createTransport();

	Instance_TCP& instance_;

	WIN32OperationOverlapped accept_Overlapped_;

	JOMOO_socket m_handle_;

	JOMOO_INET_Addr m_serveraddr_;

	tstring toString_;
};

_networks_end

#endif // __JOMOO_TCP_CHANNEL_ACCEPTOR__
