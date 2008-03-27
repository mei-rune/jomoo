

#ifndef JOMOO_THREAD_MANAGER_H
#define JOMOO_THREAD_MANAGER_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT

#include <set>
#include "synch/synch_traits.h"
#include "JOMOO_Thread.h"

_thread_begin

class JOMOO_Thread_Manager //: public JOMOO_Base_Thread_Manager
{
public:

	typedef std::set< JOMOO_Thread* > container_type;

	JOMOO_Thread_Manager( const tchar* descr );

	~JOMOO_Thread_Manager();

	/**
	 * 创建一个线程
	 * @param[ in ] runfn 线程回调接口
	 * @param[ in ] descr 该线程的描述
	 * @return 成功返回线程对象，否则返回0
	 * @remarks 注意不要试图删除它，因为它是属于本线程组所有
	 */
	JOMOO_Thread* create_thread( JOMOO_Thread::Runnable& runfn , const tchar* descr = 0 );

	/**
	 * 增加一个线程
	 * @param[ in ] thrd 线程对象
	 * @remarks 注意，将线程对象添加到本线程组后，不要试图删
	 * 除它，因为在本线程组柝构时会自动删除它。此外本函数可能会扔出异常。
	 */
	void add_thread( JOMOO_Thread* thrd );

	/**
	 * 删除一个线程
	 * @param[ in ] thrd 线程对象
	 * @remarks 注意，本函数可能会扔出异常。
	 */
	void remove_thread( JOMOO_Thread* thrd);

	/**
	 * 等待所有线程结束
	 */
	void join_all();

	/**
	 * 取得线程描述
	 * @return 返回线程描述
	 */
	const tstring& toString() const;

private:
	DECLARE_NO_COPY_CLASS( JOMOO_Thread_Manager );
	JOMOO_MUTEX_MUTABLE( m_mutex_ );
	container_type m_thread_group_;
	tstring m_descr_;
	mutable tstring m_to_string_;
};


#ifdef OS_HAS_INLINED

#include "JOMOO_Thread_Manager.inl"

#endif //

_thread_end


#endif // JOMOO_MT

#endif // JOMOO_THREAD_MANAGER_H