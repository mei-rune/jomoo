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
                _acceptor.Logger.Info("��ȡ���ӷ���,���Ѿ�ֹͣ����!");
                _acceptor.DecrementAccepting();
                return;
            }

            if (!success)
            {
                Exception err = new SocketException(error);
                _acceptor.OnError(new AcceptError(_acceptor.BindPoint, string.Format("��ȡ�˿�[{0}]������ʧ�� - {1}!", _acceptor.BindPoint, err.Message), err));
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


            _acceptor.Logger.InfoFormat("��ȡ������[{0}]������,��ʼ��ʼ��!", _socket.RemoteEndPoint);

            IOCPCore core = _acceptor.Core.GetNextCore();
            if (!core.Bind(_socket))
            {
                Win32Exception err = new Win32Exception();
                _acceptor.OnError(new InitializeError(_acceptor.BindPoint, string.Format("��ʼ������[{0}]������ʱ���󶨵�iocp�������� - {0}", _socket.RemoteEndPoint, err.Message), err));
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
                _acceptor.Logger.InfoFormat("��ʼ������[{0}]�����ӳɹ�!", _socket.RemoteEndPoint);
                _socket = null;
            }
            catch (InitializeError e)
            {
                initializeError = e;
            }
            catch (Exception e)
            {
                initializeError = new InitializeError(_socket.RemoteEndPoint, "�ڴ���������ʱ�����쳣!", e);
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
                //����Ϊ0,������д��������Ӵ���accept�У���Ϊ�ͻ���ֻ
                //�������ӣ�û�з������ݡ�
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
