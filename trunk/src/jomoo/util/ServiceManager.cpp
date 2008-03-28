#include "windows.h"
#include "servicemanager.h"

_jomoo_begin

ServiceManager::ServiceManager( logging::log_ptr logger )
: logger_( logger )
{
}

int ServiceManager::installService(const std::string& name, const std::string& display, const std::string& executable,
								   const std::vector<std::string>& args)
{
	std::string disp, exec;

    disp = display;
    if(disp.empty())
    {
        disp = name;
    }

    exec = executable;
    if(exec.empty())
    {
        //
        // ʹ�ñ�ִ���ļ�
        //
        char buf[_MAX_PATH];
        if(GetModuleFileName(NULL, buf, _MAX_PATH) == 0)
        {
            LOG_ERROR( logger_, BT_TEXT("û��ִ���ļ���") );
            return -1;
        }
        exec = buf;
    }

    //
    // ����пո�Ļ���������
    //
	std::string command;
	if(executable.find(' ') != std::string::npos)
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
	// ƴ��ѡ���ַ���
	//
	for(std::vector<std::string>::const_iterator p = args.begin(); p != args.end(); ++p)
    {
        command.push_back(' ');

		if(p->find_first_of(" \t\n\r") != std::string::npos)
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
        LOG_INFO( logger_, BT_TEXT("���ܴ� SCM") );
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
        LOG_INFO( logger_, BT_TEXT("���ܰ�װ����[") << name << BT_TEXT( "]") );
        CloseServiceHandle(hSCM);
        return -1;
    }

    CloseServiceHandle(hSCM);
    CloseServiceHandle(hService);

    return 0;
}

int ServiceManager::uninstallService(const std::string& name)
{
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(hSCM == NULL)
    {
        LOG_INFO( logger_, BT_TEXT("���ܴ� SCM") );
        return -1;
    }

    SC_HANDLE hService = OpenService(hSCM, name.c_str(), SC_MANAGER_ALL_ACCESS);
    if(hService == NULL)
    {
        LOG_INFO( logger_, BT_TEXT("���ܴ򿪷���[") << name << BT_TEXT( "]"));
        CloseServiceHandle(hSCM);
        return -1;
    }

    BOOL b = DeleteService(hService);

    if(!b)
    {
	    LOG_INFO( logger_, BT_TEXT("����ж�ط���[") << name << BT_TEXT( "]"));
    }

    CloseServiceHandle(hSCM);
    CloseServiceHandle(hService);

	return ( b?0:-1);
}

int ServiceManager::startService(const std::string& name, const std::vector<std::string>& args)
{
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(hSCM == NULL)
    {
        LOG_INFO( logger_, BT_TEXT("���ܴ� SCM") );
        return -1;
    }

    SC_HANDLE hService = OpenService(hSCM, name.c_str(), SC_MANAGER_ALL_ACCESS);
    if(hService == NULL)
    {
        LOG_INFO( logger_, BT_TEXT("���ܴ򿪷���[") << name << BT_TEXT( "]"));
        CloseServiceHandle(hSCM);
        return -1;
    }

    //
	// ���ַ���ƴ�� char* []��ʽ
    //
    const size_t argc = args.size();
    LPCSTR* argv = new LPCSTR[argc];
    size_t i = 0;
	for(std::vector<std::string>::const_iterator p = args.begin(); p != args.end(); ++p)
    {
        argv[i++] = strdup(p->c_str());
    }

    //
    // ��������
    //
    BOOL b = StartService(hService, ( DWORD )argc, argv);

    //
    // �ͷ��ڴ�
    //
    for(i = 0; i < argc; ++i)
    {
        free(const_cast<char*>(argv[i]));
    }
    delete[] argv;

    if(!b)
    {
		LOG_INFO( logger_, BT_TEXT("������������[") << name << BT_TEXT( "]"));
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCM);
        return -1;
    }

    LOG_TRACE( logger_, BT_TEXT("��������������...") );

    //
    // 
    //
    SERVICE_STATUS status;
    if(!waitForServiceState(hService, SERVICE_START_PENDING, status))
    {
		LOG_INFO( logger_, BT_TEXT("������[") << name << BT_TEXT( "]״̬����������"));
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCM);
        return -1;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCM);

    if(status.dwCurrentState == SERVICE_RUNNING)
    {
        LOG_TRACE( logger_, BT_TEXT("����������..."));
    }
    else
    {
	showServiceStatus( BT_TEXT( "������������������"), status);
	return -1;
    }

    return 0;
}

int ServiceManager::stopService(const std::string& name)
{
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(hSCM == NULL)
    {
        LOG_INFO( logger_, BT_TEXT("���ܴ� SCM") );
        return -1;
    }

    SC_HANDLE hService = OpenService(hSCM, name.c_str(), SC_MANAGER_ALL_ACCESS);
    if(hService == NULL)
    {
        LOG_INFO( logger_, BT_TEXT("���ܴ򿪷���[") << name << BT_TEXT( "]"));
        CloseServiceHandle(hSCM);
        return -1;
    }

    SERVICE_STATUS status;
    BOOL b = ControlService(hService, SERVICE_CONTROL_STOP, &status);

    if(!b)
    {
		LOG_INFO( logger_, BT_TEXT("����ֹͣ����[") << name << BT_TEXT( "]"));
        CloseServiceHandle(hSCM);
        CloseServiceHandle(hService);
        return -1;
    }

    LOG_TRACE( logger_, BT_TEXT("����ֹͣ��..."));

    //
    // �ȴ�����ֹͣ����һ������
    //
    if(!waitForServiceState(hService, SERVICE_STOP_PENDING, status))
    {
        LOG_INFO( logger_, BT_TEXT("������[") << name << BT_TEXT( "]״̬����������"));
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCM);
        return -1;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCM);

    if(status.dwCurrentState == SERVICE_STOPPED)
    {
         LOG_TRACE( logger_, BT_TEXT("������ֹͣ."));
    }
    else
    {
	showServiceStatus( BT_TEXT( "������ֹͣ��������"), status);
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
    // ������ʼtick�����ݺͳ�ʼcheckpoint.
    //
    DWORD startTickCount = GetTickCount();
    DWORD oldCheckPoint = status.dwCheckPoint;

    //
    // ��ѯ����״̬
    //
    while(status.dwCurrentState == pendingState)
    {
        //
        // ����ȴ�ʱ��( 1�� �� 10��)
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
        // �ټ�����״̬
        //
        if(!QueryServiceStatus(hService, &status))
        {
            return false;
        }

        if(status.dwCheckPoint > oldCheckPoint)
        {
            //
            // ����ǰ��һ����
            //
            startTickCount = GetTickCount();
            oldCheckPoint = status.dwCheckPoint;
        }
        else
        {
            if(GetTickCount() - startTickCount > status.dwWaitHint)
            {
                //
                // �����ȴ�����
                //
                break;
            }
        }
    }

    return true;
}

void ServiceManager::showServiceStatus(const std::string& msg, SERVICE_STATUS& status)
{
	std::string state;
    switch(status.dwCurrentState)
    {
    case SERVICE_STOPPED:
	state = BT_TEXT( "��ֹͣ");
	break;
    case SERVICE_START_PENDING:
	state = BT_TEXT( "������");
	break;
    case SERVICE_STOP_PENDING:
	state = BT_TEXT( "ֹͣ��");
	break;
    case SERVICE_RUNNING:
	state = BT_TEXT( "������");
	break;
    case SERVICE_CONTINUE_PENDING:
	state = BT_TEXT( "�ָ���");
	break;
    case SERVICE_PAUSE_PENDING:
	state = BT_TEXT( "��ͣ��");
	break;
    case SERVICE_PAUSED:
	state = BT_TEXT( "����ͣ");
	break;
    default:
	state = "δ֪";
	break;
    }

   
   LOG_TRACE( logger_, msg << BT_TEXT( ",")
	 << BT_TEXT("  ��ǰ״̬: " ) << state << BT_TEXT( ",")
	 << BT_TEXT("  �˳�����: " ) << status.dwWin32ExitCode << BT_TEXT( ",")
	 << BT_TEXT("  �����˳�����: " ) << status.dwServiceSpecificExitCode << BT_TEXT( ",")
	 << BT_TEXT("  ����: " ) << status.dwCheckPoint << BT_TEXT( ",")
	 << BT_TEXT("  �ȴ�������: " ) << status.dwWaitHint );
}

_jomoo_end