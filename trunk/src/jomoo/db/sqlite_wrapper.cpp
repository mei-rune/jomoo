
#include <windows.h>
#include "sqlite_wrapper.h"

#ifdef _MEMORY_DEBUG 
	#undef THIS_FILE
	#define new	   DEBUG_NEW  
	#define malloc DEBUG_MALLOC  
    static char THIS_FILE[] = __FILE__;  
#endif






_jomoo_db_begin

HINSTANCE hIns = 0;		//Ö÷DLLµÄ¾ä±ú.
sqlite3_close_t sqlite3_close_;
sqlite3_open_t sqlite3_open_;
sqlite3_exec_t sqlite3_exec_;
sqlite3_free_t sqlite3_free_;
sqlite3_errmsg_t sqlite3_errmsg_;
sqlite3_finalize_t sqlite3_finalize_;
sqlite3_reset_t sqlite3_reset_;
sqlite3_prepare_t sqlite3_prepare_;
sqlite3_bind_blob_t sqlite3_bind_blob_;
sqlite3_bind_double_t sqlite3_bind_double_;
sqlite3_bind_int_t sqlite3_bind_int_;
sqlite3_bind_int64_t sqlite3_bind_int64_;
sqlite3_bind_null_t sqlite3_bind_null_;
sqlite3_bind_text_t sqlite3_bind_text_;
sqlite3_bind_text16_t sqlite3_bind_text16_;
sqlite3_step_t sqlite3_step_;
sqlite3_column_int_t sqlite3_column_int_;
sqlite3_column_int64_t sqlite3_column_int64_;
sqlite3_column_text_t sqlite3_column_text_;
sqlite3_column_text16_t sqlite3_column_text16_;
sqlite3_column_type_t sqlite3_column_type_;
sqlite3_column_double_t sqlite3_column_double_;
sqlite3_column_name_t sqlite3_column_name_;
sqlite3_column_count_t sqlite3_column_count_;
sqlite3_bind_parameter_index_t sqlite3_bind_parameter_index_;
sqlite3_value_type_t sqlite3_value_type_;
sqlite3_result_null_t sqlite3_result_null_;
sqlite3_value_text_t sqlite3_value_text_;
sqlite3_result_int_t sqlite3_result_int_;
sqlite3_create_function_t sqlite3_create_function_;
sqlite3_value_int64_t sqlite3_value_int64_;
sqlite3_busy_timeout_t sqlite3_busy_timeout_;
sqlite3_changes_t sqlite3_changes_;


bool ___init_sqlite( const char* name )
{
	hIns = LoadLibrary( name );
	if( hIns == NULL )
		return false;
	sqlite3_open_ = ( sqlite3_open_t ) GetProcAddress( hIns, "sqlite3_open" );
	if( sqlite3_open_ == 0 )
		return false;
	sqlite3_close_ = ( sqlite3_close_t ) GetProcAddress( hIns, "sqlite3_close" );
	if( sqlite3_close_ == 0 )
		return false;
	sqlite3_exec_ = ( sqlite3_exec_t ) GetProcAddress( hIns, "sqlite3_exec" );
	if( sqlite3_exec_ == 0 )
		return false;
	sqlite3_free_ = ( sqlite3_free_t ) GetProcAddress( hIns, "sqlite3_free" );
	if( sqlite3_free_ == 0 )
		return false;
	sqlite3_errmsg_ = ( sqlite3_errmsg_t ) GetProcAddress( hIns, "sqlite3_errmsg" );
	if( sqlite3_errmsg_ == 0 )
		return false;
	sqlite3_finalize_ = ( sqlite3_finalize_t ) GetProcAddress( hIns, "sqlite3_finalize" );
	if( sqlite3_finalize_ == 0 )
		return false;
	sqlite3_reset_ = ( sqlite3_reset_t ) GetProcAddress( hIns, "sqlite3_reset" );
	if( sqlite3_reset_ == 0 )
		return false;
	sqlite3_prepare_ = ( sqlite3_prepare_t ) GetProcAddress( hIns, "sqlite3_prepare" );
	if( sqlite3_prepare_ == 0 )
		return false;
	sqlite3_step_ = (sqlite3_step_t) GetProcAddress( hIns, "sqlite3_step" );
	if( sqlite3_step_ == 0 )
		return false;
	sqlite3_bind_int_ = ( sqlite3_bind_int_t ) GetProcAddress( hIns, "sqlite3_bind_int" );
	if( sqlite3_bind_int_ == 0 )
		return false;
	sqlite3_bind_int64_ = ( sqlite3_bind_int64_t ) GetProcAddress( hIns, "sqlite3_bind_int64" );
	if( sqlite3_bind_int64_ == 0 )
		return false;
	sqlite3_bind_double_ = ( sqlite3_bind_double_t ) GetProcAddress( hIns, "sqlite3_bind_double" );
	if( sqlite3_bind_double_ == 0 )
		return false;
	sqlite3_bind_text_ = ( sqlite3_bind_text_t ) GetProcAddress( hIns, "sqlite3_bind_text" );
	if( sqlite3_bind_text_ == 0 )
		return false;
	sqlite3_bind_text16_ = ( sqlite3_bind_text16_t ) GetProcAddress( hIns, "sqlite3_bind_text16" );
	if( sqlite3_bind_text16_ == 0 )
		return false;
	sqlite3_bind_parameter_index_ = ( sqlite3_bind_parameter_index_t ) GetProcAddress( hIns, "sqlite3_bind_parameter_index" );
	if( sqlite3_bind_parameter_index_ == 0 )
		return false;
	sqlite3_column_int_ = ( sqlite3_column_int_t ) GetProcAddress( hIns, "sqlite3_column_int" );
	if( sqlite3_column_int_ == 0 )
		return false;
	sqlite3_column_int64_ = ( sqlite3_column_int64_t ) GetProcAddress( hIns, "sqlite3_column_int64" );
	if( sqlite3_column_int64_ == 0 )
		return false;
	sqlite3_column_double_ = (sqlite3_column_double_t ) GetProcAddress( hIns, "sqlite3_column_double" );
	if( sqlite3_column_double_ == 0 )
		return false;
	sqlite3_column_text_ = (sqlite3_column_text_t ) GetProcAddress( hIns, "sqlite3_column_text" );
	if( sqlite3_column_text_ == 0 )
		return false;
	sqlite3_column_count_ = (sqlite3_column_count_t ) GetProcAddress( hIns, "sqlite3_column_count" );
	if( sqlite3_column_count_ == 0 )
		return false;
	sqlite3_column_type_ = ( sqlite3_column_type_t )GetProcAddress( hIns, "sqlite3_column_type" );
	if( sqlite3_column_type_ == 0 )
		return false;
	sqlite3_column_name_ = ( sqlite3_column_name_t )GetProcAddress( hIns, "sqlite3_column_name" );
	if( sqlite3_column_name_ == 0 )
		return false;

	sqlite3_value_type_ = (sqlite3_value_type_t ) GetProcAddress( hIns, "sqlite3_value_type" );
	if( sqlite3_value_type_ == 0 )
		return false;
	sqlite3_result_null_ = ( sqlite3_result_null_t )GetProcAddress( hIns, "sqlite3_result_null" );
	if( sqlite3_result_null_ == 0 )
		return false;
	sqlite3_value_text_ = ( sqlite3_value_text_t )GetProcAddress( hIns, "sqlite3_value_text" );
	if( sqlite3_value_text_ == 0 )
		return false;
	sqlite3_create_function_ = ( sqlite3_create_function_t )GetProcAddress( hIns, "sqlite3_create_function" );
	if( sqlite3_create_function_ == 0 )
		return false;
	sqlite3_result_int_ = ( sqlite3_result_int_t )GetProcAddress( hIns, "sqlite3_result_int" );
	if( sqlite3_result_int_ == 0 )
		return false;

	sqlite3_value_int64_ = ( sqlite3_value_int64_t )GetProcAddress( hIns, "sqlite3_value_int64" );
	if( sqlite3_value_int64_ == 0 )
		return false;

	sqlite3_busy_timeout_ = ( sqlite3_busy_timeout_t )GetProcAddress( hIns, "sqlite3_busy_timeout" );
	if( sqlite3_busy_timeout_ == 0 )
		return false;

	sqlite3_changes_ = ( sqlite3_changes_t )GetProcAddress( hIns, "sqlite3_changes" );
	if( sqlite3_changes_ == 0 )
		return false;
	return true;
}

void ___shutdown_sqlite( )
{
	if( hIns != NULL )
		FreeLibrary(hIns);
	hIns = NULL;
}

_jomoo_db_end

