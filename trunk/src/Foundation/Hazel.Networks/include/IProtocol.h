
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "ITransport.h"

_networks_begin

    public class ProtocolContext
    {
        ITrace _trace;
        IReactorCore _reactor;
        IProtocolFactory _protocolFactory;
        ITransport _transport;
        IDictionary<string, object> _misc;

        public ProtocolContext( ITrace trace
            , IReactorCore reactor
            , IProtocolFactory protocolFactory
            , ITransport transport
            , IDictionary<string, object> misc)
        {
            _trace = trace;
            _reactor = reactor;
            _protocolFactory = protocolFactory;
            _transport = transport;
            _misc = (misc??new Dictionary<string, object>());
        }

        public ProtocolContext(IProtocolFactory protocolFactory
            , IDictionary<string, object> misc)
            : this(null, null, protocolFactory, null, misc)
        {
        }

        /// <summary>
        /// ����Ϊnull
        /// </summary>
        public IProtocolFactory ProtocolFactory
        {
            get { return _protocolFactory; }
            set { _protocolFactory = value; }
        }

        public IReactorCore Reactor
        {
            get { return _reactor; }
            set { _reactor = value; }
        }

        public ITransport Transport
        {
            get { return _transport; }
            set { _transport = value; }
        }

        public ITrace Trace
        {
            get { return _trace; }
            set { _trace = value; }
        }

        public IDictionary<string, object> Misc
        {
            get { return _misc; }
        }
    }

    public delegate void DataReceived(ProtocolContext context, ByteBuffer buffer);

    public interface IProtocol
    {
        /// <summary>
        /// ��ָ����ʱ�����û���յ��κ�����
        /// </summary>
        /// <param name="context">�Ự��������</param>
        void OnTimeout(ProtocolContext context);

        /// <summary>
        /// ���Ự�����󣬱����á�
        /// </summary>
        /// <param name="context">�Ự��������</param>
        void OnConnection(ProtocolContext context);

        /// <summary>
        /// ���Ự�رպ󣬱����á�
        /// </summary>
        /// <param name="context">�Ự��������</param>
        /// <param name="reason"></param>
        void OnDisconnection(ProtocolContext context, Exception reason);

        /// <summary>
        /// �����µ���Ϣ����ʱ�������á�
        /// </summary>
        /// <param name="context">�Ự��������</param>
        /// <param name="buffer">�����µ�����Ϣ�Ļ�����</param>
        void OnReceived(ProtocolContext context, ByteBuffer buffer);

        /// <summary>
        /// �����´�������ȡ���ݵĻ�����
        /// </summary>
        /// <param name="lastBuffer">��һ��������ȡ���ݵĻ�����</param>
        /// <returns></returns>
        ByteBuffer CreateBuffer(ByteBuffer lastBuffer);
    };

_networks_end

#endif
