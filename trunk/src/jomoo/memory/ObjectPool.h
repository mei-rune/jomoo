#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include "config_Memory.H"
# include "../string.hpp"
# include "MemoryManager.H"
# include "../Collections/ThreadSafePtrQueue.HPP"

_jomoo_memory_begin

template< typename Object >
struct POOL_CHUNK LIST_INTERFACE( POOL_CHUNK )
{

	typedef Object value_type;

	POOL_CHUNK()
		: pointee_( 0 )
		, magic_( pool_magic_v )
	{
	}
	int32_t magic_;

	LIST_DEFINE( POOL_CHUNK );
	Object* pointee_;
};


template< class Object , size_t CHUNK_HEAD_SIZE, size_t CHUNK_SIZE >
class ObjectCreationDefault //: public ObjectCreationPolicyBase<Object>
{
public:
	static Object* Construct( void* p )
	{
		Object* chunk = (Object*)p;
		chunk->magic_ = pool_magic_v;
		//new ((void _FARQ *)_Ptr) Object( );
		chunk->pointee_ = new ((void*)((( char*)p) + CHUNK_HEAD_SIZE)) typename Object::value_type ();
		return chunk;
	}
	static void Destroy(Object* pObj )
	{
		JOMOO_Destroy( pObj->pointee_ );
	}

	static Object* Construct( fixed_pool_ptr pools )
	{
		//ASSERT( pools->chunk_size() > CHUNK_SIZE )
		return Construct( JOMOO_FIXED_MALLOC( pools ) );
		//return JOMOO_FIXED_NEW(  pools , T, () );
	}

	static void Destroy(Object* pObj, fixed_pool_ptr pools )
	{
		Destroy( pObj );
		JOMOO_FREE( pools,pObj );
	}


	static Object* Construct( pool_ptr pools )
	{
		return Construct( JOMOO_MALLOC( pools , CHUNK_SIZE ) );
		//return JOMOO_NEW(  pools , T, () );
	}

	static void Destroy(Object* pObj, pool_ptr pools )
	{
		Destroy( pObj );
		JOMOO_FREE( pools,pObj );
	}
};


template<class Object, size_t CHUNK_HEAD_SIZE, size_t CHUNK_SIZE >
class ObjectNullCreation //: public ObjectCreationPolicyBase<Object>
{
public:
	static Object* Construct( void* p )
	{
		return 0;
	}

	static void Destroy(Object* pObj )
	{
	}

	static Object* Construct( fixed_pool_ptr pools )
	{
		return 0;
	}

	static void Destroy(Object* pObj, fixed_pool_ptr pools )
	{
	}

	static Object* Construct( pool_ptr pools )
	{
		return 0;
	}

	static void Destroy(Object* pObj, pool_ptr pools )
	{
	}
};

inline bool assert_chunk_size( const pool_ptr, size_t size )
{
	return true;
}

inline bool assert_chunk_size( const fixed_pool_ptr p, size_t size )
{
	if( NULL == p )
		return true;
	return (p->chunk_size() >= size) ;
}

template< class Object >
class ObjectOnError //: public ObjectCreationPolicyBase<Object>
{
public:
	static void onError()
	{
	}
};

template< typename Object 
, typename POOL = fixed_pool
, typename STORAGE = POOL_CHUNK< Object >
, template< typename,size_t,size_t > class CREATIONPOLICY = ObjectCreationDefault
, template< typename > class ERRORPOLICY = ObjectOnError >
class Pool_T
{
public:

	typedef STORAGE storage_type;
	typedef ThreadSafePtrQueue< storage_type > container_type;
	typedef typename POOL::ptr_type pool_ptr_type;

	enum
	{
		CHUNK_HEAD_SIZE = JOMOO_LCD_DEF( sizeof( storage_type ) , JOMOO_TM )
	};
	enum
	{
		CHUNK_SIZE = JOMOO_LCD_DEF( CHUNK_HEAD_SIZE + sizeof( Object ) , JOMOO_TM )
	};

	typedef CREATIONPOLICY< storage_type ,CHUNK_HEAD_SIZE , CHUNK_SIZE > CreationPolicy;
	typedef ERRORPOLICY< Object > ErrorPolicy;

	Pool_T( pool_ptr_type pools , const tstring& name )
		: pools_( pools )
		, toString_( name )
	{
		if( toString_.empty() )
			toString_ = _T("Pool_T[");
		else
			toString_ += _T("[");
		toString_ += ::toString( CHUNK_SIZE );
		toString_ += _T("]");
		ASSERT( assert_chunk_size( pools , CHUNK_SIZE ) );

	}

	virtual ~Pool_T()
	{
		destroy();
	}

	inline Object*   malloc()
	{ 
		storage_type* p = m_oFree.pop();
		if( NULL != p )
			return p->pointee_;
		p = CreationPolicy::Construct( pools_ );

		if( NULL == p )
			ErrorPolicy::onError();
			//ThrowException1( BadMemoryException, lastError() );
		return p->pointee_;
	}

	inline void free( Object * obj)
	{
		storage_type* p = ( storage_type* ) ( ( (char*)obj ) - CHUNK_HEAD_SIZE );
#ifdef FIXED_POOL_ASSERT
	ASSERT( p->magic_ == pool_magic_v );
#endif
		m_oFree.push( p );
	}

	void        destroy()
	{
		destroy_i();
	}

	const tstring& toString()
	{
		return toString_;
	}

protected:
	void        destroy_i()
	{
		for( storage_type* p = m_oFree.pop(); NULL != p ; p = m_oFree.pop() )
		{
			CreationPolicy::Destroy( p, pools_ );
		}
	}
	container_type m_oFree;
	pool_ptr_type pools_;
	tstring toString_;
};


template< typename Object
, typename POOL = pool
, template< typename,size_t,size_t > class CREATIONPOLICY = ObjectCreationDefault >
class Fixed_Pool_T : public Pool_T< Object ,POOL,POOL_CHUNK< Object >, ObjectNullCreation >
{
public:

	typedef CREATIONPOLICY< storage_type ,CHUNK_HEAD_SIZE , CHUNK_SIZE > CreationPolicy;
	//typedef typename POOL::ptr_type pool_ptr_type;

	Fixed_Pool_T( pool_ptr_type pools , size_t number , const tstring& name )
		: Pool_T< Object ,POOL,POOL_CHUNK< Object >,ObjectNullCreation >( pools , name.empty() ? "Fixed_Pool_T": name )
		, number_( number )
	{

		//toString_ = "Fixed_Pool_T[";
		//toString_ += ::toString( number_ );
		//toString_ += ":";
		//toString_ += ::toString( CHUNK_SIZE );
		//toString_ += "]";

		lpvAddr_ = JOMOO_MALLOC( pools_, CHUNK_SIZE * number_ );

		if( lpvAddr_ == 0 )
			ThrowException1( BadMemoryException, lastError() );

		for( size_t i = 0; i < number_ ; i ++ )
		{
			////storage_type* chunk = (storage_type*)();
			////chunk->magic_ = pool_magic_v;
			////chunk->pointee_ = ;
			storage_type* chunk = CreationPolicy::Construct( ( char*)lpvAddr_ + i * CHUNK_SIZE );
			if( chunk == 0 )
				ThrowException1( BadMemoryException, _T("ππ‘Ï¥ÌŒÛ!") );
				
			m_oFree.push( chunk );
		}



	}

	~Fixed_Pool_T()
	{
		destroy();
	}

	void        destroy()
	{
		size_t s = destroy_i_();
		if( number_ == s )
		{
			JOMOO_FREE( pools_, lpvAddr_ );
		}
		else
		{
			ASSERT( false );
		}
	}

protected:



	size_t         destroy_i_()
	{
		size_t r = 0;
		for( storage_type* p = m_oFree.pop(); NULL != p ; p = m_oFree.pop() )
		{
			CreationPolicy::Destroy( p );
			r++;
		}
		return r;
	}
private:
	void* lpvAddr_;
	const size_t number_;
};


_jomoo_memory_end

#endif // OBJECTPOOL_H