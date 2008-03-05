

#ifndef JOMOO_THREAD_MANAGER_H
#define JOMOO_THREAD_MANAGER_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT

#include <set>
#include "synch/synch_traits.h"
#include "JOMOO_Thread.h"

_thread_begin

class JOMOO_Thread_Manager //: public JOMOO_Base_Thread_Manager
{
public:

	typedef std::set< JOMOO_Thread* > container_type;

	JOMOO_Thread_Manager( const tchar* descr );

	~JOMOO_Thread_Manager();

	/**
	 * ����һ���߳�
	 * @param[ in ] runfn �̻߳ص��ӿ�
	 * @param[ in ] descr ���̵߳�����
	 * @return �ɹ������̶߳��󣬷��򷵻�0
	 * @remarks ע�ⲻҪ��ͼɾ��������Ϊ�������ڱ��߳�������
	 */
	JOMOO_Thread* create_thread( JOMOO_Thread::Runnable& runfn , const tchar* descr = 0 );

	/**
	 * ����һ���߳�
	 * @param[ in ] thrd �̶߳���
	 * @remarks ע�⣬���̶߳�����ӵ����߳���󣬲�Ҫ��ͼɾ
	 * ��������Ϊ�ڱ��߳����ع�ʱ���Զ�ɾ���������Ȿ�������ܻ��ӳ��쳣��
	 */
	void add_thread( JOMOO_Thread* thrd );

	/**
	 * ɾ��һ���߳�
	 * @param[ in ] thrd �̶߳���
	 * @remarks ע�⣬���������ܻ��ӳ��쳣��
	 */
	void remove_thread( JOMOO_Thread* thrd);

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
	DECLARE_NO_COPY_CLASS( JOMOO_Thread_Manager );
	JOMOO_MUTEX_MUTABLE( m_mutex_ );
	container_type m_thread_group_;
	tstring m_descr_;
	mutable tstring m_to_string_;
};


#ifdef OS_HAS_INLINED

#include "JOMOO_Thread_Manager.inl"

#endif //

_thread_end


#endif // JOMOO_MT

#endif // JOMOO_THREAD_MANAGER_H