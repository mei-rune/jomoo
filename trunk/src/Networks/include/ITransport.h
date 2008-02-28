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
         * ָ����IProtocol�ӿ������ն���������
         */
        virtual void bindProtocol(IProtocol protocol) = 0;

        /**
         * ��ʼ������
         */
        virtual void startReading() = 0;

        /**
         * ֹͣ������
         */
        virtual void stopReading() = 0;

        /**
         * �������ݣ�ע�������첽��  )
         *	@param[ in ] buffer �����͵����ݿ�</param>
         * <param name="byteBuffer">�����͵����ݿ�</param>
         * <param name="byteBuffers">��������͵����ݿ�</param>
         * <param name="offest">����ƫ��</param>
         * <param name="length">���ݳ���</param>
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
         * �ر�����
         */
        virtual void disconnection() = 0;
        virtual void disconnection( const string& err) = 0;

        /**
         * Դ��ַ
         */
        virtual const Endpoint& getHost() const = 0;

        /**
         * Ŀ���ַ
         */
        virtual const Endpoint& getPeer() const = 0;

        /**
         * ����<see cref="IProtocol"/>��OnTimeout�¼��ĳ�ʱʱ��
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
