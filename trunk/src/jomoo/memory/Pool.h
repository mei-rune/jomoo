

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ¤╭⌒╮ ╭⌒╮						  pool.h,v 1.0 2008/03/25 10:52:54
*  ╱◥██◣ ╭╭ ⌒╮
* ︱田︱田田| ╰------
* -------------------------------------------------------------------------------
*/

# ifndef _pool_h_
# define _pool_h_

# include "jomoo/config.h"

# if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
# endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_Memory.H"
# include "jomoo/string.hpp"
# include "jomoo/exception.hpp"

_memory_begin

const char pool_magic[4] = { 'p','o','o','l'};
const int32_t pool_magic_v = *( int32_t *)pool_magic;

MakeException( BadMemoryException , "分配内存块失败" );

/**
 * @Brief 内存池接口
 */
class pool
{
public:
	typedef pool* ptr_type;
	typedef pool* pool_ptr;

	/**
	 * virtual destructor
	 */
	virtual ~pool(){};

	/**
	 * 分配指定大小的内存块
	 * @param[ in ] nbytes 内存块的大小
	 * @param[ in ] file   函数所在的文件名
	 * @param[ in ] line   函数所在的文件的行号
	 * @return 返回内存块的地址
	 * @remark 它可能会失败并扔出内存错误异常
	 */
	virtual void* malloc (size_t nbytes , const char* file=0, size_t line=-1 ) = 0;

	/**
	 * 释放内存块
	 * @param[ in ] block 内存块的地址
	 * @remark 它可能会失败并扔出内存错误异常
	 */
	virtual void free (void* block ) = 0;

	/**
	 * 打印出内存池的状态
	 * @param[ in ] Target 输出流
	 */
	virtual void dump( std::ostream& Target ) const = 0;

	/**
	 * 内存池的描述
	 * @return 返回描述
	 */
	virtual const tstring& toString() const = 0;
};

/**
 * @Brief 固定大小内存池接口
 */
class fixed_pool
{
public:

	typedef fixed_pool* ptr_type;
	typedef fixed_pool* fixed_pool_ptr;

	/**
	 * virtual destructor
	 */
	virtual ~fixed_pool(){}
		
	/**
	 * 分配指定大小的内存块
	 * @param[ in ] file   函数所在的文件名
	 * @param[ in ] line   函数所在的文件的行号
	 * @return 返回内存块的地址
	 * @remark 它可能会失败并扔出内存错误异常，它没有指定内存块大小
	 */
	virtual void* malloc( const char* file=0, size_t line=-1 ) = 0;

	/**
	 * 释放内存块
	 * @param[ in ] block 内存块的地址
	 * @remark 它可能会失败并扔出内存错误异常
	 */
	virtual void  free( void* block ) = 0;

	/**
	 * 取得每个内存块的大小
	 * @return 返回每个内存块的大小
	 */
	virtual size_t chunk_size() const = 0;

	/**
	 * 打印出内存池的状态
	 * @param[ in ] Target 输出流
	 */
	virtual void dump( std::ostream& Target ) const = 0;

	/**
	 * 内存池的描述
	 * @return 返回描述
	 */
	virtual const tstring& toString() const = 0;
};

typedef pool::pool_ptr pool_ptr;
typedef fixed_pool::fixed_pool_ptr fixed_pool_ptr;

		// TEMPLATE FUNCTION _Destroy
template<class _Ty> inline
	void _Destroy(_Ty _FARQ *_Ptr)
	{	// destroy object at _Ptr
	_DESTRUCTOR(_Ty, _Ptr);
	}

template<> inline
	void _Destroy(char _FARQ *)
	{	// destroy a char (do nothing)
	}

template<> inline
	void _Destroy(wchar_t _FARQ *)
	{	// destroy a wchar_t (do nothing)
	}

_memory_end

/**
 * new "placement" 用内存池代替系统内存分配器
 * @param[ in ] size     对象需要的大小
 * @param[ in ] pool     用户内存池
 * @return 分配的内存块
 */
inline void * operator new(size_t size , _memory pool_ptr pools)
{
   return pools->malloc( size );
}

/**
 * delete "placement" 用内存池代替系统内存分配器
 * @param[ in ] chunk    内存块
 * @param[ in ] pool     用户内存池
 */
inline void   operator delete(void * chunk , _memory pool_ptr pools)
{
   pools->free(chunk);
}

/**
 * new "placement" 用固定内存池代替系统内存分配器
 * @param[ in ] size     对象需要的大小
 * @param[ in ] pool     用户内存池
 * @return 分配的内存块
 */
inline void * operator new(size_t size , _memory fixed_pool_ptr pools)
{
   ASSERT( size <= pools->chunk_size() );
   return pools->malloc();
}

/**
 * delete "placement" 用固定内存池代替系统内存分配器
 * @param[ in ] chunk    内存块
 * @param[ in ] pool     用户内存池
 */
inline void   operator delete(void * chunk , _memory fixed_pool_ptr pools)
{   
   pools->free(chunk);
}

inline void* pool_malloc( _memory fixed_pool_ptr pools ,const char* file , size_t line )
{
	return pools->malloc( file,line );
}

inline void* pool_malloc( _memory pool_ptr pools ,size_t size ,const char* file , size_t line )
{
	return pools->malloc(  size, file,line );
}
inline void* pool_malloc( _memory fixed_pool_ptr pools ,size_t size ,const char* file , size_t line )
{
	return pools->malloc( file,line );
}

#define JOMOO_MALLOC( pool, size ) pool->malloc( size, __FILE__,__LINE__ )
#define JOMOO_FIXED_MALLOC( pool )pool->malloc( __FILE__,__LINE__ )
#define JOMOO_FREE( pool , p )pool->free( p )

#define JOMOO_DELETE( pool, ptr )  _Destroy( ptr ), pool->free( ptr )
#define JOMOO_NEW( pool, T,a ) new ((void _FARQ *)pool_malloc( pool, sizeof( T ), __FILE__,__LINE__ ) ) T a
#define JOMOO_FIXED_NEW( pool, T,a ) new ((void _FARQ *)pool_malloc( pool, __FILE__,__LINE__ ) ) T a


#endif // _pool_h_