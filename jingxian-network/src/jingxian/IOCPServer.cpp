
#include "pro_config.h"
#include "IOCPServer.h"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_jingxian_begin

IOCPServer::IOCPServer(void)
{
}

IOCPServer::~IOCPServer(void)
{
}

IConnector* IOCPServer::connectWith(const tchar* endPoint)
{
}

IConnector* IOCPServer::connectWith(const tchar* endPoint
			, IDictionary& kw)
{
}

IAcceptor* IOCPServer::listenWith(const tchar* endPoint
			, IProtocolFactory* protocolFactory)
{
}
	
void IOCPServer::send( IRunnable* runnable )
{
}
	
void IOCPServer::runForever()
{
}
	
void IOCPServer::interrupt()
{
}
	
bool IOCPServer::bind(HANDLE systemHandler)
{
}
	
const tstring& IOCPServer::toString() const
{
}


_jingxian_end
