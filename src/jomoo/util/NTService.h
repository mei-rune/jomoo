
#ifndef _NTSERVICE_H_
#define _NTSERVICE_H_

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Util.h"
#include <winsvc.h>
#include <vector>
#include "../Logger.h"

_util_begin

#define SERVICE_CONTROL_USER 128

class JOMOO_Service
{
public:
	
	/**
	 * 服务运行
	 */
	virtual void run() = 0;

	/**
	 * 初始化,它将在run之前调用。
	 * @param[ in ] dwArgc 参数数组大小
	 * @param[ in ] lpszArgv 参数数组
	 * @return 成功返回true, 失败返回false
	 * @remarks 注意，不可以发生异常。如果想指定退出代码，请用SetLastError
	 * 或者SetLastErrorEx ，因为调用者会用GetLastError取得退出代码。
	 */
	virtual bool OnInit( DWORD dwArgc, LPTSTR* lpszArgv ) = 0;

	/**
	 * 接收到一个服务将停止的通知
	 * @remarks 注意，不可以发生异常。
	 */
    virtual void OnStop() = 0;

	/**
	 * 接收到一个询问服务状态的通知
	 * @remarks 注意，不可以发生异常。
	 */
    virtual void OnInterrogate() = 0;

	/**
	 * 接收到一个服务暂停的通知
	 * @remarks 注意，不可以发生异常。
	 */
    virtual void OnPause() = 0;

	/**
	 * 接收到一个服务恢复的通知
	 * @remarks 注意，不可以发生异常。
	 */
    virtual void OnContinue() = 0;
	
	/**
	 * 接收到一个系统将关闭的通知
	 * @remarks 注意，不可以发生异常。
	 */
    virtual void OnShutdown() = 0;

	/**
	 * 接收到一个新的网络组件被绑定的通知
	 * @remarks 注意，不可以发生异常。
	 */
    virtual void OnNetBindAdd() = 0;
	
	/**
	 * 接收到一个网络组件绑定被启用的通知
	 * @remarks 注意，不可以发生异常。
	 */
    virtual void OnNetBindEnable() = 0;

	/**
	 * 接收到一个网络组件绑定被禁用的通知
	 * @remarks 注意，不可以发生异常。
	 */
    virtual void OnNetBindDisable() = 0;

	/**
	 * 接收到一个网络组件绑定被删除的通知
	 * @remarks 注意，不可以发生异常。
	 */
    virtual void OnNetBindRemove() = 0;
	
	/**
	 * 接收到一个删除的通知
	 * @remarks 注意，不可以发生异常。
	 */
    virtual void OnParamChange() = 0;

	/**
	 * 接收到一个用户定义的通知
	 * @param dwOpcode 用户定义的通知
	 * @remarks 注意，不可以发生异常。
	 */
    virtual void OnUserControl(DWORD dwOpcode) = 0;
};

class CNTService
{
public:
    CNTService(const tchar* szServiceName ,JOMOO_Service* svr, UtilLoggerPtr ptr );
    virtual ~CNTService();
    bool StartService( DWORD dwArgc, LPTSTR* lpszArgv );
    void SetStatus(DWORD dwState);
    bool Initialize( DWORD dwArgc, LPTSTR* lpszArgv );
    
    static void WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
    static void WINAPI Handler(DWORD dwOpcode);

	std::vector< tchar > m_szServiceName;
    int m_iMajorVersion;
    int m_iMinorVersion;
    SERVICE_STATUS_HANDLE m_hServiceStatus;
    SERVICE_STATUS m_Status;
    bool m_bIsRunning;
private:

	UtilLoggerPtr logger_;
    static CNTService* m_pThis;
	JOMOO_Service* m_svr_;
};

_util_end

#endif // _NTSERVICE_H_
