

#ifndef thread_manager_H
#define thread_manager_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT

#include <set>
#include "thread.h"
#include "thread_mutex.h"

_thread_begin

class thread_manager
{
public:

	typedef void ( *function_type )( void * );

	typedef std::set< thread_t > container_type;

	thread_manager( const tchar* descr );

	~thread_manager();

	/**
	 * 创建一个线程
	 * @param[ in ] runfn 线程回调接口
	 * @param[ in ] descr 该线程的描述
	 * @return 成功返回线程对象，否则返回0
	 * @remarks 注意不要试图删除它，因为它是属于本线程组所有
	 */
	thread_t create_thread( function_type runfn , const tchar* descr = 0 );

	/**
	 * 增加一个线程
	 * @param[ in ] thrd 线程对象
	 * @remarks 注意，将线程对象添加到本线程组后，不要试图删
	 * 除它，因为在本线程组柝构时会自动删除它。此外本函数可能会扔出异常。
	 */
	void add_thread( thread_t thrd );

	/**
	 * 删除一个线程
	 * @param[ in ] thrd 线程对象
	 * @remarks 注意，本函数可能会扔出异常。
	 */
	void remove_thread( thread_t thrd);

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
	DECLARE_NO_COPY_CLASS( thread_manager );

	mutable thread_mutex m_mutex_;
	container_type m_thread_group_;
	tstring m_descr_;
	mutable tstring m_to_string_;
};


#ifdef OS_HAS_INLINED
#include "thread_manager.inl"
#endif //

_thread_end


#endif // JOMOO_MT

#endif // thread_manager_H