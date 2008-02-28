#ifndef SEAL_COMPONENTCONTEXTCONTAINER_H
# define SEAL_COMPONENTCONTEXTCONTAINER_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "Hazel.Base/counter_ptr.hpp"
# include "Hazel.Base/string.hpp"
# include "Hazel.Base/exception.hpp"
# include "Hazel.Base/collections/enumerator.h"
# include "Hazel.Base/is_empty.h"
# include "IKernel.h"

_micro_kernel_begin


class ComponentContextContainer : public IComponentContext::IContextContainer
{
public:
	typedef std::map< tstring, ComponentContextPtr > container_type;

	ComponentContextContainer();
	virtual ~ComponentContextContainer();

	virtual void Initialize(IKernel& kernel);

	virtual void add( ComponentContextPtr child );
	virtual bool remove( const tstring& name );
	virtual IComponentContext::ComponentContextPtr find( const tstring& name );
	virtual IComponentContext::ComponentContextConstPtr find( const tstring& name ) const;

	virtual size_t size( ) const;
	virtual void walk( walker_type& walker );
	virtual void walk( walker_type& walker ) const;
	virtual const tstring& toString() const;
private:
	DECLARE_NO_COPY_CLASS(ComponentContextContainer);

	IKernel* kernel_;
	tstring toString_;
	container_type map_;
};

_micro_kernel_end

#endif // SEAL_COMPONENTCONTEXTCONTAINER_H
