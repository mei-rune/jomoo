

#include "ComponentLoaderImpl.h"

_micro_kernel_begin

ComponentLoaderImpl::ComponentLoaderImpl (IKernel& context)
{
}

bool ComponentLoaderImpl::load (IKernel&	into,
							const tstring& componentKey,
							int key )
{
	return load( &into, name, key );
}

bool ComponentLoaderImpl::loadAll (IKernel&	into,
							   const tstring& componentKey )
{
	return loadAll( &into, name );
}


bool ComponentLoaderImpl::loadAll (  const tstring& componentKey )
{
	return loadAll( 0, name );
}

bool ComponentLoaderImpl::load ( const tstring& componentKey,
							int key )
{
	return load( 0, name, key );
}


bool ComponentLoaderImpl::loadAll (IKernel*	into,
							   const tstring& componentKey )
{
	bool done = false;  

	if( is_null(into) ) into = &kernel();
	ComponentFactory& svcdb = ComponentFactory::get ();

	ComponentFactory::Iterator svc = svcdb.begin ();
	ComponentFactory::Iterator last = svcdb.end ();
	for ( ; svc != last; ++svc)
	{
		const std::string &svcname = (*svc)->name ();
		if (! svcname.compare(0, name.size (), name) )
		{
			IKernel::key_type key( svcname );
			if ( into->has_component ( key ) )
			{
				svcdb.create (svc, *into, svcname);
				done = true;
			}
		}
	}
	return done;
}

bool ComponentLoaderImpl::load (IKernel*	into,
							const tstring& componentKey,
							int key )
{
	bool done = false;  

	if( is_null(into) ) into = &kernel();
	ComponentFactory& svcdb = ComponentFactory::get ();

	if ( into->has_component ( key ) )
	{
		svcdb.create (name, *into, key );
		done = true;
	}
	return done;
}

const tstring& ComponentLoaderImpl::toString() const
{
	return toString_;
}

BOE_Export_C IComponentLoader* ___make_ComponentLoader( IKernel& context )
{
	return new ComponentLoaderImpl( context );
}

_micro_kernel_end
