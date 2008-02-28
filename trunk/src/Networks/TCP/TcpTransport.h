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
	 * ��ͨ����.
	 * @return �ɹ��򷵻�true,���򷵻�false
	 */
	bool open( );

	void close( );

	/**
	 * ����һ�����ݣ�ע�������첽��  )
	 * @param[ in ] handle �첽�ص��ӿ�,�����ݷ��Ͳ��������ܳɹ���ʧ�ܣ�������
	 *				���óɹ�������ص�handle��handle_writed�ӿ�
	 * @param[ in ] buffer �����͵����ݿ�ָ��
	 * @param[ in ] length �����͵����ݿ��С
	 * @param[ in ] act ���β����ĵ�key
	 * @return �ɹ������첽�����򷵻�true,���򷵻�false
	 * @remark ע��������سɹ��������������ݱ����ͣ�Ҳ����������һ���ᷢ�ͳ�
	 *		   ������һ����ص�handle��handle_writed�ӿڣ��������ʧ����һ����
	 *		   �����handle��handle_writed�ӿ�
	 * @see Hazel_Transport_Handler
	 */
	bool write(handler_type& handle,
				   const void* buffer,
				   size_t length,
				   void* act ) ;
	/**
	 * ����һ�������ݣ�ע�������첽��  )
	 * @param[ in ] handle �첽�ص��ӿ�,�����ݷ��Ͳ��������ܳɹ���ʧ�ܣ�������
	 *				���óɹ�������ص�handle��onTransmit�ӿ�
	 * @param[ in ] data �����͵����ݿ�ָ��
	 * @param[ in ] size �����͵����ݿ����
	 * @param[ in ] act ���β����ĵ�key
	 * @return �ɹ������첽�����򷵻�true,���򷵻�false
	 * @remark ע��������سɹ��������������ݱ����ͣ�Ҳ����������һ���ᷢ�ͳ�
	 *		   ������һ����ص�handle��onTransmit�ӿڣ��������ʧ����һ��
	 *		   �������handle��onTransmit�ӿ�
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