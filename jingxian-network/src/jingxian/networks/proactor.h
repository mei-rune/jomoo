

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
	 * 本端口是否有效
	 */
	bool is_good() const;

	/**
	 * 初始化端口(如果已经初始化返回true)
     * @param[ in ] 并行线程数
	 */
	bool open ( size_t number_of_threads = 1 );

	/**
	 * 关闭本对象
	 */
	void close (void);
	
	/**
	 * 将句柄绑定到本端口
	 */
	bool bind(HANDLE handle,const void *completion_key);

	/**
	 * 发送一个已经完成的请求到完成端口
	 */
	bool post(ICommand *result );

	/**
	 * 获取已完成的事件,并处理这个事件
	 * @return 超时返回1,获取到事件并成功处理返回0,获取失败返回-1
	 */
	int handle_events ( u_long milli_seconds);

	/**
	 * 取得本端口的句柄
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