

#ifndef _proactor_h_
#define _proactor_h_

#include "jingxian/config.h"

#if !defined (JINGXIAN_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JINGXIAN_LACKS_PRAGMA_ONCE */

// Include files
# include "jingxian/networks/commands/ICommand.h"
# include "jingxian/IReactorCore.h"

_jingxian_begin

class proactor
{
public:

	proactor();
	
	proactor( size_t number_of_threads );
	
	~proactor(void);

	/**
	 * ���˿��Ƿ���Ч
	 */
	bool is_good() const;

	/**
	 * ��ʼ���˿�(����Ѿ���ʼ������true)
     * @param[ in ] �����߳���
	 */
	bool open ( size_t number_of_threads = 1 );

	/**
	 * �رձ�����
	 */
	void close (void);
	
	/**
	 * ������󶨵����˿�
	 */
	bool bind(HANDLE handle,const void *completion_key);

	/**
	 * ����һ���Ѿ���ɵ�������ɶ˿�
	 */
	bool post(ICommand *result );

	/**
	 * ��ȡ����ɵ��¼�,����������¼�
	 * @return ��ʱ����1,��ȡ���¼����ɹ�������0,��ȡʧ�ܷ���-1
	 */
	int handle_events ( u_long milli_seconds);

	/**
	 * ȡ�ñ��˿ڵľ��
	 */
	HANDLE handle();

private:
	void application_specific_code (ICommand *asynch_result,
		size_t bytes_transferred,
		const void *completion_key,
		u_long error);

	HANDLE m_completion_port_;
	u_long m_number_of_threads_;
};

_jingxian_end

#endif // _proactor_h_