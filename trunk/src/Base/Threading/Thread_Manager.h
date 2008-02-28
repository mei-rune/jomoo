

#ifndef Hazel_THREAD_MANAGER_H
#define Hazel_THREAD_MANAGER_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef Hazel_MT

#include <set>
#include "synch/synch_traits.h"
#include "Hazel_Thread.h"

_thread_begin

class Hazel_Thread_Manager //: public Hazel_Base_Thread_Manager
{
public:

	typedef std::set< Hazel_Thread* > container_type;

	Hazel_Thread_Manager( const tchar* descr );

	~Hazel_Thread_Manager();

	/**
	 * 创建一个线程
	 * @param[ in ] runfn 线程回调接口
	 * @param[ in ] descr 该线程的描述
	 * @return 成功返回线程对象，否则返回0
	 * @remarks 注意不要试图删除它，因为它是属于本线程组所有
	 */
	Hazel_Thread* create_thread( Hazel_Thread::Runnable& runfn , const tchar* descr = 0 );

	/**
	 * 增加一个线程
	 * @param[ in ] thrd 线程对象
	 * @remarks 注意，将线程对象添加到本线程组后，不要试图删
	 * 除它，因为在本线程组柝构时会自动删除它。此外本函数可能会扔出异常。
	 */
	void add_thread( Hazel_Thread* thrd );

	/**
	 * 删除一个线程
	 * @param[ in ] thrd 线程对象
	 * @remarks 注意，本函数可能会扔出异常。
	 */
	void remove_thread( Hazel_Thread* thrd);

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
	DECLARE_NO_COPY_CLASS( Hazel_Thread_Manager );
	Hazel_MUTEX_MUTABLE( m_mutex_ );
	container_type m_thread_group_;
	tstring m_descr_;
	mutable tstring m_to_string_;
};


#ifdef OS_HAS_INLINED

#include "Hazel_Thread_Manager.inl"

#endif //

_thread_end


#endif // Hazel_MT

#endif // Hazel_THREAD_MANAGER_H