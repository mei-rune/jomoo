using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.ComponentModel;

namespace Betanetworks.ManagedIOCP.TCP
{
    using Betanetworks.Commons;
    using Betanetworks.Commons.Error;
    using Betanetworks.Commons.Threading;
    using Betanetworks.Sockets;

    class AcceptRequest : OverlappedOp, IOperationResult, IDisposable
    {
        HazelSocket _listenSocket;
        HazelSocket _socket;
        ByteBuffer _byteBuffer;
        Acceptor _acceptor;

        public AcceptRequest(Acceptor listeningPort, HazelSocket listenSocket, HazelSocket socket)//, int dataLength)
            : base(null)
        {
            _acceptor = listeningPort;
            _listenSocket = listenSocket;
            _socket = socket;
            _byteBuffer = new ByteBuffer((HazelAddress.MaxSize + 4) * 2 + 100); //dataLength);
            PinObject(_byteBuffer.Array);
        }

        public void Complete(int bytes_transferred, bool success, int error, object context)
        {
            if (!_acceptor.IsListening)
            {
                _acceptor.Logger.Info("获取连接返回,但已经停止监听!");
                _acceptor.DecrementAccepting();
                return;
            }

            if (!success)
            {
                Exception err = new SocketException(error);
                _acceptor.OnError(new AcceptError(_acceptor.BindPoint, string.Format("获取端口[{0}]的连接失败 - {1}!", _acceptor.BindPoint, err.Message), err));
            }
            else
            {
                InitializeConnection(bytes_transferred, context);
            }

            try
            {
                _acceptor.doAccept();
            }
            catch (AcceptError e)
            {
                _acceptor.OnError(e);
            }
            catch (Exception e)
            {
                _acceptor.OnError(new AcceptError(_acceptor.BindPoint, e));
            }

            _acceptor.DecrementAccepting();
        }

        void InitializeConnection(int bytes_transferred, object context)
        {
            IntPtr bytePointer = Marshal.UnsafeAddrOfPinnedArrayElement(
                    _byteBuffer.Array, _byteBuffer.End);
            HazelAddress localAddr = null;
            HazelAddress remoteAddr = null;

            HazelSocket.GetAcceptExSockaddrs(bytePointer
                , 0
                , HazelAddress.MaxSize + 4
                , HazelAddress.MaxSize + 4
                , out localAddr
                , out remoteAddr);

            _byteBuffer.End += bytes_transferred;
            _byteBuffer.Begin += (2 * (HazelAddress.MaxSize + 4));

            _socket.SetLocalAddress(localAddr);
            _socket.SetRemoteAddress(remoteAddr);

            _socket.SetSockOpt(SocketOptionLevel.Socket, SocketOptionName.UpdateAcceptContext, _socket.Handle);


            _acceptor.Logger.InfoFormat("获取到来自[{0}]的连接,开始初始化!", _socket.RemoteEndPoint);

            IOCPCore core = _acceptor.Core.GetNextCore();
            if (!core.Bind(_socket))
            {
                Win32Exception err = new Win32Exception();
                _acceptor.OnError(new InitializeError(_acceptor.BindPoint, string.Format("初始化来自[{0}]的连接时，绑定到iocp发生错误 - {0}", _socket.RemoteEndPoint, err.Message), err));
                return;
            }

            InitializeError initializeError = null;
            ConnectedSocket connectedSocket = null;
            try
            {
                IDictionary<string, object> misc = (null == _acceptor.ProtocolFactory) ? null : _acceptor.ProtocolFactory.Misc;
                connectedSocket = new ConnectedSocket(core, _socket, new ProtocolContext(null, misc));
                IProtocol protocol = _acceptor.CreateProtocol(connectedSocket);
                core.InitializeConnection(connectedSocket, protocol);
                _acceptor.Logger.InfoFormat("初始化来自[{0}]的连接成功!", _socket.RemoteEndPoint);
                _socket = null;
            }
            catch (InitializeError e)
            {
                initializeError = e;
            }
            catch (Exception e)
            {
                initializeError = new InitializeError(_socket.RemoteEndPoint, "在处理新连接时发生异常!", e);
            }

            if (null != initializeError)
            {
                if (null != connectedSocket)
                    connectedSocket.ReleaseSocket();

                _acceptor.OnError(initializeError);
            }
        }

        public void Accept()
        {
            IntPtr bytePointer = Marshal.UnsafeAddrOfPinnedArrayElement(
                _byteBuffer.Array, _byteBuffer.End);

            if (null == _socket)
            {
                _socket = _acceptor.CreateSocket(_listenSocket.AddressFamily
                    , _listenSocket.SocketType, _listenSocket.ProtocolType);
            }

            int bytesTransferred;
            if (_listenSocket.AcceptEx(_socket, bytePointer
                , 0 //_byteBuffer.Space - (HazelAddress.MaxSize + 4) * 2 
                //必须为0,否则会有大量的连接处于accept中，因为客户端只
                //建立连接，没有发送数据。
                , HazelAddress.MaxSize + 4
                , HazelAddress.MaxSize + 4
                , out bytesTransferred
                , NativeOverlapped))
                return;

            if ((int)SocketError.IOPending == Marshal.GetLastWin32Error())
                return;

            throw new AcceptError(_acceptor.BindPoint, new SocketException());
        }

        public override void internalDispose()
        {
            base.internalDispose();

            if (null == _socket)
                return;

            try
            {
                _acceptor.ReleaseSocket(_socket, false);
            }
            catch
            { }
            _socket = null;
        }
    }
}
