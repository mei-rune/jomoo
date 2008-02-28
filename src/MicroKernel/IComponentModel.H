#ifndef IComponentModel_H
# define IComponentModel_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_MicroKernel.h"
# include "xml/IContentHandler.hpp"
# include "IHandler.h"

_micro_kernel_begin

class IComponentModel : _micro_kernel_xml IContentHandler
{
public:
	typedef IComponent::key_type key_type;

	virtual ~IComponentModel(){}
	virtual IKernel& kernel() = 0;
	virtual const IKernel& kernel() const = 0;
	virtual const key_type& key() const = 0;
	virtual const tstring& type() const = 0;

	virtual IHandler& Handler() = 0;
	virtual const IHandler& Handler() const = 0;
};

typedef IComponentModel* ComponentModelPtr;
typedef const IComponentModel* ComponentModelConstPtr;

class IHandlerFactory
{
public:
	virtual ~IHandlerFactory(){}
    virtual IHandler * create( ComponentModelPtr  ) = 0;
	virtual void release( IHandler * ) = 0; 
};


class IComponentModelFactory
{
public :
	virtual ~IComponentModelFactory(){}
	virtual ComponentModelPtr create( const tstring& type ) = 0;
	virtual void release( ComponentModelPtr ) = 0;
};
_micro_kernel_end

#endif // IComponentModel_H
