
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
//	 * 服务运行
//	 */
//	virtual void run() = 0;
//
//	/**
//	 * 初始化,它将在run之前调用。
//	 * @param[ in ] dwArgc 参数数组大小
//	 * @param[ in ] lpszArgv 参数数组
//	 * @return 成功返回true, 失败返回false
//	 * @remarks 注意，不可以发生异常。如果想指定退出代码，请用SetLastError
//	 * 或者SetLastErrorEx ，因为调用者会用GetLastError取得退出代码。
//	 */
//	virtual bool OnInit( DWORD dwArgc, LPTSTR* lpszArgv ) = 0;
//
//	/**
//	 * 接收到一个服务将停止的通知
//	 * @remarks 注意，不可以发生异常。
//	 */
//    virtual void OnStop() = 0;
//
//	/**
//	 * 接收到一个询问服务状态的通知
//	 * @remarks 注意，不可以发生异常。
//	 */
//    virtual void OnInterrogate() = 0;
//
//	/**
//	 * 接收到一个服务暂停的通知
//	 * @remarks 注意，不可以发生异常。
//	 */
//    virtual void OnPause() = 0;
//
//	/**
//	 * 接收到一个服务恢复的通知
//	 * @remarks 注意，不可以发生异常。
//	 */
//    virtual void OnContinue() = 0;
//	
//	/**
//	 * 接收到一个系统将关闭的通知
//	 * @remarks 注意，不可以发生异常。
//	 */
//    virtual void OnShutdown() = 0;
//
//	/**
//	 * 接收到一个新的网络组件被绑定的通知
//	 * @remarks 注意，不可以发生异常。
//	 */
//    virtual void OnNetBindAdd() = 0;
//	
//	/**
//	 * 接收到一个网络组件绑定被启用的通知
//	 * @remarks 注意，不可以发生异常。
//	 */
//    virtual void OnNetBindEnable() = 0;
//
//	/**
//	 * 接收到一个网络组件绑定被禁用的通知
//	 * @remarks 注意，不可以发生异常。
//	 */
//    virtual void OnNetBindDisable() = 0;
//
//	/**
//	 * 接收到一个网络组件绑定被删除的通知
//	 * @remarks 注意，不可以发生异常。
//	 */
//    virtual void OnNetBindRemove() = 0;
//	
//	/**
//	 * 接收到一个删除的通知
//	 * @remarks 注意，不可以发生异常。
//	 */
//    virtual void OnParamChange() = 0;
//
//	/**
//	 * 接收到一个用户定义的通知
//	 * @param dwOpcode 用户定义的通知
//	 * @remarks 注意，不可以发生异常。
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
		throw std::runtime_error( _T( "服务实例只能有一个") );

	if( _name.empty() )
		throw std::runtime_error( _T( "服务名不能为空") );

	if( _svr == 0 )
		throw std::runtime_error( _T( "服务回调不能空") );

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
			LOG_TRACE_RETURN( _logger ,_T("启动服务 ")<< _name << _T(" 成功!"), true );
		else
			LOG_TRACE_RETURN( _logger ,_T("启动服务 ")<< _name << _T(" 失败 - ") << lastError() << _T("!"), false );
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
		LOG_TRACE( _logger ,_T("进入 Initialize"));
		if( !set_status(SERVICE_START_PENDING) ) return false;

		bool bResult = _svr->OnInit( dwArgc, lpszArgv ); 

		// Set final state
		m_Status.dwWin32ExitCode = GetLastError();
		m_Status.dwCheckPoint = 0;
		m_Status.dwWaitHint = 0;
		if (!bResult)
		{
			LOG_INFO( _logger ,_T("用户初始化失败"));
			SetStatus(SERVICE_STOPPED);
			LOG_TRACE( _logger ,_T("退出 Initialize"));
			return false;    
		}

		LOG_INFO( _logger ,_T("服务器启动"));

		set_status(SERVICE_RUNNING);

		LOG_TRACE( _logger ,_T("退出 Initialize"));
		return true;
	}


	bool set_status(DWORD dwState)
	{
		DWORD oldState = m_Status.dwCurrentState;
		m_Status.dwCurrentState = dwState;
		if( ::SetServiceStatus(m_hServiceStatus, &m_Status) )
		{
			LOG_TRACE( _logger , _T( "更改服务器 ")<< _name << _T(" 状态(") << oldState << _T("," )<< dwState << _T( ")成功!"));
			return true;
		}
		else
		{
			LOG_TRACE( _logger , _T( "更改服务器 ")<< _name << _T(" 状态(") << oldState << _T("," )<< dwState << _T( ")失败 - ") << lastError() << _T("!"));
			m_Status.dwCurrentState = oldState;
			return false;
		}
	}

	void run(DWORD dwArgc, LPTSTR* lpszArgv)
	{
		LOG_TRACE( _logger,_T("开始运行服务 ")<< _name << _T("."));
		_status.dwCurrentState = SERVICE_START_PENDING;
		_serviceStatus = RegisterServiceCtrlHandler( (char*) _name.c_str(), Handler);
		if ( NULL == _serviceStatus )
		{
			LOG_INFO( _logger, _T( "服务 ") << _name << _T(" 注册服务控制句柄失败, " ) );
			return;
		}
		
		LOG_TRACE( _logger,_T( "初始化服务 ")<< _name << _T(".") );
		if (initialize( dwArgc, lpszArgv ))
		{
			_isRunning = true;
			_status.dwWin32ExitCode = 0;
			_status.dwCheckPoint = 0;
			_status.dwWaitHint = 0;

			LOG_TRACE( _logger,_T( "服务 ")<< _name << _T(" 运行中...") );
			_svr->run();
			// 通知NT服务管理器自已已关闭
			set_status(SERVICE_STOPPED);
			LOG_TRACE( _logger,_T( "服务 ")<< _name << _T(" 退出.") );
		}
		else
		{
			set_status(SERVICE_STOPPED);
			LOG_TRACE( _logger,_T( "初始化服务 ")<< _name << _T(" 失败.") );
		}
	}

	void OnControl(DWORD dwOpcode)
	{
		LOG_TRACE( _logger,_T("服务 ")<< _name << _T(" 接收到操作代码[")<< dwOpcode << _T("]"));

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
		case SERVICE_CONTROL_NETBINDADD: // NT 不支持
			_svr->OnNetBindAdd();
			break;
		case SERVICE_CONTROL_NETBINDENABLE: // NT 不支持
			_svr->OnNetBindEnable();
			break;
		case SERVICE_CONTROL_NETBINDDISABLE: // NT 不支持
			_svr->OnNetBindDisable();
			break;
		case SERVICE_CONTROL_NETBINDREMOVE: // NT 不支持
			_svr->OnNetBindRemove();
			break;
		case SERVICE_CONTROL_PARAMCHANGE: // NT 不支持
			_svr->OnParamChange();
			break;
		default:
			if (dwOpcode >= SERVICE_CONTROL_USER)
			{
				_svr->OnUserControl(dwOpcode);
			}
			else
			{
				LOG_INFO( _logger,_T( "服务 ")<< _name << _T(" 接收到错误的服务通知")  );
			}
			break;
		}

		// Report current status
		LOG_TRACE( _logger,_T( "更新服务 ")<< _name << _T(" 状态(") 
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
