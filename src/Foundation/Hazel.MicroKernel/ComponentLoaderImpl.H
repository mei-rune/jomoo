
#ifndef COMPONENTLOADERIMPL_H
#define COMPONENTLOADERIMPL_H

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

// Include files
#include "config_MicroKernel.h"
#include "IComponentLoader.h"

_micro_kernel_begin

class ComponentLoaderImpl : public IComponentLoader
{
public:
	ComponentLoaderImpl (IKernel& context, int posKey );

    bool load ( IKernel& into, const tstring &componentKey, int key );
 	
	bool loadAll (IKernel& into, const tstring &componentKey);

	bool load ( const tstring &componentKey, int key );
	
	bool loadAll ( const tstring &componentKey );
	
	const tstring& toString() const;

private:
    bool load ( IKernel* into, const tstring &name, const IKernel::key_type& key );
 	bool loadAll (IKernel* into, const tstring &name);

	int posKey_;
	tstring toString_;
};

_micro_kernel_end

#endif // COMPONENTLOADERIMPL_H