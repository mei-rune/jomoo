

#ifndef JOMOO_THREAD_H
#define JOMOO_THREAD_H


#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"
#include <process.h>
#include "thread_closure.h"

#ifdef JOMOO_MT

_thread_begin
	
typename uintptr_t thread_t;

//{
//public:
//	class thread_data
//	{
//	public:
//		tstring to_string;
//		uintptr_t pthread;
//	};
//	
//	/**
//	 * 等待线程结束
//	 * @remarks 注意不论该函数是否成功，本线程都一定结束，当然
//	 * 除非有人重新启动它了。
//	 */
//	void join ();
//
//	/**
//	 * 取得线程描述
//	 * @return 返回线程描述
//	 */
//	const tstring& toString() const;
//private:
//	thread_data* thread;
//};

namespace ThreadOP
{
	inline void yield()
	{
		::Sleep( 0 );
	}

	inline void sleep(int millis, int nanaos = 0)
	{
		::Sleep( millis );
	}

	template<typename F>
	inline thread_t create_thread( const F& f)
	{
		

	}
}

#if defined (JOMOO_INLINE_FUNCTIONS)
#include "thread.inl"
#endif //

_thread_end

#endif // JOMOO_MT

#endif /* JOMOO_THREAD_H */
