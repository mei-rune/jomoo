#include "servicemanager.h"

ServiceManager::ServiceManager(void)
{
}

ServiceManager::~ServiceManager(void)
{
}

int ServiceManager::installService(const string& name, const string& display, const string& executable,
                             const vector<string>& args)
{
    string disp, exec;

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
        char buf[_MAX_PATH];
        if(GetModuleFileName(NULL, buf, _MAX_PATH) == 0)
        {
            error("没有执行文件名");
            return -1;
        }
        exec = buf;
    }

    //
    // 如果有空格的话加上引号
    //
    string command;
    if(executable.find(' ') != string::npos)
    {
        command.push_back('"');
        command.append(exec);
        command.push_back('"');
    }
    else
    {
        command = exec;
    }

	//
	// 拼上选项字符串
	//
    for(vector<string>::const_iterator p = args.begin(); p != args.end(); ++p)
    {
        command.push_back(' ');

        if(p->find_first_of(" \t\n\r") != string::npos)
        {
            command.push_back('"');
            command.append(*p);
            command.push_back('"');
        }
        else
        {
            command.append(*p);
        }
    }

    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(hSCM == NULL)
    {
        syserror("不能打开 SCM");
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
        syserror("不能安装服务[" + name + "]");
        CloseServiceHandle(hSCM);
        return -1;
    }

    CloseServiceHandle(hSCM);
    CloseServiceHandle(hService);

    return 0;
}

int ServiceManager::uninstallService(const string& name)
{
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(hSCM == NULL)
    {
        syserror("不能打开 SCM");
        return -1;
    }

    SC_HANDLE hService = OpenService(hSCM, name.c_str(), SC_MANAGER_ALL_ACCESS);
    if(hService == NULL)
    {
        syserror("不能打开服务[" + name + "]");
        CloseServiceHandle(hSCM);
        return -1;
    }

    BOOL b = DeleteService(hService);

    if(!b)
    {
        syserror("不能卸载服务[" + name + "]");
    }

    CloseServiceHandle(hSCM);
    CloseServiceHandle(hService);

	return ( b?0:-1);
}

int ServiceManager::startService(const string& name, const vector<string>& args)
{
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(hSCM == NULL)
    {
        syserror("不能打开 SCM");
        return -1;
    }

    SC_HANDLE hService = OpenService(hSCM, name.c_str(), SC_MANAGER_ALL_ACCESS);
    if(hService == NULL)
    {
        syserror("不能打开服务[" + name + "]");
        CloseServiceHandle(hSCM);
        return -1;
    }

    //
	// 将字符串拼成 char* []形式
    //
    const int argc = args.size();
    LPCSTR* argv = new LPCSTR[argc];
    int i = 0;
    for(vector<string>::const_iterator p = args.begin(); p != args.end(); ++p)
    {
        argv[i++] = strdup(p->c_str());
    }

    //
    // 启动服务
    //
    BOOL b = StartService(hService, argc, argv);

    //
    // 释放内存
    //
    for(i = 0; i < argc; ++i)
    {
        free(const_cast<char*>(argv[i]));
    }
    delete[] argv;

    if(!b)
    {
        syserror("不能启动服务[" + name + "]");
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCM);
        return -1;
    }

    trace("服务正在启动中...");

    //
    // 
    //
    SERVICE_STATUS status;
    if(!waitForServiceState(hService, SERVICE_START_PENDING, status))
    {
        syserror("检测服务[" + name + "]状态，发生错误。");
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCM);
        return -1;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCM);

    if(status.dwCurrentState == SERVICE_RUNNING)
    {
        trace("服务运行中...");
    }
    else
    {
	showServiceStatus("服务器启动发生错误。", status);
	return -1;
    }

    return 0;
}

int ServiceManager::stopService(const string& name)
{
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(hSCM == NULL)
    {
        syserror("不能打开 SCM");
        return -1;
    }

    SC_HANDLE hService = OpenService(hSCM, name.c_str(), SC_MANAGER_ALL_ACCESS);
    if(hService == NULL)
    {
       syserror("不能打开服务[" + name + "]");
        CloseServiceHandle(hSCM);
        return -1;
    }

    SERVICE_STATUS status;
    BOOL b = ControlService(hService, SERVICE_CONTROL_STOP, &status);

    if(!b)
    {
        syserror("不能停止服务[" + name + "]");
        CloseServiceHandle(hSCM);
        CloseServiceHandle(hService);
        return -1;
    }

    trace("服务停止中...");

    //
    // 等待服务停止或发生一个错误
    //
    if(!waitForServiceState(hService, SERVICE_STOP_PENDING, status))
    {
        syserror("检测服务[" + name + "]状态，发生错误。");
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCM);
        return -1;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCM);

    if(status.dwCurrentState == SERVICE_STOPPED)
    {
         trace("服务已停止.");
    }
    else
    {
	showServiceStatus("服务器停止发生错误。", status);
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

void ServiceManager::showServiceStatus(const string& msg, SERVICE_STATUS& status)
{
    string state;
    switch(status.dwCurrentState)
    {
    case SERVICE_STOPPED:
	state = "STOPPED";
	break;
    case SERVICE_START_PENDING:
	state = "START PENDING";
	break;
    case SERVICE_STOP_PENDING:
	state = "STOP PENDING";
	break;
    case SERVICE_RUNNING:
	state = "RUNNING";
	break;
    case SERVICE_CONTINUE_PENDING:
	state = "CONTINUE PENDING";
	break;
    case SERVICE_PAUSE_PENDING:
	state = "PAUSE PENDING";
	break;
    case SERVICE_PAUSED:
	state = "PAUSED";
	break;
    default:
	state = "UNKNOWN";
	break;
    }

    ostringstream ostr;
    ostr << msg << endl
	 << "  当前状态: " << state << endl
	 << "  退出代码: " << status.dwWin32ExitCode << endl
	 << "  服务退出代码: " << status.dwServiceSpecificExitCode << endl
	 << "  检测点: " << status.dwCheckPoint << endl
	 << "  等待次数据: " << status.dwWaitHint;
    trace(ostr.str());
}

