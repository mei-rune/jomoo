
#include "NTService.h"

#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif

_util_begin

CNTService* CNTService::m_pThis = NULL;

CNTService::CNTService(const tchar* szServiceName,JOMOO_Service* svr, UtilLoggerPtr ptr )
: m_svr_( svr )
, logger_( ptr )
{
	if( m_pThis != 0 )
		throw std::runtime_error( BT_TEXT( "����ʵ��ֻ����һ��") );
	if( szServiceName == 0 )
		throw std::runtime_error( BT_TEXT( "����������Ϊ��") );

	if( m_svr_ == 0 )
		throw std::runtime_error( BT_TEXT( "����ص����ܿ�") );

    m_pThis = this;
    

    m_szServiceName.resize( strlen( szServiceName ) +10, 0 );
	strcpy( &m_szServiceName[0], szServiceName );
    m_iMajorVersion = 1;
    m_iMinorVersion = 0;


    m_hServiceStatus = NULL;
    m_Status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    m_Status.dwCurrentState = SERVICE_STOPPED;
    m_Status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    m_Status.dwWin32ExitCode = 0;
    m_Status.dwServiceSpecificExitCode = 0;
    m_Status.dwCheckPoint = 0;
    m_Status.dwWaitHint = 0;
    m_bIsRunning = FALSE;
}

CNTService::~CNTService()
{
    LOG_TRACE( logger_ ,BT_TEXT("CNTService::~CNTService()") );
}



bool CNTService::StartService( DWORD dwArgc, LPTSTR* lpszArgv )
{
    SERVICE_TABLE_ENTRY st[] = {
        {&m_szServiceName[0], ServiceMain},
        {NULL, NULL}
    };

    LOG_TRACE( logger_ ,BT_TEXT( "���� StartServiceCtrlDispatcher"));
    BOOL b = ::StartServiceCtrlDispatcher(st);
    LOG_TRACE( logger_ ,BT_TEXT("���� StartServiceCtrlDispatcher"));
	return ( b?true: false );
}


void CNTService::ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
    CNTService* pService = m_pThis;
    LOG_TRACE( pService->logger_ ,BT_TEXT("���� ServiceMain"));


    pService->m_Status.dwCurrentState = SERVICE_START_PENDING;
    pService->m_hServiceStatus = RegisterServiceCtrlHandler( &(pService->m_szServiceName[0]),
                                                           Handler);
    if (pService->m_hServiceStatus == NULL) {
		LOG_INFO( pService->logger_ , BT_TEXT( "ע�������ƾ��ʧ��" ) );
		LOG_TRACE( pService->logger_ ,BT_TEXT( "�˳� :ServiceMain()"));
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

    LOG_TRACE( pService->logger_ ,BT_TEXT( "�˳� ServiceMain") );
}


void CNTService::SetStatus(DWORD dwState)
{
    LOG_INFO( logger_ , BT_TEXT( "���ķ�����״̬(") << m_hServiceStatus << BT_TEXT("," )<< dwState << BT_TEXT( ")"));
    m_Status.dwCurrentState = dwState;
    ::SetServiceStatus(m_hServiceStatus, &m_Status);
}


bool CNTService::Initialize( DWORD dwArgc, LPTSTR* lpszArgv )
{
    LOG_TRACE( logger_ ,BT_TEXT("���� Initialize"));
    SetStatus(SERVICE_START_PENDING);
    
    bool bResult = m_svr_->OnInit( dwArgc, lpszArgv ); 
    
    // Set final state
    m_Status.dwWin32ExitCode = GetLastError();
    m_Status.dwCheckPoint = 0;
    m_Status.dwWaitHint = 0;
    if (!bResult) {
        LOG_INFO( logger_ ,BT_TEXT("�û���ʼ��ʧ��"));
        SetStatus(SERVICE_STOPPED);
		LOG_TRACE( logger_ ,BT_TEXT("�˳� Initialize"));
        return false;    
    }
    
	LOG_INFO( logger_ ,BT_TEXT("����������"));

    SetStatus(SERVICE_RUNNING);

    LOG_TRACE( logger_ ,BT_TEXT("�˳� Initialize"));
    return true;
}

void CNTService::Handler(DWORD dwOpcode)
{
    CNTService* pService = m_pThis;
    
    LOG_TRACE( pService->logger_,BT_TEXT("���յ���������[")<< dwOpcode << BT_TEXT("]"));
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
			    LOG_INFO( pService->logger_,BT_TEXT( "����ķ���֪ͨ")  );

           
        }
        break;
    }

    // Report current status
    LOG_TRACE( pService->logger_,BT_TEXT( "���·���״̬(") 
		<< pService->m_hServiceStatus << BT_TEXT( "," )
		<< pService->m_Status.dwCurrentState << BT_TEXT(")"));

    ::SetServiceStatus(pService->m_hServiceStatus, &pService->m_Status);
}


_util_end