
#include "pro_config.h"
#include "jingxian/IOCPServer.h"

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

	ThrowException( NotImplementedException );
}

IAcceptor* IOCPServer::listenWith(const tchar* endPoint
			, IProtocolFactory* protocolFactory)
{
	ThrowException( NotImplementedException );
}
	
void IOCPServer::send( IRunnable* runnable )
{
	ThrowException( NotImplementedException );
}
	
void IOCPServer::runForever()
{
	ThrowException( NotImplementedException );
}
	
void IOCPServer::interrupt()
{
	ThrowException( NotImplementedException );
}
	
bool IOCPServer::bind(HANDLE systemHandler)
{
	ThrowException( NotImplementedException );
}
	
const tstring& IOCPServer::toString() const
{
	ThrowException( NotImplementedException );
}


_jingxian_end
