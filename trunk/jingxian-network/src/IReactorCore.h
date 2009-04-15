
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
	 * 创建一个连接器
	 */
    connector* connectWith(const tchar* endPoint);

	
    /**
	 * 创建一个连接器
	 */
    connector* connectWith(const tchar* endPoint
            , IDictionary& kw);

	
    /**
	 * 创建一个监听服务
	 */
    acceptor* listenWith(const IEndpoint& endPoint
		, IProtocolFactory* protocolFactory);

	/**
	 * 开始运行直到调用Interrupt才返回
	 */
	void runForever();

	/**
	 * 停止运行
	 */
	void interrupt();

	/**
	 * 将句柄绑定到本端口
	 */
	bool bind(HANDLE systemHandler);
};

_jingxian_end

#endif // _REACTORARBITRARY_H_