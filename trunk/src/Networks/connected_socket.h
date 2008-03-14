

#ifndef _connected_socket_h_
#define _connected_socket_h_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "Platform/OS.H"
#include "proactor.h"

_networks_begin


/**
 * On��ͷ�ĺ������û�ֱ�ӵ��õķ����в�����ʹ�á�
 * ���û����õķ���ΪITransport�ӿ��еķ���
 */
template<typename Protocol>
class connected_socket
{

public:
	
	connected_socket(proactor& core)
		: _port( core )
    {
    }

    protected void internalRead(ByteBuffer byteBuffer)
    {
        ReadError error = null;
        try
        {
            while (0 != _readBuffer.Count)
            {
                ByteBuffer firstBuffer = _readBuffer.First.Value;
                _readBuffer.RemoveFirst();
                _protocol.OnReceived(_context, firstBuffer);
                if (!_reading)
                    return;
            }

            doRead(byteBuffer);
            return;
        }
        catch (ReadError err)
        {
            error = err;
        }
        catch (Exception e)
        {
            error = new ReadError(e, e.Message);
        }
        OnException(error);
    }

    protected void doRead(ByteBuffer byteBuffer)
    {
        _trace.Info(TransportWay.Receive ,"��ʼ������");

        ByteBuffer readBuffer = (null != _protocol) ?
            (_protocol.CreateBuffer(byteBuffer) ?? new ByteBuffer(BaseProtocol.BUFFEREDSIZE)) : new ByteBuffer(BaseProtocol.BUFFEREDSIZE );

        new ReadFileOp(this, readBuffer).Read();
    }

    protected void cbRead(ByteBuffer byteBuffer)
    {
        _port.Send<ByteBuffer>(this.internalRead, byteBuffer);
    }

    public void StartReading()
    {
        if (_state != ConnectionStatus.connected)
        {
            _trace.Info(TransportWay.Receive, "ͨ���Ѿ��ر�!");
            throw new RuntimeError("ͨ���Ѿ��ر�!");
        }

        if (_reading)
        {
            _trace.Info(TransportWay.Receive, "ͨ���Ѿ��ڶ�����!");
            return;
        }

        if (null == _protocol)
            throw new RuntimeError("û�г�ʼ��protocol����!");

        ReadError error = null;
        try
        {
            startReading(null);
            return;
        }
        catch (ReadError err)
        {
            error = err;
        }
        catch (Exception exception)
        {
            error = new ReadError(exception, exception.Message);
        }

        _port.Send<ReadError>(this.OnException, error);
    }

    public void startReading(ByteBuffer byteBuffer)
    {
        _reading = true;
        if (0 != _readBuffer.Count)
        {
            cbRead(byteBuffer);
        }
        else
        {
            doRead(byteBuffer);
        }
    }

    public void StopReading()
    {

        _trace.Info(TransportWay.Receive, "ֹͣ������!");
        _reading = false;
    }

    internal void OnRead(ByteBuffer byteBuffer)
    {
        if (_state != ConnectionStatus.connected)
        {
            _reading = false;
            _trace.Info(TransportWay.Receive, "��������ɣ���ͨ���Ѿ����ر�!");
            return;
        }


        _trace.Info(TransportWay.Receive, "�����ݳɹ�!");

        _trace.WriteInboundBuffer(byteBuffer);

        _triggeredTime = DateTime.Now;

        if (_reading)
        {
            _protocol.OnReceived(_context, byteBuffer);

            if (_state != ConnectionStatus.connected)
            {
                _trace.Info(TransportWay.Receive, "����������ɣ�ͨ�����رգ����ٶ�����!");
                return;
            }
            startReading( byteBuffer );
        }
        else
        {
            _trace.Info(TransportWay.Receive, "�����ݳɹ������Ѿ���ͣ������!");
            _readBuffer.AddLast(byteBuffer);
        }
    }

    internal void OnException(ReadError error)
    {
        _reading = false;
        if (_state != ConnectionStatus.connected)
        {
            _trace.Error(TransportWay.Receive, "������ʱ��������ʱ,�����ѹر�!", error);
            return;
        }

        _trace.Error(TransportWay.Receive, string.Format( "������ʱ�������� - {0}!", error.Message), error );
        close(error);
    }

    #endregion

    #region Write

    public void Write(byte[] data)
    {
        if (null == data || 0 == data.Length)
            return;

        Write(new ByteBuffer(data, 0, data.Length));
    }


    public void Write(byte[] data, int offest, int length)
    {
        if (null == data || 0 == data.Length)
            return;

        if (data.Length < (offest + length))
            return;

        Write(new ByteBuffer(data, offest, length));
    }

    public void Write(ByteBuffer[] byteBuffers)
    {
        if (null == byteBuffers || 0 == byteBuffers.Length)
            return;
        foreach (ByteBuffer byteBuffer in byteBuffers)
            Write(byteBuffer);
    }

    public void Write(ByteBuffer byteBuffer)
    {
        if (null == byteBuffer || 0 == byteBuffer.Count)
            return;

        if (ConnectionStatus.connected != _state
            && ConnectionStatus.disconnecting != _state)
        {
            _trace.Info(TransportWay.Send, "д����ʱͨ���Ѿ��ر�!");
            return;
        }


        if (null == _protocol)
            throw new RuntimeError("û�г�ʼ��protocol����!");

        _writebuf.AddLast(byteBuffer);
        _writeBufferedSize += byteBuffer.Count;

        if (_writing)
            return;

        _trace.Info(TransportWay.Send, "��ʼд����!");

        WriteError error;
        try
        {
            startWriting();
            return;
        }
        catch (WriteError err)
        {
            error = err;
        }
        catch (Exception exception)
        {
            error = new WriteError(exception, exception.Message);
        }

        _port.Send<WriteError>(this.OnException, error);
    }

    protected void startWriting()
    {
        _writing = true;
        ByteBuffer byteBuffer = _writebuf.First.Value;
        _trace.WriteOutboundBuffer(byteBuffer);

        new WriteRequest(this, byteBuffer).Write();
    }

    protected void stopWriting()
    {
        _trace.Info(TransportWay.Send, "ֹͣд����!");
        _writing = false;
    }

    internal void OnWrite(int bytes_transferred, ByteBuffer byteBuffer)
    {
        _writeBufferedSize -= bytes_transferred;
        byteBuffer.Begin += bytes_transferred;

        _triggeredTime = DateTime.Now;

        if (0 < byteBuffer.Count)//û�д�����ȫ��
        {
            startWriting();
            return;
        }

        if (0 > byteBuffer.Count)
        {
            _writing = false;

            _trace.Error(TransportWay.Send, "д����ʱ���ִ��� - һ�δ�����ֽ������ܴ������ֽ���!");
            throw new WriteError("һ�δ�����ֽ������ܴ������ֽ���!");
        }

        _writebuf.RemoveFirst();

        if (0 != _writebuf.Count)
        {
            startWriting();
            return;
        }
        _writing = false;
        _trace.Info(TransportWay.Send, "д������� - buffer�Ѿ�Ϊ��!");

        if (_isDisconnectingOnEmpty)
        {
            _isDisconnectingOnEmpty = false;
            _isShutdownOnEmpty = false;
            doClose(_disconnectingArg);
        }
        else if (_isShutdownOnEmpty)
        {
            _isShutdownOnEmpty = false;
            _socket.Shutdown(SocketShutdown.Send);
        }
    }

    internal void OnException(WriteError error)
    {
        _writing = false;
        if (_state != ConnectionStatus.connected
            && _state != ConnectionStatus.disconnecting)
        {
            _trace.Error(TransportWay.Send, "д����ʱ��������,��ͨ���ѹر�!", error);
            return;
        }

        _trace.Error(TransportWay.Send,  string.Format( "д����ʱ��������,�ر�ͨ�� - {0}!", error.Message), error );
        doClose(error);
    }

    #endregion

    #region Disconnection

    protected void cbDisconnection(Exception e)
    {
        if (_isDisconnectingOnEmpty)
        {
            _trace.Info(TransportWay.Receive, "����д�������ʱ�ر�ͨ�� - �Ѿ��ڵȴ���!");
            return;
        }

        _trace.Info(TransportWay.Receive, "����д�������ʱ�ر�ͨ��!");

        _isDisconnectingOnEmpty = true;
        _state = ConnectionStatus.disconnecting;
        _disconnectingArg = e;
    }

    public void OnDisconnection(Exception error)
    {
        doClose(error);
    }

    protected void doClose(Exception exception)
    {
        _trace.Info(TransportWay.Both, "��ʼ�ر�ͨ��!");

        _state = ConnectionStatus.disconnected;

        if (null == _socket)
            return;

        IProtocol protocol = _protocol;
        _protocol = null;

        try
        {
            if (null != protocol)
                _port.Disconnection(this, protocol, exception);
        }
        catch( Exception e)
        {
            _trace.Info(TransportWay.Both, "��ʼ�ر�ͨ��ʱ, ����ϵͳ�Ͽ��¼���������!", e );
        }
        if (_read_shutdown)
        {
            if (!_write_shutdown)
                _socket.Shutdown(SocketShutdown.Send);
        }
        else if (_write_shutdown)
        {
            _socket.Shutdown(SocketShutdown.Send);
        }
        else
        {
            _socket.Shutdown(SocketShutdown.Receive);
        }
        _read_shutdown = true;
        _write_shutdown = true;

        _socket.Close();
        _socket = null;
        try
        {
            if (null != protocol)
                protocol.OnDisconnection(_context, exception);
        }
        catch (Exception e)
        {
            _trace.Info(TransportWay.Both, "��ʼ�ر�ͨ��ʱ, �����Ͽ��¼���������!", e);
        }

        _trace.Info(TransportWay.Both, "�ر�ͨ�����!");
    }

    public void close(Exception exception)
    {
        _state = ConnectionStatus.disconnecting;
        if (_writing)
        {
            cbDisconnection(exception);
        }
        else
        {
            _trace.Info(TransportWay.Both, "���Թر�ͨ��!");
            doClose(exception);
        }
    }

    public void Disconnection()
    {
        Disconnection(new ConnectionDone("�ر�ͨ��!"));
    }
    public void Disconnection(Exception error)
    {
        if (_state != ConnectionStatus.connected)
        {
            _trace.Info(TransportWay.Both, "���Թر�ͨ��ʱ�����Ѿ��ر�ͨ����!");
            return;
        }

        StopReading();

        _state = ConnectionStatus.disconnecting;

        if (_writing)
        {
            cbDisconnection(error);
        }
        else
        {
            _trace.Info(TransportWay.Both, "���Թر�ͨ��!");

            _port.Send<Exception>(this.doClose, error);
        }
    }

    protected void cbShutdown(SocketShutdown arg)
    {
        if (_isDisconnectingOnEmpty)
        {
            _trace.Info(TransportWay.Both,"����д�������ʱShutdown�˿ڴ���! - �Ѿ��ڵȴ���!");
            return;
        }

        _trace.Info(TransportWay.Both, "����д�������ʱShutdown�˿ڴ���!");

        _isShutdownOnEmpty = true;
        _shutdownArg = arg;
    }

    public void Shutdown()
    {
        Shutdown(true, true);
    }

    public void Shutdown(bool write, bool read)
    {
        if (ConnectionStatus.connected != _state)
            return;

        if (read && !_read_shutdown)
        {
            _read_shutdown = true;

            _trace.Info(TransportWay.Both, "Shutdown�˿��չ���!");
            _socket.Shutdown(SocketShutdown.Receive);
        }

        if (write && !_write_shutdown)
        {
            _write_shutdown = true; // don't need to keep "we are shutting write side down", right?
            if (_writing)
            {
                cbShutdown(SocketShutdown.Send);
                //_isShutdownOnEmpty = true;
            }
            else
            {
                _trace.Info(TransportWay.Both, "Shutdown�˿ڷ�����!");
                _socket.Shutdown(SocketShutdown.Send);
            }
        }
    }

    #endregion

    #region ITransport ��Ա

    public Endpoint Host
    {
        get
        {
            //if (null != _socket)
            //    return _socket.LocalEndPoint;

            return _host;
        }
    }

    public Endpoint Peer
    {
        get
        {
            //if (null != _socket)
            //    return _socket.RemoteEndPoint;
            return _peer;
        }
    }

    public void BindProtocol( IProtocol protocol)
    {
        if (null == protocol)
            throw new ArgumentNullException("protocol");
        //if (null == context)
        //    throw new ArgumentNullException("context");

        //_context = context;

        //if (null == _context.Trace)
        //    _context.Trace = _trace;
        //_context.Transport = this;
        //if (null == _context.Reactor)
        //    _context.Reactor = _port;

        _protocol = protocol;
    }

    #endregion

    #region ITCPTransport ��Ա

    public bool NoDelay
    {
        get { return _socket.NoDelay; }
        set { _socket.NoDelay = value; }
    }

    public bool KeepAlive
    {
        get { return _socket.KeepAlive; }
        set { _socket.KeepAlive = value; }
    }

    public int SendBufferSize
    {
        get { return _socket.SendBufferSize; }
        set { _socket.SendBufferSize = value; }
    }

    public int ReceiveBufferSize
    {
        get { return _socket.ReceiveBufferSize; }
        set { _socket.ReceiveBufferSize = value; }
    }

    public IPEndPoint LocalEndPoint
    {
        get { return _socket.LocalEndPoint; }
    }

    public IPEndPoint RemoteEndPoint
    {
        get { return _socket.RemoteEndPoint; }
    }

    #endregion

    #region ITrigger ��Ա

    public void OnTimeout()
    {
        if (ConnectionStatus.connecting != _state)
            return;

        if (null != _protocol)
            _protocol.OnTimeout(_context);
    }

    public TimeSpan Timeout
    {
        get { return _timeout; }
    }

    public DateTime TriggeredTime
    {
        get { return _triggeredTime; }
        set { _triggeredTime = value; }
    }

private:

    proactor _core;
    Protocol _protocol;
    ITrace _trace;

    ProtocolContext _context;

    HazelSocket _socket;
    TCPEndpoint _host;
    TCPEndpoint _peer;

    ConnectionStatus _state = ConnectionStatus.connected;

    bool _writing = false;
    LinkedList<ByteBuffer> _writebuf = new LinkedList<ByteBuffer>();
    int _writeBufferedSize = 0; //_writebuf������byte���ܺ�

    bool _isDisconnectingOnEmpty = false;
    Exception _disconnectingArg = null;


    bool _isShutdownOnEmpty = false;
    SocketShutdown _shutdownArg = SocketShutdown.Both;

    bool _read_shutdown = false;
    bool _write_shutdown = false;

    //��ͣ����ʱ������������ʱ���λ��
    LinkedList<ByteBuffer> _readBuffer = new LinkedList<ByteBuffer>();
    bool _reading = false;

    // û��ȡ������ʱ����timeout�쳣��ʱ����
    TimeSpan _timeout = IOCPCore.TIMEOUT_INTERVAL;
    // ��һ�δ���timeout�쳣��ʱ��
    DateTime _triggeredTime = DateTime.Now;
}

_networks_end

#endif // _connected_socket_h_