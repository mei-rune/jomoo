#pragma once

class ServiceManager
{
public:
    /**
     * 安装一个 Win32 服务
	 * @param[ in ] name Win32 服务的名称
	 * @param[ in ] display Win32 服务的描述信息
	 * @param[ in ] executable Win32 服务的执行程序名称
	 * @param[ in ] args Win32 服务的参数
	 * @return 成功返回0,否则返回非0
     */
    int installService( const string& name, const string& display, const string& executable,
                             const vector<string>& args);

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
    int startService(const string& name, const vector<string>& args)

    /**
     * 停止一个 Win32 服务
	 * @param[ in ] name Win32 服务的名称
	 * @return 成功返回0,否则返回非0
     */
    int stopService(const std::string& name);

    /**
	 * 记录一个系统日志
	 */
    virtual void syserror(const std::string&);

    /**
     * 记录一个错误日志
     */
    virtual void error(const std::string&);

    /**
     * 记录一个警告日志
     */
    virtual void warning(const std::string&);

    /**
     * 记录一个调试日志
     */
    virtual void trace(const std::string&);

    /**
     * 记录一个普通日志
     */
    virtual void print(const std::string&);


private:

	bool waitForServiceState(SC_HANDLE hService, DWORD pendingState, SERVICE_STATUS& status);

	void showServiceStatus(const string& msg, SERVICE_STATUS& status);

};
