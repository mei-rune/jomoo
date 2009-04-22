
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
# include "jingxian/IConnectionBuilder.h"
# include "jingxian/IAcceptor.h"

_jingxian_begin

class IReactorCore : public IConcurrentPort
{
public:
	virtual ~IReactorCore() {};

    /**
	 * ����һ������
	 * @param[ in ] endPoint ���ӵ�Ŀ���ַ
	 * @param[ in ] buildProtocol �ɹ�����ʱ����Э�鴦�����Ļص�����
	 * @param[ in ] onConnectError ����ʧ��ʱ������Ļص�����
	 * @param[ in ] context �ص�������������
	 * @remarks �ص��������ܻ��ڵ����߳���ֱ�ӱ�����
	 */
    virtual void connectWith(const tchar* endPoint
                            , BuildProtocol buildProtocol
                            , OnConnectError onConnectError
                            , void* context ) = 0;

    /**
	 * ����һ����������
	 *
	 * @param[ in ] endPoint �����ĵ�ַ
	 * @param[ in ] protocolFactory Э�鴦��������
	 * @return �ɹ������ش����Ķ���ʧ��ʱ���� NULL
	 * @remarks ��Ҫ����ɾ�����صĶ��󣬸ö����ѱ� IReactorCore ���С�
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