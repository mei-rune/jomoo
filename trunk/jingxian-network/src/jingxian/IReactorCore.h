
#ifndef _IReactorCore_H_
#define _IReactorCore_H_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "jingxian/IConcurrentPort.h"
# include "jingxian/IEndpoint.h"
# include "jingxian/ITransport.h"
# include "jingxian/IProtocol.h"
# include "jingxian/IProtocolFactory.h"
# include "jingxian/IConnector.h"
# include "jingxian/IAcceptor.h"

_jingxian_begin

class IReactorCore : public IConcurrentPort
{
public:
	virtual ~IReactorCore() {};

    /**
	 * ����һ��������
	 */
    virtual IConnector* connectWith(const tchar* endPoint) = 0;

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

#endif // _IReactorCore_H_