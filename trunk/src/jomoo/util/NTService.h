
#ifndef _NTSERVICE_H_
#define _NTSERVICE_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Util.h"
#include <winsvc.h>
#include <vector>
#include "jomoo/logging/logger.h"

_jomoo_begin

#define SERVICE_CONTROL_USER 128

//class IService
//{
//public:
//	
//	/**
//	 * ��������
//	 */
//	virtual void run() = 0;
//
//	/**
//	 * ��ʼ��,������run֮ǰ���á�
//	 * @param[ in ] dwArgc ���������С
//	 * @param[ in ] lpszArgv ��������
//	 * @return �ɹ�����true, ʧ�ܷ���false
//	 * @remarks ע�⣬�����Է����쳣�������ָ���˳����룬����SetLastError
//	 * ����SetLastErrorEx ����Ϊ�����߻���GetLastErrorȡ���˳����롣
//	 */
//	virtual bool OnInit( DWORD dwArgc, LPTSTR* lpszArgv ) = 0;
//
//	/**
//	 * ���յ�һ������ֹͣ��֪ͨ
//	 * @remarks ע�⣬�����Է����쳣��
//	 */
//    virtual void OnStop() = 0;
//
//	/**
//	 * ���յ�һ��ѯ�ʷ���״̬��֪ͨ
//	 * @remarks ע�⣬�����Է����쳣��
//	 */
//    virtual void OnInterrogate() = 0;
//
//	/**
//	 * ���յ�һ��������ͣ��֪ͨ
//	 * @remarks ע�⣬�����Է����쳣��
//	 */
//    virtual void OnPause() = 0;
//
//	/**
//	 * ���յ�һ������ָ���֪ͨ
//	 * @remarks ע�⣬�����Է����쳣��
//	 */
//    virtual void OnContinue() = 0;
//	
//	/**
//	 * ���յ�һ��ϵͳ���رյ�֪ͨ
//	 * @remarks ע�⣬�����Է����쳣��
//	 */
//    virtual void OnShutdown() = 0;
//
//	/**
//	 * ���յ�һ���µ�����������󶨵�֪ͨ
//	 * @remarks ע�⣬�����Է����쳣��
//	 */
//    virtual void OnNetBindAdd() = 0;
//	
//	/**
//	 * ���յ�һ����������󶨱����õ�֪ͨ
//	 * @remarks ע�⣬�����Է����쳣��
//	 */
//    virtual void OnNetBindEnable() = 0;
//
//	/**
//	 * ���յ�һ����������󶨱����õ�֪ͨ
//	 * @remarks ע�⣬�����Է����쳣��
//	 */
//    virtual void OnNetBindDisable() = 0;
//
//	/**
//	 * ���յ�һ����������󶨱�ɾ����֪ͨ
//	 * @remarks ע�⣬�����Է����쳣��
//	 */
//    virtual void OnNetBindRemove() = 0;
//	
//	/**
//	 * ���յ�һ��ɾ����֪ͨ
//	 * @remarks ע�⣬�����Է����쳣��
//	 */
//    virtual void OnParamChange() = 0;
//
//	/**
//	 * ���յ�һ���û������֪ͨ
//	 * @param dwOpcode �û������֪ͨ
//	 * @remarks ע�⣬�����Է����쳣��
//	 */
//    virtual void OnUserControl(DWORD dwOpcode) = 0;
//};
template<SERVER>
class CNTService
{
public:
	CNTService(const std::string& name ,SERVER* svr, logging::log_ptr ptr )
		: _name( name )
		, _svr( svr )
		, _logger( ptr )
		, _majorVersion( 1 )
		, _minorVersion( 0 )
		, _serviceStatus( NULL )
		, _isRunning( false )
	{
	if( _pThis != 0 )
		throw std::runtime_error( _T( "����ʵ��ֻ����һ��") );

	if( _name.empty() )
		throw std::runtime_error( _T( "����������Ϊ��") );

	if( _svr == 0 )
		throw std::runtime_error( _T( "����ص����ܿ�") );

    _pThis = this;
    
    _status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    _status.dwCurrentState = SERVICE_STOPPED;
    _status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    _status.dwWin32ExitCode = 0;
    _status.dwServiceSpecificExitCode = 0;
    _status.dwCheckPoint = 0;
    _status.dwWaitHint = 0;

	
		LOG_TRACE( _logger ,_T("CNTService::CNTService()") );
	}

    ~CNTService()
	{
		LOG_TRACE( _logger ,_T("CNTService::~CNTService()") );
	}

    bool start( DWORD dwArgc, LPTSTR* lpszArgv )
	{
		SERVICE_TABLE_ENTRY st[] = {
			{ (char*)_name.c_str(), ServiceMain},
			{NULL, NULL}
		};

		if ( ::StartServiceCtrlDispatcher(st) )
			LOG_TRACE_RETURN( _logger ,_T("�������� ")<< _name << _T(" �ɹ�!"), true );
		else
			LOG_TRACE_RETURN( _logger ,_T("�������� ")<< _name << _T(" ʧ�� - ") << lastError() << _T("!"), false );
	}

	static void WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
	{
		_pThis->run(dwArgc, lpszArgv);
	}

	static void WINAPI Handler(DWORD dwOpcode)
	{
		_pThis->OnControl(dwOpcode);
	}

private:


	bool initialize( DWORD dwArgc, LPTSTR* lpszArgv )
	{
		LOG_TRACE( _logger ,_T("���� Initialize"));
		if( !set_status(SERVICE_START_PENDING) ) return false;

		bool bResult = _svr->OnInit( dwArgc, lpszArgv ); 

		// Set final state
		m_Status.dwWin32ExitCode = GetLastError();
		m_Status.dwCheckPoint = 0;
		m_Status.dwWaitHint = 0;
		if (!bResult)
		{
			LOG_INFO( _logger ,_T("�û���ʼ��ʧ��"));
			SetStatus(SERVICE_STOPPED);
			LOG_TRACE( _logger ,_T("�˳� Initialize"));
			return false;    
		}

		LOG_INFO( _logger ,_T("����������"));

		set_status(SERVICE_RUNNING);

		LOG_TRACE( _logger ,_T("�˳� Initialize"));
		return true;
	}


	bool set_status(DWORD dwState)
	{
		DWORD oldState = m_Status.dwCurrentState;
		m_Status.dwCurrentState = dwState;
		if( ::SetServiceStatus(m_hServiceStatus, &m_Status) )
		{
			LOG_TRACE( _logger , _T( "���ķ����� ")<< _name << _T(" ״̬(") << oldState << _T("," )<< dwState << _T( ")�ɹ�!"));
			return true;
		}
		else
		{
			LOG_TRACE( _logger , _T( "���ķ����� ")<< _name << _T(" ״̬(") << oldState << _T("," )<< dwState << _T( ")ʧ�� - ") << lastError() << _T("!"));
			m_Status.dwCurrentState = oldState;
			return false;
		}
	}

	void run(DWORD dwArgc, LPTSTR* lpszArgv)
	{
		LOG_TRACE( _logger,_T("��ʼ���з��� ")<< _name << _T("."));
		_status.dwCurrentState = SERVICE_START_PENDING;
		_serviceStatus = RegisterServiceCtrlHandler( (char*) _name.c_str(), Handler);
		if ( NULL == _serviceStatus )
		{
			LOG_INFO( _logger, _T( "���� ") << _name << _T(" ע�������ƾ��ʧ��, " ) );
			return;
		}
		
		LOG_TRACE( _logger,_T( "��ʼ������ ")<< _name << _T(".") );
		if (initialize( dwArgc, lpszArgv ))
		{
			_isRunning = true;
			_status.dwWin32ExitCode = 0;
			_status.dwCheckPoint = 0;
			_status.dwWaitHint = 0;

			LOG_TRACE( _logger,_T( "���� ")<< _name << _T(" ������...") );
			_svr->run();
			// ֪ͨNT��������������ѹر�
			set_status(SERVICE_STOPPED);
			LOG_TRACE( _logger,_T( "���� ")<< _name << _T(" �˳�.") );
		}
		else
		{
			set_status(SERVICE_STOPPED);
			LOG_TRACE( _logger,_T( "��ʼ������ ")<< _name << _T(" ʧ��.") );
		}
	}

	void OnControl(DWORD dwOpcode)
	{
		LOG_TRACE( _logger,_T("���� ")<< _name << _T(" ���յ���������[")<< dwOpcode << _T("]"));

		switch (dwOpcode) 
		{
		case SERVICE_CONTROL_STOP: // 1
			set_status(SERVICE_STOP_PENDING);
			_svr->OnStop();
			_isRunning = false;
			break;
		case SERVICE_CONTROL_PAUSE: // 2
			_svr->OnPause();
			break;
		case SERVICE_CONTROL_CONTINUE: // 3
			_svr->OnContinue();
			break;
		case SERVICE_CONTROL_INTERROGATE: // 4
			_svr->OnInterrogate();
			break;
		case SERVICE_CONTROL_SHUTDOWN: // 5
			_svr->OnShutdown();
			break;
		case SERVICE_CONTROL_NETBINDADD: // NT ��֧��
			_svr->OnNetBindAdd();
			break;
		case SERVICE_CONTROL_NETBINDENABLE: // NT ��֧��
			_svr->OnNetBindEnable();
			break;
		case SERVICE_CONTROL_NETBINDDISABLE: // NT ��֧��
			_svr->OnNetBindDisable();
			break;
		case SERVICE_CONTROL_NETBINDREMOVE: // NT ��֧��
			_svr->OnNetBindRemove();
			break;
		case SERVICE_CONTROL_PARAMCHANGE: // NT ��֧��
			_svr->OnParamChange();
			break;
		default:
			if (dwOpcode >= SERVICE_CONTROL_USER)
			{
				_svr->OnUserControl(dwOpcode);
			}
			else
			{
				LOG_INFO( _logger,_T( "���� ")<< _name << _T(" ���յ�����ķ���֪ͨ")  );
			}
			break;
		}

		// Report current status
		LOG_TRACE( _logger,_T( "���·��� ")<< _name << _T(" ״̬(") 
			<< _serviceStatus << _T( "," )
			<< _status.dwCurrentState << _T(")"));

		::SetServiceStatus(_serviceStatus, _status);
	}



private:
	std::string _name;
	SERVER* _svr;
	logging::log_ptr _logger;

    int _majorVersion;
    int _minorVersion;
    SERVICE_STATUS_HANDLE _serviceStatus;
    SERVICE_STATUS _status;
    bool _isRunning;
	
    static CNTService<SERVER>* _pThis;

};

template<SERVER>
CNTService<SERVER>* CNTService::_pThis = NULL;

_jomoo_end

#endif // _NTSERVICE_H_
