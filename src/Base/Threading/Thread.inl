
extern "C"
{
JOMOO_INLINE unsigned int __stdcall static_thread_svc( void * arg )
{
	thread* thread_ = ( thread* ) arg;
	try{
	thread_->__do_run();
	thread_->__do_cleanup();
	_endthreadex( 0 );
	return 0;
	}
	catch( ... )
	{
	}

	try
	{
	thread_->__do_cleanup();
	}
	catch( ... )
	{}
	_endthreadex( -1 );
	return -1;
}
}


JOMOO_INLINE thread::thread( Runnable& runfn , const tchar* descr)
: m_thread_( 0 )
, m_runfn_( runfn )
, to_string_( descr == 0 ? "< empty >" : descr )
{
	activate();
}

JOMOO_INLINE thread::~thread()
{
	/**
	if( m_thread_ == 0 )
		return ;
	CloseHandle(reinterpret_cast<HANDLE>(m_thread_));
	m_thread_ = 0;
	 */
	join();
}

JOMOO_INLINE void thread::__do_run()
{
	try
	{
		m_runfn_.run();
		to_string_ += "已退出";
	}
	catch( ... )
	{
		to_string_ += "异常中止";
		throw;
	}
}

JOMOO_INLINE void thread::__do_cleanup()
{
	//try
	//{
	//	m_runfn_.cleanup();
	//}
	//catch( ... )
	//{
	//}
}

JOMOO_INLINE bool thread::activate ( )
{
	if ( 0 != m_thread_ )
		return true;

	unsigned id = 0;
    m_thread_ = _beginthreadex(0, 0, &static_thread_svc,
                                           this, 0, &id);
    if (!m_thread_ || - 1 == m_thread_ )
	{
		m_thread_ = 0;
		return false;
	}

	tstring::value_type tmp[1024];
	string_traits<	tstring::value_type>::itoa( id, tmp, 1024, 10 );
	to_string_ += "[";
	to_string_ += tmp; 
	to_string_ += "]";

	return true;
}

JOMOO_INLINE void thread::join ()
{
	if( m_thread_ == 0 )
		return ;
	WaitForSingleObject(reinterpret_cast<HANDLE>(m_thread_), INFINITE);
   CloseHandle(reinterpret_cast<HANDLE>(m_thread_));
   m_thread_ = 0;
}

JOMOO_INLINE const tstring& thread::toString() const
{
	return to_string_;
}
