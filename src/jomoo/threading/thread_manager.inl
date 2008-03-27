

OS_INLINE JOMOO_Thread_Manager::JOMOO_Thread_Manager( const tchar* descr )
: m_descr_( descr == 0 ? "<empty>": descr )
{
}

OS_INLINE JOMOO_Thread_Manager::~JOMOO_Thread_Manager()
{
	JOMOO_GUARD( guard, m_mutex_ );
	for( container_type::iterator it = m_thread_group_.begin()
		; it != m_thread_group_.end()
		; it ++ )
		delete (*it);
	m_thread_group_.clear();
}

OS_INLINE JOMOO_Thread* JOMOO_Thread_Manager::create_thread( JOMOO_Thread::Runnable& runfn , const tchar* descr )
{
	//std::auto_ptr< JOMOO_Thread > ptr ( JOMOO_Thread_Facetory::get()->createThread( runfn ,descr) );
	std::auto_ptr< JOMOO_Thread > ptr ( new JOMOO_Thread( runfn ,descr) );
	add_thread( ptr.get() );
    return ptr.release();
}

OS_INLINE void JOMOO_Thread_Manager::add_thread( JOMOO_Thread* thrd)
{
	JOMOO_GUARD_THROW( guard, m_mutex_ , 
		 "添加线程[" + thrd->toString() + "]到[" + m_descr_ + "]失败" );
	m_thread_group_.insert( thrd );
}

OS_INLINE void JOMOO_Thread_Manager::remove_thread( JOMOO_Thread* thrd)
{
	JOMOO_GUARD_THROW( guard, m_mutex_ , 
		"添加线程[" + thrd->toString() + "]到[" + m_descr_ + "]失败" );
	m_thread_group_.erase( thrd );
}

OS_INLINE void JOMOO_Thread_Manager::join_all()
{
	JOMOO_GUARD( guard, m_mutex_ );
	for( container_type::iterator it = m_thread_group_.begin()
		; it != m_thread_group_.end()
		; it ++ )
			( *it )->join();
}

OS_INLINE const tstring& JOMOO_Thread_Manager::toString() const
{
	return m_descr_;
}
