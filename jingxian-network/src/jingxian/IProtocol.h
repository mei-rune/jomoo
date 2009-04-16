
#ifndef _IProtocol_H_
#define _IProtocol_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "exception.hpp"

_jingxian_begin

class ProtocolContext;

class IProtocol
{
public:

	virtual ~IProtocol(){}

    /**
     * 在指定的时间段内没有收到任何数据
     * 
     * @param[ in ] context 会话的上下文
	 */
    void onTimeout(ProtocolContext& context);

    /**
     * 当会话建立后，被调用。
     * 
     * @param[ in ] context 会话的上下文
	 */
    void onConnection(ProtocolContext& context);

    /**
     * 当会话关闭后，被调用。
     * 
     * @param[ in ] context 会话的上下文
	 */
    void onDisconnection(ProtocolContext& context, Exception& reason);

    /**
     * 当有新的信息到来时，被调用。
     * 
     * @param[ in ] context 会话的上下文
     * @param[ in ] buffer 包含新到来信息的缓冲区
	 */
    void onReceived(ProtocolContext& context, Buffer& buffer);

    /**
     * 创建下次用来读取数据的缓冲区
     * 
     * @param[ in ] lastBuffer 上一次用来读取数据的缓冲区</param>
     * @param[ in ] buffer 包含新到来信息的缓冲区
	 */
	Buffer createBuffer(Buffer& lastBuffer);

	/**
	* 取得地址的描述
	*/
	virtual const tstring& toString() const = 0;
};

inline tostream& operator<<( tostream& target, const IProtocol& protocol )
{
	target << protocol.toString();
	return target;
}

_jingxian_end

#endif // _IProtocol_H_