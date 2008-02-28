

#ifndef BOE_WIN_SELECT_REACTOR_H
#define BOE_WIN_SELECT_REACTOR_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include <set>
#include <vector>
#include "BOE_SOCK.H"
#include "include/BOE_Operation_Result.h"




//class BOE_WIN32_Select_Operation_Result;
//class BOE_WIN_Select_Reactor
//{
//public:
//	BOE_WIN_Select_Reactor( bool result_delete = true );
//	BOE_WIN_Select_Reactor( u_long milli_seconds , bool result_delete = true );
//	~BOE_WIN_Select_Reactor(void);
//
//	int open ( size_t number_of_threads );
//	void close (void);
//	int handle_events ( u_long milli_seconds);
//
//	int register_handle ( BOE_WIN32_Select_Operation_Result* handle );
//
//	int unregister_handle ( BOE_WIN32_Select_Operation_Result* handle ) ;
//
//	static BOE_WIN_Select_Reactor* get( BOE_WIN_Select_Reactor* proactor = 0 );
//
//private:
//	void application_specific_code (BOE_WIN32_Select_Operation_Result *asynch_result,
//		size_t bytes_transferred,
//		const void *completion_key,
//		BOOL success);
//
//	bool result_delete_;
//
//	std::set< BOE_WIN32_Select_Operation_Result* > container_;
//	fd_set fdSet_;
//};
//
//class BOE_WIN32_Select_Operation_Result
//	: public BOE_OVERLAPPED
//	, public BOE_Operation_Result
//{
//public:
//
//	BOE_WIN32_Select_Operation_Result( BOE_WIN_Select_Reactor &proactor , BOE_SOCK_HANDLE handle, void * act )
//		: m_proactor_( proactor )
//		, m_handle_( handle )
//		, m_act_( act )
//	{
//		Internal =  0;
//		InternalHigh =  0;
//		Offset =  0;
//		OffsetHigh =  0;
//		hEvent = 0;
//	}
//
//	virtual ~BOE_WIN32_Select_Operation_Result(void){}
//
//	BOE_WIN_Select_Reactor* get_proactor()
//	{
//		return &m_proactor_;
//	}
//
//	virtual int open(  )
//	{
//		return m_proactor_.register_handle( this );
//	}
//
//	BOE_SOCK_HANDLE getHandle() const
//	{
//		return m_handle_;
//	}
//
//	void setHandle( BOE_SOCK_HANDLE handle )
//	{
//		m_handle_ = handle;
//	}
//
//private:
//	BOE_SOCK_HANDLE m_handle_;
//
//	void * m_act_;
//
//	BOE_WIN_Select_Reactor& m_proactor_;
//
//};

#endif // BOE_WIN_SELECT_REACTOR_H