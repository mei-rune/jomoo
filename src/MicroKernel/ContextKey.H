#ifndef Hazel_CONTEXT_KEY_H
# define Hazel_CONTEXT_KEY_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "Hazel.Base/counter_ptr.hpp"
# include "Hazel.Base/string.hpp"
# include <map>

_micro_kernel_begin

class ContextKey
{
public:

	typedef tstring guid_type;

	ContextKey( const guid_type& guid, size_t pos )
		: guid_( guid )
		, position_( pos )
	{
		init();
	}

	ContextKey( const guid_type& guid )
	{
		tstring var;
		StringOps::square_pattern( guid, guid_ , var );
		position_ = ( size_t )string_traits<tchar>::atoi64( var.c_str() );
		init();
	}

	const guid_type& guid() const
	{
		return guid_;
	}

	size_t position() const
	{
		return position_;
	}

	const tstring& toString() const
	{
		if( is_null( toString_ ) )
			return guid_;
		return *toString_;
	}
private:
	DECLARE_NO_COPY_CLASS(ContextKey);

	void init()
	{
		position_ = 0 > position_ ? 0 : position_;
		if( 0 == position_ )
			return ;
		toString_.reset( new tstring( guid_ ));
		*toString_ += "[";
		*toString_ += ::toString( position_  );
		*toString_ += "]";
	}
	guid_type guid_;
	size_t position_;
	std::auto_ptr<tstring> toString_;
};



//class ContextKeyManager
//{
//public:
//
//	enum {
//		KEY_NONE	= 0xffffffff
//	};
//
//	enum
//	{
//		/**
//		* 这是标志表示这个key被定义过，后来又被删除了
//		*/
//		KEY_REMOVED_BIT	= 0x80000000,
//
//		/**
//		* 
//		*/
//		KEY_NOLIFE_BIT	= 0x40000000,
//
//		KEY_MAX		= 0x0fffffff
//	};
//
//	typedef u_int_t key_type;
//
//	virtual ~ContextKeyManager( ){}
//
//	virtual const tstring& label( key_type value ) const = 0;
//
//	virtual key_type	find (const tstring &label) const = 0;
//
//	virtual key_type	allocate (const tstring &label) const = 0;
//
//	virtual key_type	create (const tstring &label) const = 0;
//
//	virtual void	remove (const tstring &label) const = 0;
//};
//
//typedef counter_ptr< ContextKeyManager > ContextKeyManagerPtr;
//
//class ContextKey
//{
//public:
//
//    enum {
//		KEY_NONE	= ContextKeyManager::KEY_NONE
//    };
//
//	operator ContextKeyManager::key_type (void) const;
//    ContextKeyManager::key_type		value (void) const;
//    tstring	label (void) const;
//
//	ContextKey( const ContextKeyManager& manager, const tstring& label );
//	const ContextKeyManager& getKeyManager() const;
//protected:
//	ContextKey ( const ContextKeyManager& manager, ContextKeyManager::key_type value );
//	enum
//	{
//		/**
//		* 这是标志表示这个key被定义过，后来又被删除了
//		*/
//		KEY_REMOVED_BIT	= ContextKeyManager::KEY_REMOVED_BIT,
//
//		/**
//		* 
//		*/
//		KEY_NOLIFE_BIT	= ContextKeyManager::KEY_NOLIFE_BIT,
//
//		KEY_MAX		= ContextKeyManager::KEY_MAX
//	};
//
//    ContextKeyManager::key_type	m_value;
//	const ContextKeyManager& manager_;
//};
//
//
//class ContextKeyDef : public ContextKey
//{
//public:
//    ContextKeyDef ( ContextKeyManager& manager,const std::string &label);
//    ~ContextKeyDef (void);
//
//private:
//    std::string		m_label;	//< The key value.
//};
//
//
//Hazel_Export_C ContextKeyManager* ___createContextKeyManager( void* arg );
//Hazel_Export_C void __freeContextKeyManager( ContextKeyManager* );
//
//
//Hazel_Export_C ContextKeyManager& ___getContextKeyManager( );
//
//inline ContextKeyManagerPtr createContextKeyManager( void* arg )
//{
//	return ContextKeyManagerPtr( ___createContextKeyManager( arg) ,__freeContextKeyManager );
//}
//
//inline ContextKeyManager& getContextKeyManager( )
//{
//	return ___getContextKeyManager();
//}

_micro_kernel_end


#endif // Hazel_CONTEXT_KEY_H
