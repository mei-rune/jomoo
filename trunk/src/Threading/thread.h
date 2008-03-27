

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
 * @Brief �̵߳Ļص��ӿ�
 */
class runnable 
{ 
public:

	/**
	* Runnable destructor
	*/
	virtual ~runnable() { };

	/**
	* �̵߳Ļص��ӿ�
	*/
	virtual void run() = 0;
};

/**
 * @Brief thread �߳̽ӿڣ����̷߳�װ��ƽ̨�ĸ����߳̽ӿ�
 */
class  thread
{
public:
	thread ( runnable& runfn , const tchar* descr );

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

	runnable& m_runfn_;

	tstring to_string_;
};



class thread_t
{
public:
	class thread_data
	{
	public:
		tstring to_string
		runnable runner;
		uintptr_t pthread;
	};
	
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
private:
	thread_data* thread;
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

	inline void create_thread( 
}

_thread_end

#endif // JOMOO_MT

#endif /* JOMOO_THREAD_H */
