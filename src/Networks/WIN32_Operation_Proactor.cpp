
# include "WIN32OperationProactor.h"
# include "WIN32OperationOverlapped.h"
# include "Base/exception.hpp"
# include <iostream>

#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin

WIN32_Operation_Proactor::WIN32_Operation_Proactor(  )
: m_completion_port_( NULL )
{
	//for( int i = 0; i < 100; i ++ )
	//{
	//	queue_.push( WIN32_Defer( 0, !result_delete_, this, HAZEL_INVALID_HANDLE_VALUE , 0 );
	//}
}

WIN32_Operation_Proactor::WIN32_Operation_Proactor( u_long milli_seconds)
: m_completion_port_( NULL )
{
	open( milli_seconds );
	//	ThrowException1( RuntimeException , BT_TEXT("创建完成端口失败") );
}

WIN32_Operation_Proactor::~WIN32_Operation_Proactor(void)
{
}

int WIN32_Operation_Proactor::open ( size_t number_of_threads )
{
	if( m_completion_port_ != NULL )
		ThrowException1( RuntimeException , BT_TEXT("已经初始化过了!") );

	m_number_of_threads_ = number_of_threads;
	m_completion_port_ = ::CreateIoCompletionPort (INVALID_HANDLE_VALUE,
		0,
		0,
		m_number_of_threads_);

	if ( is_null(m_completion_port_) )
		ThrowException1( RuntimeException , lastError() );
	
	return 0;
}

void WIN32_Operation_Proactor::close (void)
{
	if (is_null(m_completion_port_ ))
		return ;

	for (;;)
	{
		Hazel_OVERLAPPED *overlapped = 0;
		u_long bytes_transferred = 0;
#if defined (Hazel_WIN64)
		ULONG_PTR completion_key = 0;
#else
		ULONG completion_key = 0;
#endif /* Hazel_WIN64 */

		BOOL res = ::GetQueuedCompletionStatus
			(m_completion_port_,
			&bytes_transferred,
			&completion_key,
			&overlapped,
			0);  // poll

		if ( is_null(overlapped) || res == FALSE)
			break;

		WIN32_Operation_Result *asynch_result =
			(WIN32_Operation_Result *) overlapped;

		asynch_result->release();
	}

	::CloseHandle( m_completion_port_);
	m_completion_port_ = NULL;

}

int WIN32_Operation_Proactor::handle_events (unsigned long milli_seconds)
{
	Hazel_OVERLAPPED *overlapped = 0;
	u_long bytes_transferred = 0;

	ULONG_PTR completion_key = 0;

	BOOL result = ::GetQueuedCompletionStatus (m_completion_port_,
		&bytes_transferred,
		&completion_key,
		&overlapped,
		milli_seconds);
	if (result == FALSE && is_null(overlapped) )
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
		WIN32_Operation_Result *asynch_result = (WIN32_Operation_Result *) overlapped;
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

void WIN32_Operation_Proactor::application_specific_code (WIN32_Operation_Result *asynch_result,
														  size_t bytes_transferred,
														  const void *completion_key,
														  u_long error)
{
	try
	{
		asynch_result->complete (bytes_transferred,
			error == 0 ? 0 : 1,
			(void *) completion_key,
			error );
	}
	catch( std::exception& e )
	{
		std::cout << "error :" << e.what() << std::endl;
	}
	catch( ... )
	{	
		std::cout << "unkown error!" << std::endl;
	}
	asynch_result->release();
}

int WIN32_Operation_Proactor::post_completion (WIN32_Operation_Result *result )
{
	if( is_null( result ) )
		ThrowException1( IllegalArgumentException, "result" );
		

	WIN32_Operation_Result* res = result;
	if( is_null( res ) )
		ThrowException( CastException );

	DWORD bytes_transferred = 0;
	ULONG_PTR comp_key = 0;

	if (::PostQueuedCompletionStatus (m_completion_port_, // completion port
		static_cast< DWORD >( bytes_transferred ) ,      // xfer count
		comp_key,               // completion key
		res                  // overlapped
		) == FALSE)
	{
		ThrowException1( RuntimeException, lastError() );
	}

	return 0;
}

int WIN32_Operation_Proactor::post_completion ( Hazel_Operation_Result_Ptr result)
{
	//std::auto_ptr< WIN32_Defer > defer( createDefer( result ) );
	//if( defer.get() == 0 )
	//	return -1;
	//if( post_completion( defer.get() ) != 0 )
		return -1;
	//defer.release();
	//return 0;
}

//WIN32_Defer* WIN32_Operation_Proactor::createDefer( Hazel_Operation_Result_Ptr result )
//{
//	//WIN32_Defer* p = queue_.pop();
//	//if( p != 0 )
//	//	return p;
//	//return ( new WIN32_Defer( result ,!result_delete_, *this , HAZEL_INVALID_HANDLE_VALUE , 0  ) );
//	return 0;
//}

Hazel_HANDLE WIN32_Operation_Proactor::get_handle()
{
	return m_completion_port_;
}

int WIN32_Operation_Proactor::register_handle (Hazel_HANDLE handle,
											   const void *completion_key)
{
	ULONG_PTR comp_key = reinterpret_cast < ULONG_PTR >( (void*)completion_key);

	Hazel_HANDLE cp = ::CreateIoCompletionPort (handle,
		this->m_completion_port_,
		comp_key,
		this->m_number_of_threads_);
	if (0 == cp )
	{
		ThrowException1( RuntimeException, lastError() );
	}
	return 0;
}

_networks_end