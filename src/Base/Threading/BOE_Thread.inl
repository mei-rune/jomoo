
#ifdef OS_HAS_INLINED

OS_INLINE void BOE_Thread::static_thread_svc( void * arg )
{
	try{
	BOE_Thread* thread_ = ( BOE_Thread* ) arg;
	thread_->m_runfn_.run();
	_endthreadex( 0 );
	return ;
	}
	catch( ... )
	{
	}
	_endthreadex( -1 );
}


#endif // OS_HAS_INLINED


OS_INLINE BOE_Thread::BOE_Thread( _thread Runnable& runfn , const tchar* descr)
: m_runfn_( runfn )
, to_string_( descr == 0 ? "< empty >" : descr )
{
	if( activate() != 0 )
		ThrowException1( RuntimeException ,BT_TEXT("创建线程失败，") + get_c_error() )
}

OS_INLINE BOE_Thread::~BOE_Thread()
{
	join();
}


OS_INLINE int BOE_Thread::activate ( )
{
	//if ( m_thread_ )
	//	return -1;

	unsigned id = 0;
    m_thread_ = _beginthreadex(0, 0, &static_thread_svc,
                                           this, 0, &id);
    if (!m_thread_ || m_thread_ == –1L )
	{
		m_thread_ = 0;
		return -1;
	}
	to_string_ += "[";
	to_string_ += convertIntegerToString( id ); 
	to_string_ += "]";

	return 0;
}

OS_INLINE void BOE_Thread::join (void)
{
	if( m_thread_ == 0 )
		return ;
   WaitForSingleObject(reinterpret_cast<HANDLE>(m_thread_), INFINITE);
   CloseHandle(reinterpret_cast<HANDLE>(m_thread_));
   m_thread_ = 0;
}

OS_INLINE const tstring& BOE_Thread::toString() const
{
	return to_string_;
}
