using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;


namespace Betanetworks.ManagedIOCP.TCP
{
    using Betanetworks.Sockets;
    using Betanetworks.Commons;
    using Betanetworks.Commons.Error;
    using Betanetworks.Commons.Threading;

    internal class DisconnectRequest : OverlappedOp, IOperationResult, IDisposable
    {
        ConnectedSocket _connectedSocket;
        Exception _exception;

        public DisconnectRequest(ConnectedSocket connectedSocket,Exception error)
            : base( null )
        {
            _connectedSocket = connectedSocket;
            _exception = error;
        }

        public void Complete(int bytes_transferred, bool success, int error, object context)
        {
            _connectedSocket.OnDisconnection(_exception);
        }

        public void Disconnect()
        {
            if (_connectedSocket.Socket.DisconnectEx(this.NativeOverlapped
                , IoctlSocketConstants.TF_REUSE_SOCKET, 0))
                return;

            int errCode = Marshal.GetLastWin32Error();
            if ((int)SocketError.IOPending == errCode)
            {
                return;
            }

            throw new ReadError(errCode);
        }
    }
}
