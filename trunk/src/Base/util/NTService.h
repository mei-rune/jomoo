
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
	 * ��������
	 */
	virtual void run() = 0;

	/**
	 * ��ʼ��,������run֮ǰ���á�
	 * @param[ in ] dwArgc ���������С
	 * @param[ in ] lpszArgv ��������
	 * @return �ɹ�����true, ʧ�ܷ���false
	 * @remarks ע�⣬�����Է����쳣�������ָ���˳����룬����SetLastError
	 * ����SetLastErrorEx ����Ϊ�����߻���GetLastErrorȡ���˳����롣
	 */
	virtual bool OnInit( DWORD dwArgc, LPTSTR* lpszArgv ) = 0;

	/**
	 * ���յ�һ������ֹͣ��֪ͨ
	 * @remarks ע�⣬�����Է����쳣��
	 */
    virtual void OnStop() = 0;

	/**
	 * ���յ�һ��ѯ�ʷ���״̬��֪ͨ
	 * @remarks ע�⣬�����Է����쳣��
	 */
    virtual void OnInterrogate() = 0;

	/**
	 * ���յ�һ��������ͣ��֪ͨ
	 * @remarks ע�⣬�����Է����쳣��
	 */
    virtual void OnPause() = 0;

	/**
	 * ���յ�һ������ָ���֪ͨ
	 * @remarks ע�⣬�����Է����쳣��
	 */
    virtual void OnContinue() = 0;
	
	/**
	 * ���յ�һ��ϵͳ���رյ�֪ͨ
	 * @remarks ע�⣬�����Է����쳣��
	 */
    virtual void OnShutdown() = 0;

	/**
	 * ���յ�һ���µ�����������󶨵�֪ͨ
	 * @remarks ע�⣬�����Է����쳣��
	 */
    virtual void OnNetBindAdd() = 0;
	
	/**
	 * ���յ�һ����������󶨱����õ�֪ͨ
	 * @remarks ע�⣬�����Է����쳣��
	 */
    virtual void OnNetBindEnable() = 0;

	/**
	 * ���յ�һ����������󶨱����õ�֪ͨ
	 * @remarks ע�⣬�����Է����쳣��
	 */
    virtual void OnNetBindDisable() = 0;

	/**
	 * ���յ�һ����������󶨱�ɾ����֪ͨ
	 * @remarks ע�⣬�����Է����쳣��
	 */
    virtual void OnNetBindRemove() = 0;
	
	/**
	 * ���յ�һ��ɾ����֪ͨ
	 * @remarks ע�⣬�����Է����쳣��
	 */
    virtual void OnParamChange() = 0;

	/**
	 * ���յ�һ���û������֪ͨ
	 * @param dwOpcode �û������֪ͨ
	 * @remarks ע�⣬�����Է����쳣��
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
