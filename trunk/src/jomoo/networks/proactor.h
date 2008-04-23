

#ifndef _proactor_h_
#define _proactor_h_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "jomoo/platform/os.h"
#include "io_request.h"

_networks_begin

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
	bool bind(JOMOO_HANDLE handle,const void *completion_key);

	/**
	 * ����һ���Ѿ���ɵ�������ɶ˿�
	 */
	bool post_completion (io_request *result );

	/**
	 * ��ȡ����ɵ��¼�,����������¼�
	 * @return ��ʱ����1,��ȡ���¼����ɹ�������0,��ȡʧ�ܷ���-1
	 */
	int handle_events ( u_long milli_seconds);

	/**
	 * ȡ�ñ��˿ڵľ��
	 */
	JOMOO_HANDLE get_handle();

private:
	void application_specific_code (io_request *asynch_result,
		size_t bytes_transferred,
		const void *completion_key,
		u_long error);

	JOMOO_HANDLE m_completion_port_;
	u_long m_number_of_threads_;
};

_networks_end

#endif // _proactor_h_