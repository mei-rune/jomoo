#include "StdAfx.h"
#include "bt_shell.h"
#include <vector>


DWORD GetAppPath(char *szModName, DWORD Size)
{
	DWORD ps = GetModuleFileName(NULL, szModName, Size);
	while(ps > 0 && szModName[ps-1] != '\\') ps--;
	szModName[ps] = '\0';
	return ps;
}

BT_Shell::BT_Shell( const tstring & comm_line )
: comm_line_( comm_line )
{
	init( );
}

BT_Shell::BT_Shell( const tstring & app_name, const tstring& comm_line )
: app_name_( app_name )
, comm_line_( comm_line )
{
	init( );
}
BT_Shell::BT_Shell( const tchar* comm_line )
{
	if( comm_line != 0 )
		comm_line_ = comm_line;
	init( );
}

BT_Shell::BT_Shell( const tchar* app_name, const tchar* comm_line )
{
	if( app_name != 0 )
		app_name_ = app_name;
	if( comm_line != 0 )
		comm_line_ = comm_line;
	init( );
}

BT_Shell::~BT_Shell(void)
{
	if( success_ )
	{
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );
	}
	if ( hChildStdout != INVALID_HANDLE_VALUE ) 
	{
		::CloseHandle( hChildStdout );
		hChildStdout = INVALID_HANDLE_VALUE;
	}

	if( tstrcmp( TempFileName,"") != 0 )
		::DeleteFile( TempFileName );
}

int BT_Shell::init( )
{
	success_ = false;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 


	screen_ = false;
	hChildStdout = INVALID_HANDLE_VALUE;
	TempFileName[ 0 ] = 0;
	TempFileName[ 1 ] = 0;

	return 0;
}

int BT_Shell::svc( )
{
	const tchar* app_name = 0;
	tchar* comm_line = 0;
	std::vector< tchar > comm_str;
	if( app_name_ != "" )
		app_name = app_name_.c_str();
	if( comm_line_ != "" )
	{
		comm_str.resize( comm_line_.size() + 3 );
		tstrcpy( &comm_str[ 0 ], comm_line_.c_str() );
		comm_line = &comm_str[ 0 ];
	}


	HANDLE hSaveStdout = INVALID_HANDLE_VALUE;
	if( screen_ )
	{
		hSaveStdout = GetStdHandle(STD_OUTPUT_HANDLE); 

		if ( hChildStdout == INVALID_HANDLE_VALUE)
		{
			tchar path[ MAX_PATH ] = "";
			GetTempPath( MAX_PATH, path );

			GetTempFileName( path,"SCREEN_",0,TempFileName );
			hChildStdout = CreateFile( TempFileName
				,GENERIC_WRITE
				,FILE_SHARE_READ|FILE_SHARE_WRITE
				,&saAttr
				,CREATE_ALWAYS
				,FILE_FLAG_RANDOM_ACCESS
				,NULL );
		}

		if ( hChildStdout != INVALID_HANDLE_VALUE && !SetStdHandle(STD_OUTPUT_HANDLE, hChildStdout) ) 
		{
			::CloseHandle( hChildStdout );
			hChildStdout = INVALID_HANDLE_VALUE;
		}
	}

	char PATH[ MAX_PATH ] = ""; 
	GetAppPath( PATH , MAX_PATH );

	// Start the child process. 
	if( ( comm_line != 0 || app_name != 0 ) && CreateProcess( app_name, // No module name (use command line). 
		comm_line, // Command line. 
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,             // Use parent's environment block. 
		PATH,              
		&si,              // Pointer to STARTUPINFO structure.
		&pi )             // Pointer to PROCESS_INFORMATION structure.
		) 
	{
		success_ = true;
	}
	else
	{
		LPVOID lpMsgBuf;
		if ( FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL ))
		{
			last_error_ = (LPCTSTR)lpMsgBuf;
			LocalFree( lpMsgBuf );
		}
	}

	//if( screen_ && hChildStdout != INVALID_HANDLE_VALUE )
	//{

	//}

	 
   if ( hSaveStdout != INVALID_HANDLE_VALUE ) 
      SetStdHandle( STD_OUTPUT_HANDLE, hSaveStdout );
 
	if( success_ )
		return 0;
	return -1;
}

int BT_Shell::wait( DWORD timeout )
{
    if( WaitForSingleObject( pi.hProcess, timeout * 1000 ) == WAIT_OBJECT_0 )
		return 0;
	return -1;
}

int BT_Shell::exit_code( DWORD &ExitCode )
{
	if( success_ && GetExitCodeProcess( pi.hProcess, &ExitCode ) )
		return 0;
	return -1;
}

int BT_Shell::screen_str( tstring& str )
{
	tchar inBuffer[ 1002 ] = "";
	DWORD nBytesRead = 0;
	while( ReadFile( hChildStdout, &inBuffer, 1000, &nBytesRead, NULL ) )
	{
		inBuffer[ nBytesRead ] = 0;
		str += inBuffer;
		nBytesRead = 0;		
	}
	return 0;
}

const tstring& BT_Shell::last_error( ) const
{
	return last_error_;
}

void BT_Shell::screen( )
{
	screen_ = true;
}