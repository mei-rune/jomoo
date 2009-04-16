
#ifndef _REACTORARBITRARY_H_
#define _REACTORARBITRARY_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "IConcurrentPort.h"
# include "IEndpoint.h"
# include "ITransport.h"
# include "IProtocol.h"
# include "IProtocolFactory.h"
# include "IConnector.h"
# include "IAcceptor.h"

_jingxian_begin

public class IReactorCore : public IConcurrentPort
{
public:
	virtual ~IReactorCore() {};

    /**
	 * ����һ��������
	 */
    virtual IConnector* connectWith(const tchar* endPoint) = 0;

	
    /**
	 * ����һ��������
	 */
    virtual IConnector* connectWith(const tchar* endPoint
			, IDictionary& kw) = 0;

    /**
	 * ����һ����������
	 */
    virtual IAcceptor* listenWith( const tchar* endPoint
			, IProtocolFactory* protocolFactory) = 0;
	
	/**
	 * ��ʼ����ֱ������Interrupt�ŷ���
	 */
	virtual void runForever() = 0;

	/**
	 * ֹͣ����
	 */
	virtual void interrupt() = 0;

	/**
	 * ������󶨵����˿�
	 */
	virtual bool bind(HANDLE systemHandler) = 0;
};

_jingxian_end

#endif // _REACTORARBITRARY_H_