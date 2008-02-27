
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
        /// 可能为null
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
        /// 在指定的时间段内没有收到任何数据
        /// </summary>
        /// <param name="context">会话的上下文</param>
        void OnTimeout(ProtocolContext context);

        /// <summary>
        /// 当会话建立后，被调用。
        /// </summary>
        /// <param name="context">会话的上下文</param>
        void OnConnection(ProtocolContext context);

        /// <summary>
        /// 当会话关闭后，被调用。
        /// </summary>
        /// <param name="context">会话的上下文</param>
        /// <param name="reason"></param>
        void OnDisconnection(ProtocolContext context, Exception reason);

        /// <summary>
        /// 当有新的信息到来时，被调用。
        /// </summary>
        /// <param name="context">会话的上下文</param>
        /// <param name="buffer">包含新到来信息的缓冲区</param>
        void OnReceived(ProtocolContext context, ByteBuffer buffer);

        /// <summary>
        /// 创建下次用来读取数据的缓冲区
        /// </summary>
        /// <param name="lastBuffer">上一次用来读取数据的缓冲区</param>
        /// <returns></returns>
        ByteBuffer CreateBuffer(ByteBuffer lastBuffer);
    };

_networks_end

#endif
