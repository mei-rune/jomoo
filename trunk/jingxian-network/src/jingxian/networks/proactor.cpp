
# include "pro_config.h"
# include "proactor.h"
# include "Jexception.hpp"
# include "jingxian/logging/logging.hpp"
# include "jingxian/netowrks/commands/command_queue.h"

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_jingxian_begin

logger* iocpLogger;

logger* getLogger()
{
	if( null_ptr == iocpLogger)
		iocpLogger = logging::makeLogger(_T("jingxian.proactor") );
	return iocpLogger;
}

proactor::proactor(  )
: m_completion_port_( NULL )
{
}

proactor::proactor( size_t number_of_threads )
: m_completion_port_( NULL )
{
	open( number_of_threads );
}

proactor::~proactor(void)
{
}

bool proactor::is_good() const
{
	return NULL != m_completion_port_;
}

bool proactor::open ( size_t number_of_threads )
{
	if( ! is_null(m_completion_port_) )
		return false;

	m_number_of_threads_ = number_of_threads;
	m_completion_port_ = ::CreateIoCompletionPort (INVALID_HANDLE_VALUE,
		0,
		0,
		m_number_of_threads_);

	return  is_null(m_completion_port_);
}

void proactor::close (void)
{
	if (is_null(m_completion_port_ ))
		return ;

	for (;;)
	{
		OVERLAPPED *overlapped = 0;
		u_long bytes_transferred = 0;
#if defined (JOMOO_WIN64)
		ULONG_PTR completion_key = 0;
#else
		ULONG completion_key = 0;
#endif /* JOMOO_WIN64 */

		BOOL res = ::GetQueuedCompletionStatus
			(m_completion_port_,
			&bytes_transferred,
			&completion_key,
			&overlapped,
			0);  // poll

		if ( is_null(overlapped) || FALSE == res )
			break;

		command *asynch_result =
			(command *) overlapped;

		command_queue::release( asynch_result );
	}

	::CloseHandle( m_completion_port_);
	m_completion_port_ = NULL;

}

/// If the function dequeues a completion packet for a successful I/O operation 
/// from the completion port, the return value is nonzero. The function stores 
/// information in the variables pointed to by the lpNumberOfBytesTransferred, 
/// lpCompletionKey, and lpOverlapped parameters
/// 
/// 如果函数从端口取出一个完成包，且完成操作是成功的，则返回非0值。上下文数据
/// 保存在lpNumberOfBytesTransferred，lpCompletionKey，lpOverlapped中
/// 
/// If *lpOverlapped is NULL and the function does not dequeue a completion packet
/// from the completion port, the return value is zero. The function does not 
/// store information in the variables pointed to by the lpNumberOfBytes and 
/// lpCompletionKey parameters. To get extended error information, call GetLastError.
/// If the function did not dequeue a completion packet because the wait timed out,
/// GetLastError returns WAIT_TIMEOUT.
/// 
///如lpOverlapped 是NULL，没有从端口取出一个完成包，则返回0值。lpNumberOfBytesTransferred
/// ，lpCompletionKey，lpOverlapped也没有保存上下文数据，可以用GetLastError取
/// 得详细错误。如果没有从端口取出一个完成包，可能是超时，GetLastError返回WAIT_TIMEOUT
/// 
///If *lpOverlapped is not NULL and the function dequeues a completion packet for
/// a failed I/O operation from the completion port, the return value is zero. 
/// The function stores information in the variables pointed to by lpNumberOfBytes,
/// lpCompletionKey, and lpOverlapped. To get extended error information, call GetLastError.
/// 
///如果 lpOverlapped 不是NULL，但完成操作是失败的，则返回0值。上下文数据保存在
/// lpNumberOfBytesTransferred，lpCompletionKey，lpOverlapped中，可以用GetLastError
/// 取得详细错误。
/// 
///If a socket handle associated with a completion port is closed, GetQueuedCompletionStatus
/// returns ERROR_SUCCESS, with *lpOverlapped non-NULL and lpNumberOfBytes equal zero.
/// 
///如一个socket句柄被关闭了，GetQueuedCompletionStatus返回ERROR_SUCCESS， lpOverlapped 
/// 不是NULL,lpNumberOfBytes等于0。
/// 
/// </summary>
int proactor::handle_events (unsigned long milli_seconds)
{
	OVERLAPPED *overlapped = 0;
	u_long bytes_transferred = 0;

	ULONG_PTR completion_key = 0;

	BOOL result = ::GetQueuedCompletionStatus (m_completion_port_,
		&bytes_transferred,
		&completion_key,
		&overlapped,
		milli_seconds);
	if ( FALSE == result && is_null(overlapped) )
	{
		switch ( GetLastError() )
		{
		case WAIT_TIMEOUT:
			return 1;

		case ERROR_SUCCESS:
			return 0;

		default:
			return -1;
		}
	}
	else
	{
		command *asynch_result = (command *) overlapped;
		u_long error = 0;
		if( !result )
			error = GetLastError();

		this->application_specific_code (asynch_result,
			bytes_transferred,
			(void *) completion_key,
			error );
	}
	return 0;
}

void proactor::application_specific_code (ICommand *asynch_result,
														  size_t bytes_transferred,
														  const void *completion_key,
														  u_long error)
{
	try
	{
		asynch_result->on_complete (bytes_transferred,
			error == 0 ? 0 : 1,
			(void *) completion_key,
			error );
	}
	catch( std::exception& e )
	{
		FATAL( getLogger() , "error :" << e.what() );
	}
	catch( ... )
	{	
		FATAL( getLogger() , "unkown error!" );
	}
	
	command_queue::release( asynch_result );
}

bool proactor::post(ICommand *result )
{
	if( is_null( result ) )
		return false;
		
	DWORD bytes_transferred = 0;
	ULONG_PTR comp_key = 0;

	return TRUE == ::PostQueuedCompletionStatus (m_completion_port_, // completion port
		bytes_transferred ,      // xfer count
		comp_key,               // completion key
		result                  // overlapped
		);
}

HANDLE proactor::handle()
{
	return m_completion_port_;
}

bool proactor::bind (HANDLE handle, const void *completion_key)
{
	ULONG_PTR comp_key = reinterpret_cast < ULONG_PTR >( (void*)completion_key);

	return 0 != ::CreateIoCompletionPort (handle,
		this->m_completion_port_,
		comp_key,
		this->m_number_of_threads_);
}

_jingxian_end
