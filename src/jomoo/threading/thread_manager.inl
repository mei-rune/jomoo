

OS_INLINE thread_manager::thread_manager( const tchar* descr )
: m_descr_( descr == 0 ? "<empty>": descr )
{
}

OS_INLINE thread_manager::~thread_manager()
{

}

OS_INLINE thread_t thread_manager::create_thread( function_type runfn , const tchar* descr )
{
	return 0;
}

OS_INLINE void thread_manager::add_thread( thread_t thrd)
{
	thread_mutex::spcode_lock guard( m_mutex_ , false );
	if( !guard.locked() )
		ThrowException1(  LockException, "添加线程[" + ::toString( thrd ) + "]到[" + m_descr_ + "]失败" );

	m_thread_group_.insert( thrd );
}

OS_INLINE void thread_manager::remove_thread( thread_t thrd)
{
	thread_mutex::spcode_lock guard( m_mutex_ , false );
	if( !guard.locked() )
		 ThrowException1(  LockException, "添加线程[" + ::toString( thrd ) + "]到[" + m_descr_ + "]失败" );

	m_thread_group_.erase( thrd );
}

OS_INLINE void thread_manager::join_all()
{
	thread_mutex::spcode_lock guard( m_mutex_ );
	container_type container( m_thread_group_ );
	guard.unlock();

	for(container_type::iterator it = container.begin()
		; it != container.end(); it ++ )
	{
		//
	}
}

OS_INLINE const tstring& thread_manager::toString() const
{
	return m_descr_;
}
