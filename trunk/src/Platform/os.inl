
bool close_handle( Hazel_HANDLE &handle )
{
	if( handle != NULL )
		return ( ::CloseHandle( handle ) == TRUE );
	else
		return true;
}

bool dup_handle( Hazel_HANDLE hSourceProcessHandle,
					Hazel_HANDLE hSourceHandle,
					Hazel_HANDLE hTargetProcessHandle,
					HANDLE& lpTargetHandle,
					DWORD dwDesiredAccess,
					bool bInheritHandle,
					DWORD dwOptions )
{
	return DuplicateHandle(
		hSourceProcessHandle,
		hSourceHandle,
		hTargetProcessHandle,
		& lpTargetHandle,
		dwDesiredAccess,
		bInheritHandle ?TRUE:FALSE,
		dwOptions
		) == TRUE;
}

bool get_handle_info( Hazel_HANDLE hObject,DWORD& dwFlags )
{
	return ( GetHandleInformation( hObject,&dwFlags) == TRUE );
}


bool get_handle_info( Hazel_HANDLE hObject, DWORD dwMask, DWORD dwFlags )
{
	return ( SetHandleInformation( hObject,dwMask,dwFlags) == TRUE );
}

long InterlockedIncrement( long& v )
{

#ifdef Hazel_MT
	return ::InterlockedIncrement( &v );
#else
	return ++v;
#endif 
}

long InterlockedDecrement( long& v )
{
#ifdef Hazel_MT
	return ::InterlockedDecrement( &v );
#else
	return --v;
#endif 
}