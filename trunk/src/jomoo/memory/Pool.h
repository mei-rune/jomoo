

/**
* -*- C++ -*-
* -------------------------------------------------------------------------------
* - ��q�Шr �q�Шr						  pool.h,v 1.0 2008/03/25 10:52:54
*  �u�������� �q�q �Шr
* ���������| �t------
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

MakeException( BadMemoryException , "�����ڴ��ʧ��" );

/**
 * @Brief �ڴ�ؽӿ�
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
	 * ����ָ����С���ڴ��
	 * @param[ in ] nbytes �ڴ��Ĵ�С
	 * @param[ in ] file   �������ڵ��ļ���
	 * @param[ in ] line   �������ڵ��ļ����к�
	 * @return �����ڴ��ĵ�ַ
	 * @remark �����ܻ�ʧ�ܲ��ӳ��ڴ�����쳣
	 */
	virtual void* malloc (size_t nbytes , const char* file=0, size_t line=-1 ) = 0;

	/**
	 * �ͷ��ڴ��
	 * @param[ in ] block �ڴ��ĵ�ַ
	 * @remark �����ܻ�ʧ�ܲ��ӳ��ڴ�����쳣
	 */
	virtual void free (void* block ) = 0;

	/**
	 * ��ӡ���ڴ�ص�״̬
	 * @param[ in ] Target �����
	 */
	virtual void dump( std::ostream& Target ) const = 0;

	/**
	 * �ڴ�ص�����
	 * @return ��������
	 */
	virtual const tstring& toString() const = 0;
};

/**
 * @Brief �̶���С�ڴ�ؽӿ�
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
	 * ����ָ����С���ڴ��
	 * @param[ in ] file   �������ڵ��ļ���
	 * @param[ in ] line   �������ڵ��ļ����к�
	 * @return �����ڴ��ĵ�ַ
	 * @remark �����ܻ�ʧ�ܲ��ӳ��ڴ�����쳣����û��ָ���ڴ���С
	 */
	virtual void* malloc( const char* file=0, size_t line=-1 ) = 0;

	/**
	 * �ͷ��ڴ��
	 * @param[ in ] block �ڴ��ĵ�ַ
	 * @remark �����ܻ�ʧ�ܲ��ӳ��ڴ�����쳣
	 */
	virtual void  free( void* block ) = 0;

	/**
	 * ȡ��ÿ���ڴ��Ĵ�С
	 * @return ����ÿ���ڴ��Ĵ�С
	 */
	virtual size_t chunk_size() const = 0;

	/**
	 * ��ӡ���ڴ�ص�״̬
	 * @param[ in ] Target �����
	 */
	virtual void dump( std::ostream& Target ) const = 0;

	/**
	 * �ڴ�ص�����
	 * @return ��������
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
 * new "placement" ���ڴ�ش���ϵͳ�ڴ������
 * @param[ in ] size     ������Ҫ�Ĵ�С
 * @param[ in ] pool     �û��ڴ��
 * @return ������ڴ��
 */
inline void * operator new(size_t size , _memory pool_ptr pools)
{
   return pools->malloc( size );
}

/**
 * delete "placement" ���ڴ�ش���ϵͳ�ڴ������
 * @param[ in ] chunk    �ڴ��
 * @param[ in ] pool     �û��ڴ��
 */
inline void   operator delete(void * chunk , _memory pool_ptr pools)
{
   pools->free(chunk);
}

/**
 * new "placement" �ù̶��ڴ�ش���ϵͳ�ڴ������
 * @param[ in ] size     ������Ҫ�Ĵ�С
 * @param[ in ] pool     �û��ڴ��
 * @return ������ڴ��
 */
inline void * operator new(size_t size , _memory fixed_pool_ptr pools)
{
   ASSERT( size <= pools->chunk_size() );
   return pools->malloc();
}

/**
 * delete "placement" �ù̶��ڴ�ش���ϵͳ�ڴ������
 * @param[ in ] chunk    �ڴ��
 * @param[ in ] pool     �û��ڴ��
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