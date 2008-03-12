

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
 * @Brief thread �߳̽ӿڣ����̷߳�װ��ƽ̨�ĸ����߳̽ӿ�
 */
class  thread
{
public:
	/**
	* @Brief �̵߳Ļص��ӿ�
	*/
	class Runnable 
	{ 
	public:

		/**
		* Runnable destructor
		*/
		virtual ~Runnable() { };

		/**
		* �̵߳Ļص��ӿ�
		*/
		virtual void run() = 0;

		/**
		 * �߳��˳�ʱ�Ļص��ӿ�
		 */
		virtual void cleanup() = 0;
	};

	thread ( Runnable& runfn , const tchar* descr );

	~thread();


	/**
	 * ���߳�
	 * @return �����ɹ�������������true,���򷵻�false
	 */
	bool activate ( );

	/**
	 * �ȴ��߳̽���
	 * @remarks ע�ⲻ�۸ú����Ƿ�ɹ������̶߳�һ����������Ȼ
	 * �������������������ˡ�
	 */
	void join ();

	/**
	 * ȡ���߳�����
	 * @return �����߳�����
	 */
	const tstring& toString() const;

	void __do_run();

	void __do_cleanup();

private:
	DECLARE_NO_COPY_CLASS( thread );

	/**
	 * �̵߳�ϵͳ�ص�����
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
	 * ȡ�ñ��ߵ��̶߳���
	 * �ɹ������̶߳���ʧ�ܷ���0;
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
