
#ifndef Hazel_WIN32_OPERATION_RESULT_H
#define Hazel_WIN32_OPERATION_RESULT_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_Networks.h"
#include "include/Hazel_Operation_Result.h"
#include "WIN32OperationProactor.h"
#include <vector>

_networks_begin

//class WIN32_Defer : public WIN32OperationOverlapped
//{
//public:
//	WIN32_Defer( Hazel_Operation_Result_Ptr result
//		, bool delete_self
//		, WIN32_Operation_Proactor& instance
//		, Hazel_HANDLE handle
//		, void * act )
//		: WIN32OperationOverlapped( instance, handle, act )
//		, delete_self_( delete_self )
//		, result_( result )
//	{
//	}
//
//	void complete (size_t bytes_transferred,
//		int success,
//		const void *completion_key,
//		u_long error)
//	{
//		if( ! is_null( result_ ) )
//		{
//			result_->complete( bytes_transferred, success, completion_key, error );
//			result_.reset( ( Hazel_Operation_Result*)0 );
//		}
//		if( delete_self_ )
//			delete this;
//	}
//
//	void set( Hazel_Operation_Result_Ptr result )
//	{
//		result_ = result;
//	}
//
//private:
//	bool delete_self_;
//	Hazel_Operation_Result_Ptr result_;
//};

_networks_begin

#endif //Hazel_WIN32_OPERATION_RESULT_H