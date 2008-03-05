

#ifndef JOMOO_WIN32_OPERATION_PROACTOR_H
#define JOMOO_WIN32_OPERATION_PROACTOR_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "Platform/OS.H"
#include "include/OperationProactor.H"
#include "Base/Collections/ThreadSafePtrQueue.HPP"

_networks_begin

class WIN32OperationOverlapped;
//class WIN32_Defer;

class WIN32_Operation_Proactor : public JOMOO_Operation_Proactor
{
public:

	WIN32_Operation_Proactor( bool result_delete = true );
	WIN32_Operation_Proactor( u_long milli_seconds , bool result_delete = true );
	~WIN32_Operation_Proactor(void);

	int open ( size_t number_of_threads = 0 );
	void close (void);
	
	int register_handle (JOMOO_HANDLE handle,const void *completion_key);

	int handle_events ( u_long milli_seconds);

	int post_completion ( WIN32OperationOverlapped *result );
	int post_completion ( JOMOO_Operation_Result_Ptr result );

	//WIN32_Defer* createDefer( JOMOO_Operation_Result_Ptr result );

	JOMOO_HANDLE get_handle();

private:
	void application_specific_code (WIN32OperationOverlapped *asynch_result,
		size_t bytes_transferred,
		const void *completion_key,
		u_long error);

	JOMOO_HANDLE m_completion_port_;
	u_long m_number_of_threads_;

	bool result_delete_;

	//ThreadSafePtrQueue< WIN32_Defer > queue_;
};

_networks_end

#endif // JOMOO_WIN32_OPERATION_PROACTOR_H