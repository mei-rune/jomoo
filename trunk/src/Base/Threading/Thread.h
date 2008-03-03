

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
 * @Brief Hazel_Base_Thread �߳̽ӿڣ����̷߳�װ��ƽ̨�ĸ����߳̽ӿ�
 */
class  Hazel_Thread
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

	Hazel_Thread ( Runnable& runfn , const tchar* descr );

	~Hazel_Thread();

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
	DECLARE_NO_COPY_CLASS( Hazel_Thread );

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
	 * ȡ�ñ��ߵ��̶߳���
	 * �ɹ������̶߳���ʧ�ܷ���0;
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
