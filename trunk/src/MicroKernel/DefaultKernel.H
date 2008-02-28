
#ifndef _DefaultKernel_H_
#define _DefaultKernel_H_

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "IKernel.H"
# include "ComponentContextContainer.H"
# include "DefaultNamingSubSystem.H"

/**
 */
_micro_kernel_begin

class DefaultKernel : public IKernel
{
public:
	DefaultKernel(	const tstring& nm
				, IComponentModelFactory&			ComponentModelBuilder
				, IHandlerFactory&				HandlerBuilder );
	DefaultKernel(	const tstring& nm , IKernel& kernel );
	virtual ~DefaultKernel();

	virtual const tstring& name() const;

	virtual IComponent&	component ( const key_type& key );
	virtual const IComponent&	component ( const key_type& key ) const;
	virtual IComponent&	component ( const tstring& key_string );
	virtual const IComponent&	component ( const tstring& key_string ) const;
	virtual bool		has_component ( const key_type& key ) const;
	virtual bool		has_component ( const tstring& key_string ) const;
	virtual size_t			size (void) const;
	
	class component_walker : public INamingSubSystem::walker_type
	{
	public:
		component_walker( IComponentContext::walker_type& walker )
			: walker_( walker )
		{
		}
		void on_walk( value_type& value )
		{
			ComponentPtr comp = value.Handler().Resolve();
			if( !is_null( comp ) )
				walker_.on_walk( *comp );
		}
		void on_walk( const value_type& value )
		{
			ComponentConstPtr comp = value.Handler().Resolve();
			if( !is_null( comp ) )
				walker_.on_walk( *comp );
		}
	private:
		IComponentContext::walker_type& walker_;
	};
	virtual void walk( walker_type& walker );
	virtual void walk( walker_type& walker ) const;

	virtual IContextContainer& childs();
	virtual const IContextContainer& childs() const;
	virtual IComponentContext* parent();
	virtual const IComponentContext* parent() const;

	virtual INamingSubSystem& NamingSubSystem();
	virtual const INamingSubSystem& NamingSubSystem() const;
	virtual IComponentModelFactory& ComponentModelFactory();
	virtual IHandlerFactory& HandlerFactory();

	virtual const tstring&	toString() const;
private:
	DECLARE_NO_COPY_CLASS( DefaultKernel );

	void Initialize();

	IKernel* parent_;

	tstring name_;
	ComponentContextContainer childs_;

	DefaultNamingSubSystem			NamingSubSystem_;
	IComponentModelFactory*			ComponentModelBuilder_;
	IHandlerFactory*				HandlerBuilder_;
};

_micro_kernel_end

#endif // _DefaultKernel_H_