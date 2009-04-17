
#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "jingxian/string/string.hpp"
# include "Exception.hpp"

_jingxian_begin

class IEndpoint;

typedef IProtocol* (*BuildProtocol)( ITransport* transport, void* context);
typedef void (*OnConnectError)( const Exception& exception, void* context);

class IConnector
{
public:

	virtual ~IConnector() {};
    /**
     * ����һ������
     * 
     * @param[ in ] buildProtocol �����ӳɹ�ʱ�����ñ�ί�д���һ��������
     * @param[ in ] throwError  �����ӷ���������ʼ����������������ʱ��
	 * �ñ�ί�У������쳣������������ConnectError��InitializeError
     * @param[ in ] context �������ӵ�������
     * @exception ConnectError �����ӷ�������ʱ�����ô�����ί��ʱ������</exception>
     * @exception InitializeError ��ʼ����������������ʱ�����ô�����ί��ʱ������</exception>
	 */
    virtual void connect(BuildProtocol buildProtocol, OnConnectError onConnectError, void* context ) = 0;

	/**
	 * ���ӵ�Ŀ���ַ
	 */
    virtual const IEndpoint& connectTo() const = 0;

	/**
	 * ȡ�õ�ַ������
	 */
	virtual const tstring& toString() const = 0;
};

class IConnectorFactory
{
public:

	virtual ~IConnectorFactory(){}

	/**
	 * ���� IConnector ����
	 */
	virtual IConnector* createConnector() = 0;

	/**
	 * ȡ�õ�ַ������
	 */
	virtual const tstring& toString() const = 0;
};

inline tostream& operator<<( tostream& target, const IConnector& connector )
{
	target << connector.toString();
	return target;
}

inline tostream& operator<<( tostream& target, const IConnectorFactory& connectorFactory )
{
	target << connectorFactory.toString();
	return target;
}

_jingxian_end

#endif // CONNECTOR_H
