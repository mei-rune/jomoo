

#ifndef _write_request_h_
#define _write_request_h_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "../io_request.h"

_networks_begin

class write_request : io_request
{

public:
	write_request()
	{
	}

	void init(  )
	{
	}



	void on_complete(size_t bytes_transferred,
		int success,
		const void *completion_key,
		u_long error = 0)
	{
		WriteError exception = null;
		try
		{
			if (!success)
			{
				exception = new WriteError(error);
			}
			else if (0 == bytes_transferred)
			{
				exception = new WriteError(new SocketException((int)SocketError.Shutdown), "¶Á0¸ö×Ö½Ú!");
			}
			else
			{
				_transport.OnWrite(bytes_transferred, _byteBuffer);
				return;
			}
		}
		catch (WriteError err)
		{
			exception = err;
		}
		catch (Exception e)
		{
			exception = new WriteError(e, e.Message);
		}
		_transport.OnException(exception);
	}

	void post()
	{
		if (_transport.Socket.Write(bytePointer
			, _byteBuffer.Count
			, out bytesTransferred
			, NativeOverlapped))
			return;

		int errCode = Marshal.GetLastWin32Error();
		if ((int)SocketError.IOPending == errCode)
			return;

		throw new WriteError(errCode);
	}
private:
	connected_socket* _transport;
	std::vector<iovec> _iovec;
};

_networks_end

#endif 
