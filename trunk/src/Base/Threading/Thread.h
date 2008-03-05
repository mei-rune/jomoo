

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
 * @Brief JOMOO_Base_Thread �߳̽ӿڣ����̷߳�װ��ƽ̨�ĸ����߳̽ӿ�
 */
class  JOMOO_Thread
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
	};

	JOMOO_Thread ( Runnable& runfn , const tchar* descr );

	~JOMOO_Thread();

	/**
	 * �ȴ��߳̽���
	 * @remarks ע�ⲻ�۸ú����Ƿ�ɹ������̶߳�һ����������Ȼ
	 * �������������������ˡ�
	 */
	void join (void);

	/**
	 * ȡ���߳�����
	 * @return �����߳�����
	 */
	const tstring& toString() const;

	static void static_thread_svc( void * arg );

private:
	DECLARE_NO_COPY_CLASS( JOMOO_Thread );

	/**
	 * ���߳�
	 * @return �ɹ�����0,ʧ�ܷ���-1���Ѿ���������1
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
	 * ȡ�ñ��ߵ��̶߳���
	 * �ɹ������̶߳���ʧ�ܷ���0;
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
