
# include "pro_config.h"
# include "jingxian/logging/logutils.h"
# include "jingxian/logging/stdlogger.h"

_jingxian_begin

namespace logging
{

	StdLogger _console;

	logger* makeLogger( const tchar* nm )
	{
		return &_console;
	}

	logger* makeLogger( const tstring& nm )
	{
		return &_console;
	}
	
	//tracer* makeTracer( const tchar* nm )
	//{
	//	return 0;
	//}

	//tracer* makeTracer( const tstring& nm )
	//{
	//	return 0;
	//}
}

_jingxian_end