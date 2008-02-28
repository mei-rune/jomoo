
#ifndef Hazel_ACCEPTOR_H
#define Hazel_ACCEPTOR_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "Hazel_Transport.h"

_networks_begin


class Hazel_Accept_Handler;
class Hazel_Acceptor;
typedef counter_ptr< Hazel_Acceptor > Hazel_Acceptor_Ptr;

class Hazel_Accept_Result : virtual public Hazel_Transport_Result
{
public:

	typedef Hazel_Transport_Ptr transportptr;
	typedef Hazel_Accept_Handler handler_type;
	typedef Hazel_Acceptor acceptor_type;
	typedef Hazel_Transport transport_type;

	/**
	 * virtual destructor
	 */
	virtual ~Hazel_Accept_Result(){}

	/**
	 * ȡ���½�����channel���
	 * @return �½�����channel���
	 */
	virtual Hazel_Transport_Ptr new_channel() = 0;

	/**
	 * �����첽�����Ļص����
	 */
	virtual Hazel_Accept_Handler& handle() = 0;

	/**
	 * �����첽������acceptor���
	 */
	virtual Hazel_Acceptor& acceptor() = 0;

};// END CLASS DEFINITION Hazel_Accept_Result

/**
 * @Brief Hazel_Accept_Handler Acceptor �첽�ص��ӿڣ�@see Hazel_Transport
 */
class Hazel_Accept_Handler
{
public:
	
	typedef Hazel_Accept_Result result_type;

	/**
	 * virtual destructor
	 */
	virtual ~Hazel_Accept_Handler(){}

	/**
	 * channel������ѯ�����ص��ӿ�
	 * @see Hazel_Accept_Result
	 * @see Hazel_Transport::accept
	 */
	virtual void onAccept(Hazel_Accept_Result& result) = 0;

	/**
	 * ȡ��ʵ��������
	 */
	virtual const tstring& toString() const = 0;

};// END CLASS DEFINITION Hazel_Accept_Handler

class Hazel_Acceptor
{
public:

	typedef Hazel_Accept_Handler handler_type;

	/**
	 * virtual destructor
	 */
	virtual ~Hazel_Acceptor(){}

	/**
	 * ����һ��channel��������ѯ�Ƿ����µ�channel���ӵ�����
	 * @param[ in ] handle �첽�ص��ӿ�,��channel������ѯ���������ܳɹ���ʧ
	 *				�ܣ����������óɹ�������ص�handle��onAccept�ӿ�
	 * @param[ in ] act ���β����ĵ�key
	 * @return �ɹ������첽channel������ѯ�����򷵻�true,���򷵻�false
	 * @remark ע��������سɹ��������������µ�channel���ӵ�����Ҳ������һ��
	 *		   ���µ�channel���ӵ�������һ����ص�handle��onAccept�ӿڣ�
	 *		   �������ʧ����һ���������handle��onAccept�ӿڡ�
	 * @see Hazel_Accept_Handler
	 */
	virtual bool accept( Hazel_Accept_Handler& handle
							/*,Hazel_Transport_Ptr new_channel*/ 
							, void* act ) = 0;

	/**
	 * ȡ������һ��channel������ȡ����ѯ�Ƿ����µ�channel���ӵ�����
	 * @return �ɹ�ȡ���첽channel������ѯ�����򷵻�true,���򷵻�false
	 * @see Hazel_Accept_Handler
	 */
	virtual bool cancel() = 0;

	/**
	 * ȡ��ʵ��������
	 */
	virtual const tstring& toString() const = 0;
};

_networks_end

#endif
