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
     * ��װһ�� Win32 ����
	 * @param[ in ] name Win32 ���������
	 * @param[ in ] display Win32 �����������Ϣ
	 * @param[ in ] executable Win32 �����ִ�г�������
	 * @param[ in ] args Win32 ����Ĳ���
	 * @return �ɹ�����0,���򷵻ط�0
     */
	int installService( const std::string& name, const std::string& display, 
		const std::string& executable,const std::vector<std::string>& args);

    /**
     * ж��һ�� Win32 ����
	 * @param[ in ] name Win32 ���������
	 * @return �ɹ�����0,���򷵻ط�0
	 */
    int uninstallService(const std::string& name );

    /**
     * ����һ�� Win32 ����
	 * @param[ in ] name Win32 ���������
	 * @param[ in ] args Win32 ����Ĳ���
	 * @return �ɹ�����0,���򷵻ط�0
     */
	int startService(const std::string& name, const std::vector<std::string>& args);

    /**
     * ֹͣһ�� Win32 ����
	 * @param[ in ] name Win32 ���������
	 * @return �ɹ�����0,���򷵻ط�0
     */
    int stopService(const std::string& name);

private:

	bool waitForServiceState(SC_HANDLE hService, DWORD pendingState, SERVICE_STATUS& status);

	void showServiceStatus(const std::string& msg, SERVICE_STATUS& status);

	logging::log_ptr logger_;
};

_jomoo_end

#endif // SERVICEMANAGER_H