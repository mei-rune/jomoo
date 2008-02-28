#pragma once

class ServiceManager
{
public:
    /**
     * ��װһ�� Win32 ����
	 * @param[ in ] name Win32 ���������
	 * @param[ in ] display Win32 �����������Ϣ
	 * @param[ in ] executable Win32 �����ִ�г�������
	 * @param[ in ] args Win32 ����Ĳ���
	 * @return �ɹ�����0,���򷵻ط�0
     */
    int installService( const string& name, const string& display, const string& executable,
                             const vector<string>& args);

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
    int startService(const string& name, const vector<string>& args)

    /**
     * ֹͣһ�� Win32 ����
	 * @param[ in ] name Win32 ���������
	 * @return �ɹ�����0,���򷵻ط�0
     */
    int stopService(const std::string& name);

    /**
	 * ��¼һ��ϵͳ��־
	 */
    virtual void syserror(const std::string&);

    /**
     * ��¼һ��������־
     */
    virtual void error(const std::string&);

    /**
     * ��¼һ��������־
     */
    virtual void warning(const std::string&);

    /**
     * ��¼һ��������־
     */
    virtual void trace(const std::string&);

    /**
     * ��¼һ����ͨ��־
     */
    virtual void print(const std::string&);


private:

	bool waitForServiceState(SC_HANDLE hService, DWORD pendingState, SERVICE_STATUS& status);

	void showServiceStatus(const string& msg, SERVICE_STATUS& status);

};
