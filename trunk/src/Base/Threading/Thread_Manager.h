

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
	 * ����һ���߳�
	 * @param[ in ] runfn �̻߳ص��ӿ�
	 * @param[ in ] descr ���̵߳�����
	 * @return �ɹ������̶߳��󣬷��򷵻�0
	 * @remarks ע�ⲻҪ��ͼɾ��������Ϊ�������ڱ��߳�������
	 */
	Hazel_Thread* create_thread( Hazel_Thread::Runnable& runfn , const tchar* descr = 0 );

	/**
	 * ����һ���߳�
	 * @param[ in ] thrd �̶߳���
	 * @remarks ע�⣬���̶߳�����ӵ����߳���󣬲�Ҫ��ͼɾ
	 * ��������Ϊ�ڱ��߳����ع�ʱ���Զ�ɾ���������Ȿ�������ܻ��ӳ��쳣��
	 */
	void add_thread( Hazel_Thread* thrd );

	/**
	 * ɾ��һ���߳�
	 * @param[ in ] thrd �̶߳���
	 * @remarks ע�⣬���������ܻ��ӳ��쳣��
	 */
	void remove_thread( Hazel_Thread* thrd);

	/**
	 * �ȴ������߳̽���
	 */
	void join_all();

	/**
	 * ȡ���߳�����
	 * @return �����߳�����
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