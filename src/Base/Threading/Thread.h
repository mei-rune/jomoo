

#ifndef Hazel_THREAD_H
#define Hazel_THREAD_H


#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef Hazel_MT


_thread_begin

/**
 * @Brief Hazel_Base_Thread 线程接口，本线程封装了平台的各种线程接口
 */
class  Hazel_Thread
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

	Hazel_Thread ( Runnable& runfn , const tchar* descr );

	~Hazel_Thread();

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
	DECLARE_NO_COPY_CLASS( Hazel_Thread );

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

#include "Hazel_Thread.inl"

#endif //

_thread_end

#ifndef HAZEL_HAS_INLINED

//JOMOO_Export_C _thread Hazel_Thread* ___make_Hazel_Thread( _thread Runnable& runfn ,const tchar* descr );
JOMOO_Export_C _thread Hazel_Thread* ___get_Hazel_Thread( );

#endif // HAZEL_HAS_INLINED

_thread_begin

namespace ThreadOP
{
	/**
	 * 取得本线的线程对象
	 * 成功返回线程对象，失败返回0;
	 */
	inline Hazel_Thread* get_self()
	{
#ifndef HAZEL_HAS_INLINED
		return ___get_Hazel_Thread( );
#else 
		return 0;
#endif // HAZEL_HAS_INLINED
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

#endif // Hazel_MT

#endif /* Hazel_THREAD_H */
