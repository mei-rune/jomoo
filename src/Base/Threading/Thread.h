

#ifndef JOMOO_THREAD_H
#define JOMOO_THREAD_H


#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"
#include <process.h>

#ifdef JOMOO_MT

_thread_begin

/**
 * @Brief thread 线程接口，本线程封装了平台的各种线程接口
 */
class  thread
{
public:
	/**
	* @Brief 线程的回调接口
	*/
	class Runnable 
	{ 
	public:

		/**
		* Runnable destructor
		*/
		virtual ~Runnable() { };

		/**
		* 线程的回调接口
		*/
		virtual void run() = 0;

		/**
		 * 线程退出时的回调接口
		 */
		virtual void cleanup() = 0;
	};

	thread ( Runnable& runfn , const tchar* descr );

	~thread();


	/**
	 * 起动线程
	 * @return 启动成功或已启动返回true,否则返回false
	 */
	bool activate ( );

	/**
	 * 等待线程结束
	 * @remarks 注意不论该函数是否成功，本线程都一定结束，当然
	 * 除非有人重新启动它了。
	 */
	void join ();

	/**
	 * 取得线程描述
	 * @return 返回线程描述
	 */
	const tstring& toString() const;

	void __do_run();

	void __do_cleanup();

private:
	DECLARE_NO_COPY_CLASS( thread );

	/**
	 * 线程的系统回调函数
	 */
	//static void static_thread_svc( void * arg );

	uintptr_t m_thread_ ;

	Runnable& m_runfn_;

	tstring to_string_;
};


#if defined (JOMOO_INLINE_FUNCTIONS)

#include "thread.inl"

#endif //

namespace ThreadOP
{
	/**
	 * 取得本线的线程对象
	 * 成功返回线程对象，失败返回0;
	 */
	inline thread* get_self()
	{
		return 0;
	}

	inline void yield()
	{
		::Sleep( 0 );
	}

	inline void sleep(int millis, int nanaos = 0)
	{
		::Sleep( millis );
	}
}

_thread_end

#endif // JOMOO_MT

#endif /* JOMOO_THREAD_H */
