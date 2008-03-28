
#include "NTService.h"

#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif

_jomoo_begin

CNTService* CNTService::m_pThis = NULL;

CNTService::CNTService(const tchar* szServiceName,IService* svr, logging::log_ptr ptr )

CNTService::~CNTService()
{
    LOG_TRACE( logger_ ,_T("CNTService::~CNTService()") );
}



bool CNTService::StartService( DWORD dwArgc, LPTSTR* lpszArgv )
{
    SERVICE_TABLE_ENTRY st[] = {
        {&m_szServiceName[0], ServiceMain},
        {NULL, NULL}
    };

    LOG_TRACE( logger_ ,_T( "���� StartServiceCtrlDispatcher"));
    BOOL b = ::StartServiceCtrlDispatcher(st);
    LOG_TRACE( logger_ ,_T("���� StartServiceCtrlDispatcher"));
	return ( b?true: false );
}


void CNTService::ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
    CNTService* pService = m_pThis;
    LOG_TRACE( pService->logger_ ,_T("���� ServiceMain"));


    pService->m_Status.dwCurrentState = SERVICE_START_PENDING;
    pService->m_hServiceStatus = RegisterServiceCtrlHandler( &(pService->m_szServiceName[0]),
                                                           Handler);
    if (pService->m_hServiceStatus == NULL) {
		LOG_INFO( pService->logger_ , _T( "ע�������ƾ��ʧ��" ) );
		LOG_TRACE( pService->logger_ ,_T( "�˳� :ServiceMain()"));
        return;
    }

    if (pService->Initialize( dwArgc, lpszArgv )) {
        pService->m_bIsRunning = TRUE;
        pService->m_Status.dwWin32ExitCode = 0;
        pService->m_Status.dwCheckPoint = 0;
        pService->m_Status.dwWaitHint = 0;
        pService->m_svr_->run();
    }

    // ֪ͨNT��������������ѹر�
    pService->SetStatus(SERVICE_STOPPED);

    LOG_TRACE( pService->logger_ ,_T( "�˳� ServiceMain") );
}


void CNTService::SetStatus(DWORD dwState)
{
    LOG_INFO( logger_ , _T( "���ķ�����״̬(") << m_hServiceStatus << _T("," )<< dwState << _T( ")"));
    m_Status.dwCurrentState = dwState;
    ::SetServiceStatus(m_hServiceStatus, &m_Status);
}


bool CNTService::Initialize( DWORD dwArgc, LPTSTR* lpszArgv )
{
    LOG_TRACE( logger_ ,_T("���� Initialize"));
    SetStatus(SERVICE_START_PENDING);
    
    bool bResult = m_svr_->OnInit( dwArgc, lpszArgv ); 
    
    // Set final state
    m_Status.dwWin32ExitCode = GetLastError();
    m_Status.dwCheckPoint = 0;
    m_Status.dwWaitHint = 0;
    if (!bResult) {
        LOG_INFO( logger_ ,_T("�û���ʼ��ʧ��"));
        SetStatus(SERVICE_STOPPED);
		LOG_TRACE( logger_ ,_T("�˳� Initialize"));
        return false;    
    }
    
	LOG_INFO( logger_ ,_T("����������"));

    SetStatus(SERVICE_RUNNING);

    LOG_TRACE( logger_ ,_T("�˳� Initialize"));
    return true;
}

void CNTService::Handler(DWORD dwOpcode)
{
    CNTService* pService = m_pThis;
    
    LOG_TRACE( pService->logger_,_T("���յ���������[")<< dwOpcode << _T("]"));
    switch (dwOpcode) {
    case SERVICE_CONTROL_STOP: // 1
        pService->SetStatus(SERVICE_STOP_PENDING);
        pService->m_svr_->OnStop();
        pService->m_bIsRunning = false;
      
        break;
    case SERVICE_CONTROL_PAUSE: // 2
        pService->m_svr_->OnPause();
        break;

    case SERVICE_CONTROL_CONTINUE: // 3
        pService->m_svr_->OnContinue();
        break;

    case SERVICE_CONTROL_INTERROGATE: // 4
        pService->m_svr_->OnInterrogate();
        break;

    case SERVICE_CONTROL_SHUTDOWN: // 5
        pService->m_svr_->OnShutdown();
        break;
	case SERVICE_CONTROL_NETBINDADD: // NT ��֧��
		 pService->m_svr_->OnNetBindAdd();
		break;
	case SERVICE_CONTROL_NETBINDENABLE: // NT ��֧��
		 pService->m_svr_->OnNetBindEnable();
		break;
	case SERVICE_CONTROL_NETBINDDISABLE: // NT ��֧��
		 pService->m_svr_->OnNetBindDisable();
		break;
		
	case SERVICE_CONTROL_NETBINDREMOVE: // NT ��֧��
		 pService->m_svr_->OnNetBindRemove();
		break;
	case SERVICE_CONTROL_PARAMCHANGE: // NT ��֧��
		 pService->m_svr_->OnParamChange();
		break;
    default:
        if (dwOpcode >= SERVICE_CONTROL_USER) {
           pService->m_svr_->OnUserControl(dwOpcode);
        } else {
			    LOG_INFO( pService->logger_,_T( "����ķ���֪ͨ")  );

           
        }
        break;
    }

    // Report current status
    LOG_TRACE( pService->logger_,_T( "���·���״̬(") 
		<< pService->m_hServiceStatus << _T( "," )
		<< pService->m_Status.dwCurrentState << _T(")"));

    ::SetServiceStatus(pService->m_hServiceStatus, &pService->m_Status);
}


_jomoo_end