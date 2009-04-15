
#ifndef _REACTORARBITRARY_H_
#define _REACTORARBITRARY_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "connector.h"
# include "acceptor.h"

_jingxian_begin

public class IReactorCore : public IConcurrentPort
{
public:
	virtual ~IReactorCore() {};

    /**
	 * ����һ��������
	 */
    connector* connectWith(const tchar* endPoint);

	
    /**
	 * ����һ��������
	 */
    connector* connectWith(const tchar* endPoint
            , IDictionary& kw);

	
    /**
	 * ����һ����������
	 */
    acceptor* listenWith(const IEndpoint& endPoint
		, IProtocolFactory* protocolFactory);

	/**
	 * ��ʼ����ֱ������Interrupt�ŷ���
	 */
	void runForever();

	/**
	 * ֹͣ����
	 */
	void interrupt();

	/**
	 * ������󶨵����˿�
	 */
	bool bind(HANDLE systemHandler);
};

_jingxian_end

#endif // _REACTORARBITRARY_H_