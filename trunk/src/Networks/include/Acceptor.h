
#ifndef JOMOO_ACCEPTOR_H
#define JOMOO_ACCEPTOR_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "JOMOO_Transport.h"

_networks_begin


class JOMOO_Accept_Handler;
class JOMOO_Acceptor;
typedef counter_ptr< JOMOO_Acceptor > JOMOO_Acceptor_Ptr;

class JOMOO_Accept_Result : virtual public JOMOO_Transport_Result
{
public:

	typedef JOMOO_Transport_Ptr transportptr;
	typedef JOMOO_Accept_Handler handler_type;
	typedef JOMOO_Acceptor acceptor_type;
	typedef JOMOO_Transport transport_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Accept_Result(){}

	/**
	 * ȡ���½�����channel���
	 * @return �½�����channel���
	 */
	virtual JOMOO_Transport_Ptr new_channel() = 0;

	/**
	 * �����첽�����Ļص����
	 */
	virtual JOMOO_Accept_Handler& handle() = 0;

	/**
	 * �����첽������acceptor���
	 */
	virtual JOMOO_Acceptor& acceptor() = 0;

};// END CLASS DEFINITION JOMOO_Accept_Result

/**
 * @Brief JOMOO_Accept_Handler Acceptor �첽�ص��ӿڣ�@see JOMOO_Transport
 */
class JOMOO_Accept_Handler
{
public:
	
	typedef JOMOO_Accept_Result result_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Accept_Handler(){}

	/**
	 * channel������ѯ�����ص��ӿ�
	 * @see JOMOO_Accept_Result
	 * @see JOMOO_Transport::accept
	 */
	virtual void onAccept(JOMOO_Accept_Result& result) = 0;

	/**
	 * ȡ��ʵ��������
	 */
	virtual const tstring& toString() const = 0;

};// END CLASS DEFINITION JOMOO_Accept_Handler

class JOMOO_Acceptor
{
public:

	typedef JOMOO_Accept_Handler handler_type;

	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Acceptor(){}

	/**
	 * ����һ��channel��������ѯ�Ƿ����µ�channel���ӵ�����
	 * @param[ in ] handle �첽�ص��ӿ�,��channel������ѯ���������ܳɹ���ʧ
	 *				�ܣ����������óɹ�������ص�handle��onAccept�ӿ�
	 * @param[ in ] act ���β����ĵ�key
	 * @return �ɹ������첽channel������ѯ�����򷵻�true,���򷵻�false
	 * @remark ע��������سɹ��������������µ�channel���ӵ�����Ҳ������һ��
	 *		   ���µ�channel���ӵ�������һ����ص�handle��onAccept�ӿڣ�
	 *		   �������ʧ����һ���������handle��onAccept�ӿڡ�
	 * @see JOMOO_Accept_Handler
	 */
	virtual bool accept( JOMOO_Accept_Handler& handle
							/*,JOMOO_Transport_Ptr new_channel*/ 
							, void* act ) = 0;

	/**
	 * ȡ������һ��channel������ȡ����ѯ�Ƿ����µ�channel���ӵ�����
	 * @return �ɹ�ȡ���첽channel������ѯ�����򷵻�true,���򷵻�false
	 * @see JOMOO_Accept_Handler
	 */
	virtual bool cancel() = 0;

	/**
	 * ȡ��ʵ��������
	 */
	virtual const tstring& toString() const = 0;
};

_networks_end

#endif
