
#include "MemoryManager.H"
#include "SystemPool.h"
#include "FixedPool.H"
#include "jomoo/threading.hpp"
#include <map>

_jomoo_memory_begin

/**
 * @Brief 内存池管理器
 */
class POOL_Manager : public pool_mgr
{
public:

	typedef std::map< tstring,fixed_pool_ptr > container_type;

	static POOL_Manager& get()
	{
		static POOL_Manager pm;
		return pm;
	}

	pool_ptr getPool( )
	{
		return &SystemPool::get();
	}

	
	pool_ptr createPool( const tstring& name , size_t pages )
	{
		return &SystemPool::get();
	}
		
	
	fixed_pool_ptr createPool( const tstring& name, size_t number,size_t size )
	{
		JOMOO_GUARD( lock, mutex_ );
		container_type::iterator it = loop_pools_.find( name );
		if( it != loop_pools_.end() )
			return it->second;
		FixedPool* pool = new FixedPool( name , number, size );
		loop_pools_.insert( std::make_pair( name , pool ));
		return pool;
	}
	
	
	pool_ptr findPool( const tstring& name  )
	{
		return &SystemPool::get();
	}

	fixed_pool_ptr findPool( const tstring& name, size_t chunk_size )
	{
		JOMOO_GUARD( lock, mutex_ );
		container_type::iterator it = loop_pools_.find( name );
		if( it != loop_pools_.end() && it->second ->chunk_size() >= chunk_size )
			return it->second;
		return 0;
	}

	
	void dump( tostream& Target ) const
	{
		Target << _T("<MemoryPool>");
		SystemPool::get().dump( Target );

		JOMOO_GUARD( lock, mutex_ );
		for( container_type::const_iterator it = loop_pools_.begin()
			; it != loop_pools_.end()
			; it ++ )
			it->second->dump( Target );
		Target << _T("</MemoryPool>");
	}

	
	const tstring& toString() const
	{
		return toString_;
	}

private:

	POOL_Manager()
		: toString_( _T("POOL_Manager") )
	{
	}

	JOMOO_MUTEX_MUTABLE( mutex_ );

	container_type loop_pools_;
	tstring toString_;
};

_jomoo_memory_end

/**
 * 取得默认的内存池
 * @return 返回默认的内存池的指针
 */
JOMOO_Export_C _jomoo_memory pool_mgr* ___getPoolManager()
{
	return & _jomoo_memory POOL_Manager::get();
}

/**
 * 打印出内存池管理器的状态
 * @param[ in ] Target 输出流
 */
JOMOO_Export_C void  ___dumpPoolManager( tostream& Target )
{
	_jomoo_memory POOL_Manager::get().dump( Target );
}

/**
 * 取得默认的内存池
 * @return 返回默认的内存池的指针
 */
JOMOO_Export_C _jomoo_memory pool_ptr ___getPool( )
{
	return _jomoo_memory POOL_Manager::get().getPool();
}

/**
 * 创建一个内存池
 * @param[ in ] name 内存池名称
 * @param[ in ] pages 指定内存池预分配内存块的大小
 * @return 返回内存池的指针
 */
JOMOO_Export_C _jomoo_memory pool_ptr ___createPool( const tstring& name , size_t pages )
{
	return _jomoo_memory POOL_Manager::get().createPool( name , pages );
}
	
/**
 * 创建一个固定大小内存池
 * @param[ in ] name 内存池名称
 * @param[ in ] number 指定内存池预分配内存块的数目
 * @param[ in ] size 指定内存池每个预分配内存块的大小
 * @return 返回内存池的指针
 */
JOMOO_Export_C _jomoo_memory fixed_pool_ptr ___createLoopPool( const tstring& name, size_t number,size_t size )
{
	return _jomoo_memory POOL_Manager::get().createPool( name , number, size );
}

/**
 * 查找一个内存池
 * @param[ in ] name 内存池名称
 * @return 返回内存池的指针
 */
JOMOO_Export_C _jomoo_memory pool_ptr ___findPool( const tstring& name  )
{
	return _jomoo_memory POOL_Manager::get().findPool( name );
}

/**
 * 查找一个固定大小内存池
 * @param[ in ] name 内存池名称
 * @return 返回内存池的指针
 */
JOMOO_Export_C _jomoo_memory fixed_pool_ptr ___findLoopPool( const tstring& name, size_t chunk_size)
{
	return _jomoo_memory POOL_Manager::get().findPool ( name ,chunk_size );
}

JOMOO_Export_C void* ___system_malloc (size_t nbytes , const char* file, size_t line )
{
	return _jomoo_memory POOL_Manager::get().getPool()->malloc( nbytes, file, line );
}

JOMOO_Export_C void ___system_free (void* block )
{
	return _jomoo_memory POOL_Manager::get().getPool()->free( block );
}
