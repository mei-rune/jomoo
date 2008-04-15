

#ifndef JOMOO_proactor_H
#define JOMOO_proactor_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "jomoo/platform/OS.H"
#include "Base/Collections/ThreadSafePtrQueue.HPP"

_networks_begin

class proactor
{
public:

	proactor( bool result_delete = true );
	proactor( u_long milli_seconds , bool result_delete = true );
	~proactor(void);

	int open ( size_t number_of_threads = 0 );
	void close (void);
	
	int register_handle (JOMOO_HANDLE handle,const void *completion_key);

	int handle_events ( u_long milli_seconds);

	JOMOO_HANDLE get_handle();

private:
	void application_specific_code (WIN32_Operation_Result *asynch_result,
		size_t bytes_transferred,
		const void *completion_key,
		u_long error);

	JOMOO_HANDLE m_completion_port_;
	u_long m_number_of_threads_;

	bool result_delete_;
};

_networks_end

#endif // JOMOO_proactor_H