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
        // ʹ�ñ�ִ���ļ�
        //
        char buf[_MAX_PATH];
        if(GetModuleFileName(NULL, buf, _MAX_PATH) == 0)
        {
            error("û��ִ���ļ���");
            return -1;
        }
        exec = buf;
    }

    //
    // ����пո�Ļ���������
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
	// ƴ��ѡ���ַ���
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
        syserror("���ܴ� SCM");
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
        syserror("���ܰ�װ����[" + name + "]");
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
        syserror("���ܴ� SCM");
        return -1;
    }

    SC_HANDLE hService = OpenService(hSCM, name.c_str(), SC_MANAGER_ALL_ACCESS);
    if(hService == NULL)
    {
        syserror("���ܴ򿪷���[" + name + "]");
        CloseServiceHandle(hSCM);
        return -1;
    }

    BOOL b = DeleteService(hService);

    if(!b)
    {
        syserror("����ж�ط���[" + name + "]");
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
        syserror("���ܴ� SCM");
        return -1;
    }

    SC_HANDLE hService = OpenService(hSCM, name.c_str(), SC_MANAGER_ALL_ACCESS);
    if(hService == NULL)
    {
        syserror("���ܴ򿪷���[" + name + "]");
        CloseServiceHandle(hSCM);
        return -1;
    }

    //
	// ���ַ���ƴ�� char* []��ʽ
    //
    const int argc = args.size();
    LPCSTR* argv = new LPCSTR[argc];
    int i = 0;
    for(vector<string>::const_iterator p = args.begin(); p != args.end(); ++p)
    {
        argv[i++] = strdup(p->c_str());
    }

    //
    // ��������
    //
    BOOL b = StartService(hService, argc, argv);

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
        syserror("������������[" + name + "]");
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCM);
        return -1;
    }

    trace("��������������...");

    //
    // 
    //
    SERVICE_STATUS status;
    if(!waitForServiceState(hService, SERVICE_START_PENDING, status))
    {
        syserror("������[" + name + "]״̬����������");
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCM);
        return -1;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCM);

    if(status.dwCurrentState == SERVICE_RUNNING)
    {
        trace("����������...");
    }
    else
    {
	showServiceStatus("������������������", status);
	return -1;
    }

    return 0;
}

int ServiceManager::stopService(const string& name)
{
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(hSCM == NULL)
    {
        syserror("���ܴ� SCM");
        return -1;
    }

    SC_HANDLE hService = OpenService(hSCM, name.c_str(), SC_MANAGER_ALL_ACCESS);
    if(hService == NULL)
    {
       syserror("���ܴ򿪷���[" + name + "]");
        CloseServiceHandle(hSCM);
        return -1;
    }

    SERVICE_STATUS status;
    BOOL b = ControlService(hService, SERVICE_CONTROL_STOP, &status);

    if(!b)
    {
        syserror("����ֹͣ����[" + name + "]");
        CloseServiceHandle(hSCM);
        CloseServiceHandle(hService);
        return -1;
    }

    trace("����ֹͣ��...");

    //
    // �ȴ�����ֹͣ����һ������
    //
    if(!waitForServiceState(hService, SERVICE_STOP_PENDING, status))
    {
        syserror("������[" + name + "]״̬����������");
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCM);
        return -1;
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCM);

    if(status.dwCurrentState == SERVICE_STOPPED)
    {
         trace("������ֹͣ.");
    }
    else
    {
	showServiceStatus("������ֹͣ��������", status);
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
	 << "  ��ǰ״̬: " << state << endl
	 << "  �˳�����: " << status.dwWin32ExitCode << endl
	 << "  �����˳�����: " << status.dwServiceSpecificExitCode << endl
	 << "  ����: " << status.dwCheckPoint << endl
	 << "  �ȴ�������: " << status.dwWaitHint;
    trace(ostr.str());
}

