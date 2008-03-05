

JOMOO_HANDLE create_semaphore( long lInitialCount,long lMaxCount,const char* pSemaphoreName)
{
	return ::CreateSemaphore( NULL, lInitialCount,lMaxCount,pSemaphoreName );
}

bool close_semaphore( JOMOO_HANDLE &handle )
{
	return close_handle( handle );
}

bool aquire_semaphore( JOMOO_HANDLE &handle, unsigned long timeout )
{
	return ( WaitForSingleObject( handle,timeout ) !=WAIT_TIMEOUT );
}

bool release_semaphore( JOMOO_HANDLE &handle, long count )
{
	return ( ReleaseSemaphore( handle,count,0) == TRUE );
}

JOMOO_HANDLE create_event(  bool bManualReset,bool bInitialState,const char* lpName )
{
	return CreateEvent( 0,bManualReset,bInitialState,lpName );
}

JOMOO_HANDLE open_event( u_long DesiredAccess,bool bInheritHandle,const char* lpName )
{
	return OpenEvent( DesiredAccess,bInheritHandle,lpName );
}

bool set_event( JOMOO_HANDLE hEvent )
{
	return ( ::SetEvent( hEvent ) == TRUE );

}

bool reset_event( JOMOO_HANDLE hEvent )
{
	return ( ::ResetEvent( hEvent ) == TRUE );
}

bool pulse_event( JOMOO_HANDLE hEvent )
{
	return ( ::PulseEvent( hEvent ) == TRUE );
}

u_long wait_for_singleobjectex(
									   JOMOO_HANDLE hHandle, 
									   u_long timeout,
									   bool bAlertable        // alertable option
									   )
{
	return WaitForSingleObjectEx( hHandle,timeout,bAlertable );
}

u_long wait_for_singleobject(
		JOMOO_HANDLE hHandle,        // handle to object
		u_long timeout   // time-out interval
		)
{
	return WaitForSingleObject( hHandle,timeout );
}

u_long wait_for_multipleobjects(
		const JOMOO_HANDLE* hHandles,
		size_t n,
		bool bWaitAll,            // wait option
		u_long timeout      // time-out interval
		)
{
	return WaitForMultipleObjects( u_long( n ) ,hHandles ,bWaitAll,timeout );
}

u_long wait_for_multipleobjectsex(
		const JOMOO_HANDLE* hHandles,
		size_t n,
		bool bWaitAll,            // wait option
		u_long timeout,      // time-out interval
		bool bAlertable           // alertable option
		)
{
	return WaitForMultipleObjectsEx( u_long( n ) ,hHandles ,bWaitAll,timeout ,bAlertable );
}

#if(_WIN32_WINNT >= 0x0400)

u_long signal_object_and_wait(
		JOMOO_HANDLE hObjectToSignal,  // handle to object to signal
		JOMOO_HANDLE hObjectToWaitOn,  // handle to object to watch
		u_long timeout,      // time-out interval
		bool bAlertable          // alertable option
		)
{
	return SignalObjectAndWait( hObjectToSignal,hObjectToWaitOn,timeout, bAlertable );
}

#endif 

void create_critical_section( critical_section* section )
{
	return InitializeCriticalSection( (  LPCRITICAL_SECTION ) section );  // critical section
}

void close_critical_section( critical_section* section )
{
	return DeleteCriticalSection( ( LPCRITICAL_SECTION ) section );   // critical section
}

void enter_critical_section( critical_section* section )
{
	return EnterCriticalSection( ( LPCRITICAL_SECTION )section );  // critical section
}

void leave_critical_section( critical_section* section )
{
	return LeaveCriticalSection( ( LPCRITICAL_SECTION ) section );   // critical section
}

#if(_WIN32_WINNT >= 0x0400)
bool try_enter_critical_section( critical_section* section )
{
	return ( TryEnterCriticalSection( ( LPCRITICAL_SECTION ) section ) == TRUE );  // critical section
}
#endif

