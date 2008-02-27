// Communication


#ifndef __Hazel_IOBUF__H__
#define __Hazel_IOBUF__H__

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "../config_Networks.h"
#include "hazel_sap.h"

_networks_begin

class IOBuf
{
public:

	iovec* data()
	{
		return &iovec_buf[0];
	}

	virtual size_t size() const
	{
		return iovec_buf.size();
	}

	void calc( size_t bytes_transferred )
	{
		//重新计算m_data_中的长度。
		for( size_t i = 0; i < iovec_buf.size(); i ++ )
		{
			if( bytes_transferred > iovec_buf[i].len )
			{
				bytes_transferred -= iovec_buf[i].len;
				iovec_len[ i ] = iovec_buf[i].len;
				continue;
			}
			iovec_buf[i].len = bytes_transferred;
			iovec_len[ i ] = bytes_transferred;
			bytes_transferred = 0;
			break;
		}
	}

	void addbuf( )
private:
	std::vector< iovec > iovec_buf;
	std::vector< size_t > iovec_len;
};

_networks_end

#endif // __Hazel_IOBUF__H__