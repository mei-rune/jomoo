
#ifndef SEAL_KERNEL_COMPONENT_LOADER_H
# define SEAL_KERNEL_COMPONENT_LOADER_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_MicroKernel.h"
#include "Component.h"
#include "Hazel.Base/Exception.hpp"

_micro_kernel_begin

Hazel_Export_C ComponentLoaderBase* ___make_ComponentLoader( IKernel& context );

class ComponentLoader
{
public:
	ComponentLoader (IKernel& context)
		: m_ptr_( 0 )
	{
		//m_ptr_ = dynamicCast< ComponentLoaderBase*, Component* >
		//	( & (context.component( ComponentLoaderBase::classContextKey() ) ) );
		if ( is_null( m_ptr_ ) )
		{
			throw std::runtime_error( "ComponentLoader" );
			/*
			m_ptr_ =  ___make_ComponentLoader( context );
			if ( is_null( m_ptr_ ) )
				ThrowException1( RuntimeException,",´´½¨ComponentLoaderÊ§°Ü" );
			context.put( ComponentLoaderBase::classContextKey (), m_ptr_ );*/
		}
		toString_ = BT_TEXT( "ComponentLoader" );
	}

    bool load ( IKernel& into, const tstring &name, const IKernel::key_type& key )
	{
		return m_ptr_->load( into, name , key );
	}

 	bool loadAll (IKernel& into, const tstring &name)
	{
		return m_ptr_->loadAll( into, name );
	}

	bool load ( const tstring &name, const IKernel::key_type& key )
	{
		return m_ptr_->load( name , key );
	}

	bool loadAll ( const tstring &name )
	{
		return m_ptr_->loadAll( name );
	}

	const tstring& toString() const
	{
		return toString_;
	}

private:
	IComponentLoader* m_ptr_;
	tstring toString_;
};

_micro_kernel_end

#endif // SEAL_KERNEL_COMPONENT_LOADER_H
