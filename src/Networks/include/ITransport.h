using System;
using System.Collections.Generic;
using System.Text;
using System.Net;

namespace Networks
{
    using Betanetworks.Commons;
    using Betanetworks.Commons.Threading;

    class ITransport
    {
	public:

		virtual ~ITransport(){};

        /**
         * 指定用IProtocol接口来接收读到的数据
         */
        virtual void bindProtocol(IProtocol protocol) = 0;

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
         *	@param[ in ] buffer 待发送的数据块</param>
         * <param name="byteBuffer">待发送的数据块</param>
         * <param name="byteBuffers">多个待发送的数据块</param>
         * <param name="offest">数据偏移</param>
         * <param name="length">数据长度</param>
		 */
        virtual void write(byte[] buffer);
        virtual void write(byte[] buffer, int offest, int length);
        virtual void write(ByteBuffer byteBuffer);
        virtual void write(ByteBuffer[] byteBuffers);
	};

	class ITCPTransport : public ITransport
    {
	public:

		virtual ~ITCPTransport(){};

        /**
         * 关闭连接
         */
        virtual void disconnection() = 0;
        virtual void disconnection( const string& err) = 0;

        /**
         * 源地址
         */
        virtual const Endpoint& getHost() const = 0;

        /**
         * 目标地址
         */
        virtual const Endpoint& getPeer() const = 0;

        /**
         * 引发<see cref="IProtocol"/>的OnTimeout事件的超时时间
         */
        virtual const TimeSpan& getTimeout() const = 0;


		
		virtual bool getNoDelay() const = 0;

		virtual void setNoDelay(bool value) = 0;

		virtual bool getKeepAlive() const = 0;

		virtual void setKeepAlive(bool value) = 0;

		virtual bool getKeepAlive() const = 0;

		virtual void setKeepAlive(bool value) = 0;

        int SendBufferSize { get;set; }

        int ReceiveBufferSize { get;set; }
    }
}
