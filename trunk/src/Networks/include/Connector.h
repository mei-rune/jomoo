
#ifndef JOMOO_CONNECTOR_H
#define JOMOO_CONNECTOR_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */


// Include files
#include "../config_Networks.h"
#include "JOMOO_Transport.h"

_networks_begin

class JOMOO_Connect_Handler;
class JOMOO_Connector;

typedef counter_ptr< JOMOO_Connector > JOMOO_Connector_Ptr;

class JOMOO_Connect_Result : public JOMOO_Transport_Result
{

public:

	typedef JOMOO_Transport transport_type;
	typedef JOMOO_Transport_Ptr transportptr;
	typedef JOMOO_Connect_Handler handler_type;
	typedef JOMOO_Connector connector_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Connect_Result(){}

	/**
	 * ȡ���½�����channel���
	 * @return �½�����channel���
	 */
	virtual JOMOO_Transport_Ptr new_channel() = 0;

	/**
	 * �����첽�����Ļص����
	 */
	virtual JOMOO_Connect_Handler& handle() = 0;

	/**
	 * �����첽������connector���
	 */
	virtual JOMOO_Connector& connector() = 0;

};// END CLASS DEFINITION JOMOO_Connect_Result

/**
 * @Brief JOMOO_Connect_Handler Connector �첽�ص��ӿڣ�@see JOMOO_Transport
 */
class JOMOO_Connect_Handler
{
public:
	
	typedef JOMOO_Connect_Result result_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Connect_Handler(){}

	/**
	 * channel�������Ӳ����ص��ӿ�
	 * @see JOMOO_Connect_Result
	 * @see JOMOO_Transport::connect
	 */
	virtual void onConnect(JOMOO_Connect_Result& result) = 0;

	/**
	 * ȡ��ʵ��������
	 */
	virtual const tstring& toString() const = 0;

};// END CLASS DEFINITION JOMOO_Connect_Handler


class JOMOO_Connector
{
public:
    	
	typedef JOMOO_Connect_Handler handler_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Connector(){}

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
	 * @see JOMOO_Connect_Handler
	 */
	virtual bool connect(JOMOO_Connect_Handler& handle
						, void* act ) = 0;
	/**
	 * ȡ������һ��channel
	 * @return �ɹ�ȡ���򷵻�true,���򷵻�false
	 * @see JOMOO_Connect_Handler
	 */
	virtual bool cancel() = 0;

	/**
	 * ȡ��ʵ��������
	 */
    virtual const std::string& toString() const = 0;
};

_networks_end

#endif
