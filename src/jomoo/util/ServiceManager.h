#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Util.h"
#include <string>
#include <vector>
#include "winsvc.h"
#include "jomoo/logging/logger.h"

_jomoo_begin

class ServiceManager
{
public:

	ServiceManager( logging::log_ptr logger = 0 );

    /**
     * 安装一个 Win32 服务
	 * @param[ in ] name Win32 服务的名称
	 * @param[ in ] display Win32 服务的描述信息
	 * @param[ in ] executable Win32 服务的执行程序名称
	 * @param[ in ] args Win32 服务的参数
	 * @return 成功返回0,否则返回非0
     */
	int installService( const std::string& name, const std::string& display, 
		const std::string& executable,const std::vector<std::string>& args);

    /**
     * 卸载一个 Win32 服务
	 * @param[ in ] name Win32 服务的名称
	 * @return 成功返回0,否则返回非0
	 */
    int uninstallService(const std::string& name );

    /**
     * 启动一个 Win32 服务
	 * @param[ in ] name Win32 服务的名称
	 * @param[ in ] args Win32 服务的参数
	 * @return 成功返回0,否则返回非0
     */
	int startService(const std::string& name, const std::vector<std::string>& args);

    /**
     * 停止一个 Win32 服务
	 * @param[ in ] name Win32 服务的名称
	 * @return 成功返回0,否则返回非0
     */
    int stopService(const std::string& name);

private:

	bool waitForServiceState(SC_HANDLE hService, DWORD pendingState, SERVICE_STATUS& status);

	void showServiceStatus(const std::string& msg, SERVICE_STATUS& status);

	logging::log_ptr logger_;
};

_jomoo_end

#endif // SERVICEMANAGER_H