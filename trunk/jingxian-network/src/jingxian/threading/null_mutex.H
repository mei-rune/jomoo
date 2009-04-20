

#ifndef null_mutex_H
#define null_mutex_H

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "jingxian/threading/guard.h"

_jingxian_begin

class null_mutex
{
public:
	
	typedef guard< null_mutex > spcode_lock;

	null_mutex()
	{
		
	}

	~null_mutex()
	{
		
	}

	bool acquire()
	{
		return true;
	}
	void release()
	{
	}

#if(_WIN32_WINNT >= 0x0400)
	bool tryacquire()
	{
		return true;
	}
#endif

private:
	DECLARE_NO_COPY_CLASS( null_mutex );
};

_jingxian_end


#endif // null_mutex_H