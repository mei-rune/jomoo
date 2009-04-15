
#ifndef _LOGUTILS_H_
#define _LOGUTILS_H_

#include "config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

#include "logger.h"
#include "tracer.h"
#include "jingxian_export.h"


_jingxian_begin

namespace logging
{
	logger* makeLogger( const tchar* nm );

	logger* makeLogger( const tstring& nm );

	tracer* makeTracer( const tchar* nm );

	tracer* makeTracer( const tstring& nm );
}

_jingxian_end

#endif //_LOGUTILS_H_