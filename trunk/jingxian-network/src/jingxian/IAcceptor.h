
#ifndef _IAcceptor_H_
#define _IAcceptor_H_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "buffer.h"
# include "Dictionary.h"

_jingxian_begin

class IEndpoint;
class IProtocolFactory;

class IAcceptor
{
public:
	virtual ~IAcceptor(){}

	/**
	 * ȡ�ó�ʱʱ��
	 */
    virtual  time_t timeout () const = 0;

	/**
	 * �����ĵ�ַ
	 */
    virtual const IEndpoint& bindPoint() const = 0;

	/**
	 * ֹͣ����
	 */
    virtual void stopListening() = 0;

	/**
	 * ��������
	 * 
	 * @return ���������ɹ�����true, ʧ�ܷ���false
	 */
    virtual bool startListening() = 0;

	/**
	 * ȡ��Э�鹤��
	 */
    virtual IProtocolFactory& protocolFactory() = 0;

	/**
	 * ȡ�������ֵ�
	 */
    virtual IDictionary& misc() = 0;

	/**
	 * ȡ�������ֵ�
	 */
	virtual const IDictionary& misc() const = 0;

	/**
	* ȡ�õ�ַ������
	*/
	virtual const tstring& toString() const = 0;
};


class IAcceptorFactory
{
public:

	virtual ~IAcceptorFactory(){}

	/**
	 * ���� IAcceptor ����
	 */
	virtual IAcceptor* createAcceptor(const tchar* endPoint) = 0;

	/**
	 * ȡ�õ�ַ������
	 */
	virtual const tstring& toString() const = 0;
};

inline tostream& operator<<( tostream& target, const IAcceptor& acceptor )
{
	target << acceptor.toString();
	return target;
}

inline tostream& operator<<( tostream& target, const IAcceptorFactory& acceptorFactory )
{
	target << acceptorFactory.toString();
	return target;
}

_jingxian_end

#endif //_IAcceptor_H_ 