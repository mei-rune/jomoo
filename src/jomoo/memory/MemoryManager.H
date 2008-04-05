

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ¤╭⌒╮ ╭⌒╮						  Memory_Base.H,v 1.0 2005/03/25 10:52:54
*  ╱◥██◣ ╭╭ ⌒╮
* ︱田︱田田| ╰------
* -------------------------------------------------------------------------------
*/

#ifndef _jomoo_memory_Manager_H_
#define _jomoo_memory_Manager_H_


#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_Memory.H"
# include "jomoo/memory/pool.h"
# include "jomoo/jomoo_export.h"

_jomoo_memory_begin

/**
 * @Brief 内存池管理器
 */
class pool_mgr
{
public:

	virtual ~pool_mgr(){}

	/**
	 * 取得默认的内存池
	 * @return 返回默认的内存池的指针
	 */
	virtual pool_ptr getPool( ) = 0;

	/**
	 * 创建一个内存池
	 * @param[ in ] name 内存池名称
	 * @param[ in ] pages 指定内存池预分配内存块的大小
	 * @return 返回内存池的指针
	 */
	virtual pool_ptr createPool( const tstring& name , size_t pages = -1 ) = 0;
		
	/**
	 * 创建一个固定大小内存池
	 * @param[ in ] name 内存池名称
	 * @param[ in ] number 指定内存池预分配内存块的数目
	 * @param[ in ] size 指定内存池每个预分配内存块的大小
	 * @return 返回内存池的指针
	 */
	virtual fixed_pool_ptr createPool( const tstring& name, size_t number,size_t size ) = 0;
	
	/**
	 * 查找一个内存池
	 * @param[ in ] name 内存池名称
	 * @return 返回内存池的指针
	 */
	virtual pool_ptr findPool( const tstring& name  ) = 0;

	/**
	 * 查找一个固定大小内存池
	 * @param[ in ] name 内存池名称
	 * @return 返回内存池的指针
	 */
	virtual fixed_pool_ptr findPool( const tstring& name, size_t chunk_size ) = 0;

	/**
	 * 打印出内存池管理器的状态
	 * @param[ in ] Target 输出流
	 */
	virtual void dump( tostream& Target ) const = 0;

	/**
	 * 内存池管理器的描述
	 * @return 返回描述
	 */
	virtual const tstring& toString() const = 0;
};

_jomoo_memory_end

/**
 * 取得默认的内存池
 * @return 返回默认的内存池的指针
 */
JOMOO_Export_C _jomoo_memory pool_mgr* ___getPoolManager();

/**
 * 打印出内存池管理器的状态
 * @param[ in ] Target 输出流
 */
JOMOO_Export_C void  ___dumpPoolManager( tostream& Target );

/**
 * 取得默认的内存池
 * @return 返回默认的内存池的指针
 */
JOMOO_Export_C _jomoo_memory pool_ptr ___getPool( );

/**
 * 创建一个内存池
 * @param[ in ] name 内存池名称
 * @param[ in ] pages 指定内存池预分配内存块的大小
 * @return 返回内存池的指针
 */
JOMOO_Export_C _jomoo_memory pool_ptr ___createPool( const tstring& name , size_t pages );
	
/**
 * 创建一个固定大小内存池
 * @param[ in ] name 内存池名称
 * @param[ in ] number 指定内存池预分配内存块的数目
 * @param[ in ] size 指定内存池每个预分配内存块的大小
 * @return 返回内存池的指针
 */
JOMOO_Export_C _jomoo_memory fixed_pool_ptr ___createLoopPool( const tstring& name, size_t number,size_t size );

/**
 * 查找一个内存池
 * @param[ in ] name 内存池名称
 * @return 返回内存池的指针
 */
JOMOO_Export_C _jomoo_memory pool_ptr ___findPool( const tstring& name  );

/**
 * 查找一个固定大小内存池
 * @param[ in ] name 内存池名称
 * @return 返回内存池的指针
 */
JOMOO_Export_C _jomoo_memory fixed_pool_ptr ___findLoopPool( const tstring& name, size_t chunk_size);

/**
 * 分配指定大小的内存块
 * @param[ in ] nbytes 内存块的大小
 * @param[ in ] file   函数所在的文件名
 * @param[ in ] line   函数所在的文件的行号
 * @return 返回内存块的地址
 * @remark 它可能会失败并扔出内存错误异常
 */
JOMOO_Export_C void* ___system_malloc (size_t nbytes , const char* file, size_t line );

/**
 * 释放内存块
 * @param[ in ] block 内存块的地址
 * @remark 它可能会失败并扔出内存错误异常
 */
JOMOO_Export_C void ___system_free (void* block );

_jomoo_memory_begin

/**
 * 打印出内存池管理器的状态
 * @param[ in ] Target 输出流
 */
inline void dumpPoolManager( tostream& Target )
{
	___dumpPoolManager( Target );
}

/**
 * 取得默认的内存池
 * @return 返回默认的内存池的指针
 */
inline _jomoo_memory pool_ptr getPool( )
{
	return ___getPool( );
}

/**
 * 创建一个内存池
 * @param[ in ] name 内存池名称
 * @param[ in ] pages 指定内存池预分配内存块的大小
 * @return 返回内存池的指针
 */
inline _jomoo_memory pool_ptr createPool( const tstring& name , size_t pages )
{
	return ___createPool( name ,pages);
}
	
/**
 * 创建一个固定大小内存池
 * @param[ in ] name 内存池名称
 * @param[ in ] number 指定内存池预分配内存块的数目
 * @param[ in ] size 指定内存池每个预分配内存块的大小
 * @return 返回内存池的指针
 */
inline _jomoo_memory fixed_pool_ptr createPool( const tstring& name, size_t number,size_t size )
{
	return ___createLoopPool( name ,number, size );
}

/**
 * 查找一个内存池
 * @param[ in ] name 内存池名称
 * @return 返回内存池的指针
 */
inline _jomoo_memory pool_ptr findPool( const tstring& name  )
{
	return ___findPool( name );
}

/**
 * 查找一个固定大小内存池
 * @param[ in ] name 内存池名称
 * @return 返回内存池的指针
 */
inline _jomoo_memory fixed_pool_ptr findPool( const tstring& name , size_t chunk_size )
{
	return ___findLoopPool( name,chunk_size );
}

/**
 * 分配指定大小的内存块
 * @param[ in ] nbytes 内存块的大小
 * @param[ in ] file   函数所在的文件名
 * @param[ in ] line   函数所在的文件的行号
 * @return 返回内存块的地址
 * @remark 它可能会失败并扔出内存错误异常
 */
inline void* system_malloc (size_t nbytes , const char* file, size_t line )
{
	return ___system_malloc( nbytes, file, line );
}

/**
 * 释放内存块
 * @param[ in ] block 内存块的地址
 * @remark 它可能会失败并扔出内存错误异常
 */
inline void system_free (void* block )
{
	___system_free( block ); 
}


_jomoo_memory_end

#endif // _jomoo_memory_Base_H_