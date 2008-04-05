#include "windows.h"
#include "servicemanager.h"

_jomoo_begin

ServiceManager::ServiceManager( logging::log_ptr logger )
: logger_( logger )
{
}

int ServiceManager::installService(const tstring& name, const tstring& display, const tstring& executable,
								   const std::vector<tstring>& args)
{
	tstring disp, exec;

    disp = display;
    if(disp.empty())
    {
        disp = name;
    }

    exec = executable;
    if(exec.empty())
    {
        //
        // 使用本执行文件
        //
        tchar buf[_MAX_PATH];
        if(GetModuleFileName(NULL, buf, _MAX_PATH) == 0)
        {
            LOG_ERROR( logger_, _T("没有执行文件名") );
            return -1;
        }
        exec = buf;
    }

    //
    // 如果有空格的话加上引号
    //
	tstring command;
	if(executable.find( _T(' ')) != tstring::npos)
    {
        command.push_back( _T('"'));
        command.append(exec);
        command.push_back( _T('"'));
    }
    else
    {
        command = exec;
    }

	//
	// 拼上选项字符串
	//
	for(std::vector<tstring>::const_iterator p = args.begin(); p != args.end(); ++p)
    {
        command.push_back( _T(' '));

		if(p->find_first_of( _T(" \t\n\r") ) != tstring::npos)
        {
            command.push_back( _T('"'));
            command.append(*p);
            command.push_back( _T('"'));
        }
        else
        {
            command.append(*p);
        }
    }

    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(hSCM == NULL)
    {
        LOG_INFO( logger_, _T("不能打开 SCM") );
        return -1;
    }
    SC_HANDLE hService = CreateService(
        hSCM,
        name.c_str(),
        disp.c_str(),
        SC_MANAGER_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_AUTO_START,
        SERVICE_ERROR_NORMAL,
        command.c_str(),
        NULL,
        NULL,
        NULL,
        NULL,
        NULL);

    if(hService == NULL)
    {
        LOG_INFO( logger_, _T("不能安装服务[") << toTstring(name) << _T( "]") );
        CloseServiceHandle(hSCM);
        return -1;
    }

    CloseServiceHandle(hSCM);
    CloseServiceHandle(hService);

    return 0;
}

int ServiceManager::uninstallService(const tstring& name)
{
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(hSCM == NULL)
    {
        LOG_INFO( logger_, _T("不能打开 SCM") );
        return -1;
    }

    SC_HANDLE hService = OpenService(hSCM, name.c_str(), SC_MANAGER_ALL_ACCESS);
    if(hService == NULL)
    {
        LOG_INFO( logger_, _T("不能打开服务[") << toTstring(name) << _T( "]"));
        CloseServiceHandle(hSCM);
        return -1;
    }

    BOOL b = DeleteService(hService);

    if(!b)
    {
	    LOG_INFO( logger_, _T("不能卸载服务[") << toTstring(name) << _T( "]"));
    }

    CloseServiceHandle(hSCM);
    CloseServiceHandle(hService);

	return ( b?0:-1);
}

int ServiceManager::startService(const tstring& name, const std::vector<tstring>& args)
{
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(hSCM == NULL)
    {
        LOG_INFO( logger_, _T("不能打开 SCM") );
        return -1;
    }

    SC_HANDLE hService = OpenService(hSCM, name.c_str(), SC_MANAGER_ALL_ACCESS);
    if(hService == NULL)
    {
        LOG_INFO( logger_, _T("不能打开服务[") << toTstring(name) << _T( "]"));
        CloseServiceHandle(hSCM);
        return -1;
    }

    //
	// 将字符串拼成 char* []形式
    //
    const size_t argc = args.size();
    const char** argv = new const char*[argc];
    size_t i = 0;
	for(std::vector<tstring>::const_iterator p = args.begin(); p != args.end(); ++p)
    {
		argv[i++] = string_traits<char>::strdup( toNarrowString(*p).c_str());
    }

    //
    // 启动服务
    //
    BOOL b = StartServiceA(hService, ( DWORD )argc, argv);

    //
    // 释放内存
    //
    for(i = 0; i < argc; ++i)
    {
        string_traits<char>::free((char*)(argv[i]));
    }
    delete[] argv;

    if(!b)
    {
		LOG_INFO( logger_, _T("不能启动服务[") << toTstring(name) << _T( "]"));
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCM);
        return -1;
    }

    LOG_TRACE( logger_, _T("服务正在启动中...") );

    //
    // 
    //
    SERVICE_STATUS status;
    if(!waitForServiceState(hService, SERVICE_START_PENDING, status))
    {
		LOG_INFO( logger_, _T("检测服务[") << toTstring(name) << _T( "]状态，发生错误。"));
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCM);
        return -1;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCM);

    if(status.dwCurrentState == SERVICE_RUNNING)
    {
        LOG_TRACE( logger_, _T("服务运行中..."));
    }
    else
    {
	showServiceStatus( _T( "服务器启动发生错误。"), status);
	return -1;
    }

    return 0;
}

int ServiceManager::stopService(const tstring& name)
{
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(hSCM == NULL)
    {
        LOG_INFO( logger_, _T("不能打开 SCM") );
        return -1;
    }

    SC_HANDLE hService = OpenService(hSCM, name.c_str(), SC_MANAGER_ALL_ACCESS);
    if(hService == NULL)
    {
        LOG_INFO( logger_, _T("不能打开服务[") << toTstring(name) << _T( "]"));
        CloseServiceHandle(hSCM);
        return -1;
    }

    SERVICE_STATUS status;
    BOOL b = ControlService(hService, SERVICE_CONTROL_STOP, &status);

    if(!b)
    {
		LOG_INFO( logger_, _T("不能停止服务[") << toTstring(name) << _T( "]"));
        CloseServiceHandle(hSCM);
        CloseServiceHandle(hService);
        return -1;
    }

    LOG_TRACE( logger_, _T("服务停止中..."));

    //
    // 等待服务停止或发生一个错误
    //
    if(!waitForServiceState(hService, SERVICE_STOP_PENDING, status))
    {
        LOG_INFO( logger_, _T("检测服务[") << toTstring(name) << _T( "]状态，发生错误。"));
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCM);
        return -1;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCM);

    if(status.dwCurrentState == SERVICE_STOPPED)
    {
         LOG_TRACE( logger_, _T("服务已停止."));
    }
    else
    {
	showServiceStatus( _T( "服务器停止发生错误。"), status);
	return -1;
    }

    return 0;
}

bool ServiceManager::waitForServiceState(SC_HANDLE hService, DWORD pendingState, SERVICE_STATUS& status)
{
    if(!QueryServiceStatus(hService, &status))
    {
	return false;
    }

    //
    // 保存起始tick计数据和初始checkpoint.
    //
    DWORD startTickCount = GetTickCount();
    DWORD oldCheckPoint = status.dwCheckPoint;

    //
    // 轮询服务状态
    //
    while(status.dwCurrentState == pendingState)
    {
        //
        // 计算等待时间( 1秒 到 10秒)
        //

        DWORD waitTime = status.dwWaitHint / 10;

        if(waitTime < 1000)
        {
            waitTime = 1000;
        }
        else if(waitTime > 10000)
        {
            waitTime = 10000;
        }

        Sleep(waitTime);

        //
        // 再检测服务状态
        //
        if(!QueryServiceStatus(hService, &status))
        {
            return false;
        }

        if(status.dwCheckPoint > oldCheckPoint)
        {
            //
            // 服务前进一步了
            //
            startTickCount = GetTickCount();
            oldCheckPoint = status.dwCheckPoint;
        }
        else
        {
            if(GetTickCount() - startTickCount > status.dwWaitHint)
            {
                //
                // 超过等待进间
                //
                break;
            }
        }
    }

    return true;
}

void ServiceManager::showServiceStatus(const tstring& msg, SERVICE_STATUS& status)
{
	tstring state;
    switch(status.dwCurrentState)
    {
    case SERVICE_STOPPED:
	state = _T( "已停止");
	break;
    case SERVICE_START_PENDING:
	state = _T( "启动中");
	break;
    case SERVICE_STOP_PENDING:
	state = _T( "停止中");
	break;
    case SERVICE_RUNNING:
	state = _T( "运行中");
	break;
    case SERVICE_CONTINUE_PENDING:
	state = _T( "恢复中");
	break;
    case SERVICE_PAUSE_PENDING:
	state = _T( "暂停中");
	break;
    case SERVICE_PAUSED:
	state = _T( "已暂停");
	break;
    default:
	state = _T("未知");
	break;
    }

   
   LOG_TRACE( logger_, msg << _T( ",")
	 << _T("  当前状态: " ) << state << _T( ",")
	 << _T("  退出代码: " ) << status.dwWin32ExitCode << _T( ",")
	 << _T("  服务退出代码: " ) << status.dwServiceSpecificExitCode << _T( ",")
	 << _T("  检测点: " ) << status.dwCheckPoint << _T( ",")
	 << _T("  等待次数据: " ) << status.dwWaitHint );
}

_jomoo_end