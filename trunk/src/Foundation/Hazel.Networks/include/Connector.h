
#ifndef Hazel_CONNECTOR_H
#define Hazel_CONNECTOR_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */


// Include files
#include "../config_Networks.h"
#include "Hazel_Transport.h"

_networks_begin

class Hazel_Connect_Handler;
class Hazel_Connector;

typedef counter_ptr< Hazel_Connector > Hazel_Connector_Ptr;

class Hazel_Connect_Result : public Hazel_Transport_Result
{

public:

	typedef Hazel_Transport transport_type;
	typedef Hazel_Transport_Ptr transportptr;
	typedef Hazel_Connect_Handler handler_type;
	typedef Hazel_Connector connector_type;

	/**
	 * virtual destructor
	 */
	virtual ~Hazel_Connect_Result(){}

	/**
	 * ȡ���½�����channel���
	 * @return �½�����channel���
	 */
	virtual Hazel_Transport_Ptr new_channel() = 0;

	/**
	 * �����첽�����Ļص����
	 */
	virtual Hazel_Connect_Handler& handle() = 0;

	/**
	 * �����첽������connector���
	 */
	virtual Hazel_Connector& connector() = 0;

};// END CLASS DEFINITION Hazel_Connect_Result

/**
 * @Brief Hazel_Connect_Handler Connector �첽�ص��ӿڣ�@see Hazel_Transport
 */
class Hazel_Connect_Handler
{
public:
	
	typedef Hazel_Connect_Result result_type;

	/**
	 * virtual destructor
	 */
	virtual ~Hazel_Connect_Handler(){}

	/**
	 * channel�������Ӳ����ص��ӿ�
	 * @see Hazel_Connect_Result
	 * @see Hazel_Transport::connect
	 */
	virtual void onConnect(Hazel_Connect_Result& result) = 0;

	/**
	 * ȡ��ʵ��������
	 */
	virtual const tstring& toString() const = 0;

};// END CLASS DEFINITION Hazel_Connect_Handler


class Hazel_Connector
{
public:
    	
	typedef Hazel_Connect_Handler handler_type;

	/**
	 * virtual destructor
	 */
	virtual ~Hazel_Connector(){}

	/**
	 * ����һ��channel
	 * @param[ in ] handle �첽�ص��ӿ�,������channel���Ӳ��������ܳɹ���ʧ
	 *				�ܣ����������óɹ�������ص�handle��onConnect�ӿ�
	 * @param[ in ] addr Զ�̵�ַ
	 * @param[ in ] act ���β����ĵ�key
	 * @return �ɹ����ý���channel���Ӳ����򷵻�true,���򷵻�false
	 * @remark ע��������سɹ�������������channel���ӳɹ���Ҳ������channel
	 *		   ����һ���Ὠ���ɹ�����һ����ص�handle��onConnect�ӿڣ�
	 *		   �������ʧ����һ���������handle��onConnect�ӿڡ�
	 * @see Hazel_Connect_Handler
	 */
	virtual bool connect(Hazel_Connect_Handler& handle
						, void* act ) = 0;
	/**
	 * ȡ������һ��channel
	 * @return �ɹ�ȡ���򷵻�true,���򷵻�false
	 * @see Hazel_Connect_Handler
	 */
	virtual bool cancel() = 0;

	/**
	 * ȡ��ʵ��������
	 */
    virtual const std::string& toString() const = 0;
};

_networks_end

#endif
