

#ifndef JOMOO_THREAD_H
#define JOMOO_THREAD_H


#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT


_thread_begin

/**
 * @Brief JOMOO_Base_Thread 线程接口，本线程封装了平台的各种线程接口
 */
class  JOMOO_Thread
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
	};

	JOMOO_Thread ( Runnable& runfn , const tchar* descr );

	~JOMOO_Thread();

	/**
	 * 等待线程结束
	 * @remarks 注意不论该函数是否成功，本线程都一定结束，当然
	 * 除非有人重新启动它了。
	 */
	void join (void);

	/**
	 * 取得线程描述
	 * @return 返回线程描述
	 */
	const tstring& toString() const;

	static void static_thread_svc( void * arg );

private:
	DECLARE_NO_COPY_CLASS( JOMOO_Thread );

	/**
	 * 起动线程
	 * @return 成功返回0,失败返回-1，已经启动返回1
	 */
	int activate ( );

	uintptr_t m_thread_ ;

	Runnable& m_runfn_;

	tstring to_string_;

};


#ifdef OS_HAS_INLINED

#include "JOMOO_Thread.inl"

#endif //

_thread_end

#ifndef JOMOO_HAS_INLINED

//JOMOO_Export_C _thread JOMOO_Thread* ___make_JOMOO_Thread( _thread Runnable& runfn ,const tchar* descr );
JOMOO_Export_C _thread JOMOO_Thread* ___get_JOMOO_Thread( );

#endif // JOMOO_HAS_INLINED

_thread_begin

namespace ThreadOP
{
	/**
	 * 取得本线的线程对象
	 * 成功返回线程对象，失败返回0;
	 */
	inline JOMOO_Thread* get_self()
	{
#ifndef JOMOO_HAS_INLINED
		return ___get_JOMOO_Thread( );
#else 
		return 0;
#endif // JOMOO_HAS_INLINED
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
