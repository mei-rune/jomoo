

#ifndef thread_manager_H
#define thread_manager_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include "config_threading.h"

#ifdef JOMOO_MT

#include <set>
#include "thread.h"
#include "thread_mutex.h"

_thread_begin

class thread_manager
{
public:

	typedef void ( *function_type )( void * );

	typedef std::set< thread_t > container_type;

	thread_manager( const tchar* descr );

	~thread_manager();

	/**
	 * ����һ���߳�
	 * @param[ in ] runfn �̻߳ص��ӿ�
	 * @param[ in ] descr ���̵߳�����
	 * @return �ɹ������̶߳��󣬷��򷵻�0
	 * @remarks ע�ⲻҪ��ͼɾ��������Ϊ�������ڱ��߳�������
	 */
	thread_t create_thread( function_type runfn , const tchar* descr = 0 );

	/**
	 * ����һ���߳�
	 * @param[ in ] thrd �̶߳���
	 * @remarks ע�⣬���̶߳�����ӵ����߳���󣬲�Ҫ��ͼɾ
	 * ��������Ϊ�ڱ��߳����ع�ʱ���Զ�ɾ���������Ȿ�������ܻ��ӳ��쳣��
	 */
	void add_thread( thread_t thrd );

	/**
	 * ɾ��һ���߳�
	 * @param[ in ] thrd �̶߳���
	 * @remarks ע�⣬���������ܻ��ӳ��쳣��
	 */
	void remove_thread( thread_t thrd);

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
	DECLARE_NO_COPY_CLASS( thread_manager );

	mutable thread_mutex m_mutex_;
	container_type m_thread_group_;
	tstring m_descr_;
	mutable tstring m_to_string_;
};


#ifdef OS_HAS_INLINED
#include "thread_manager.inl"
#endif //

_thread_end


#endif // JOMOO_MT

#endif // thread_manager_H