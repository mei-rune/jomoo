
#ifndef _transport_h_
#define _transport_h_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "buffer.h"
# include "IEndpoint.h"
# include "exception.hpp"

_jingxian_begin

class IProtocol;

class ITransport
{
public:
	virtual ~ITransport(){}

		/**
         * 指定用 @see{protocol} 接口来接收读到的数据
         */
        virtual void bindProtocol(IProtocol* protocol) = 0;

        /**
         * 开始读数据
         */
        virtual void startReading() = 0;

        /**
         * 停止读数据
         */
        virtual void stopReading() = 0;

        /**
         * 发送数据（注意它是异步的  )
         * @param[ in ] handle  异步回调接口,当数据发送操作（不管成功，失败，撤消）
         *				调用成功，都会回调handle的onWrite接口
         * @param[ in ] buffer 待发送的数据块
         * @param[ in ] IOBuffer 待发送的数据块
         * @param[ in ] IOBuffers 多个待发送的数据块
         * @param[ in ] offest 数据偏移
         * @param[ in ] length 数据长度
         */
        virtual void write(char* buffer) = 0;
        virtual void write(char* buffer, int offest, int length) = 0;
        virtual void write(Buffer& buffer) = 0;

        /**
         * 关闭连接
         */
        virtual void disconnection() = 0;
		
		/**
         * 关闭连接
         */
        virtual void disconnection(const Exception& error) = 0;

        /**
         * 源地址
         */
        virtual const IEndpoint& host() const = 0;

        /**
         * 目标地址
         */
        virtual const IEndpoint& peer() const = 0;

        /**
         * 引发 @see{protocol} 的onTimeout事件的超时时间
         */
        virtual time_t timeout() const = 0;

		/**
		 * 取得地址的描述
		 */
		virtual const tstring& toString() const = 0;
};

inline tostream& operator<<( tostream& target, const ITransport& transport )
{
	target << transport.toString();
	return target;
}

_jingxian_end

#endif //_transport_h_