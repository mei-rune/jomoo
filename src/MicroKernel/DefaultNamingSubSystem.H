#ifndef DEFAULT_NAMING_SUB_SYSTEM_H
# define DEFAULT_NAMING_SUB_SYSTEM_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "INamingSubSystem.H"
# include "IKernel.H"
# include <map>

_micro_kernel_begin

class DefaultNamingSubSystem : public INamingSubSystem
{
public:

	typedef IComponentModel::key_type key_type;

	typedef std::vector< ComponentModelPtr > vector_type;
	typedef std::map< key_type::guid_type , vector_type > container_type;

	DefaultNamingSubSystem( );

	virtual ~DefaultNamingSubSystem();

	virtual void Initialize( IKernel& kernel );

	virtual ComponentModelPtr	find ( const key_type& key ) ;
	virtual ComponentModelConstPtr	find ( const key_type& key ) const;

	virtual ComponentModelPtr&			add ( const key_type::guid_type& guid, size_t pos );

	virtual bool			remove ( const key_type& index);

	virtual size_t		size (void) const;
	
	virtual void walk( walker_type& walker );

	virtual void walk( walker_type& walker ) const;

	virtual const tstring& toString() const;

private:

	DECLARE_NO_COPY_CLASS( DefaultNamingSubSystem );

	IKernel* kernel_;

	container_type container_;

	tstring toString_;
};

_micro_kernel_end

#endif // DEFAULT_NAMING_SUB_SYSTEM_H
