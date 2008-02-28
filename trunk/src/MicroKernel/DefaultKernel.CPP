

// Include files
#include "DefaultKernel.h"

_micro_kernel_begin

DefaultKernel::DefaultKernel(const tstring& nm
					, IComponentModelFactory&			ComponentModelBuilder
					, IHandlerFactory&				HandlerBuilder)
					: parent_( 0 )
					, name_( nm ) 
					, childs_( )
					, NamingSubSystem_()
					, ComponentModelBuilder_(&ComponentModelBuilder)
					, HandlerBuilder_(&HandlerBuilder)
{
	Initialize();
}

DefaultKernel::DefaultKernel(	const tstring& nm , IKernel& kernel )
					: parent_( &kernel )
					, name_( nm ) 
					, childs_( )
					, NamingSubSystem_()
					, ComponentModelBuilder_( 0 )
					, HandlerBuilder_( 0 )
{
	Initialize();
}

DefaultKernel::~DefaultKernel()
{
}

void DefaultKernel::Initialize()
{
	if( tstring::npos != name_.find( '/') )
		ThrowException1( IllegalArgumentException, BT_TEXT("Ãû×Ö") + name_ + BT_TEXT("ÖÐº¬ÓÐ'/'×Ö·û!") );

	childs_.Initialize( *this );
	NamingSubSystem_.Initialize(*this);
}

const tstring& DefaultKernel::name() const
{
	return name_;
}

IComponent&	DefaultKernel::component ( const key_type& key )
{
	ComponentModelPtr cm = NamingSubSystem().find( key );
	if( is_null( cm ) )
		ThrowException1( NoExistError,key );
	ComponentPtr comp = cm->Handler().Resolve();
	if( is_null( comp ) )
		ThrowException1( NoExistError,key );
	return *comp;
}

const IComponent&	DefaultKernel::component ( const key_type& key ) const
{
	ComponentModelConstPtr cm = NamingSubSystem().find( key );
	if( is_null( cm ) )
		ThrowException1( NoExistError,key );
	ComponentConstPtr comp = cm->Handler().Resolve();
	if( is_null( comp ) )
		ThrowException1( NoExistError,key );
	return *comp;
}

IComponent&	DefaultKernel::component ( const tstring& key_string )
{
	if( key_string.empty() )
		ThrowException2( NoExistError,key_string,0 );

	tstring::size_type slash = key_string.find( '/' );
	if( tstring::npos == slash )
	{
		key_type key( key_string );
		return component( key );
	}
	tstring contextName = key_string.substr( 0 , slash );
	ComponentContextPtr context = this->childs().find( contextName );
	if( is_null( context ) )
	{
		key_type key( key_string );
		return component( key );
	}
	else
	{
		return context->component( key_string.substr( slash + 1) );
	}
}

const IComponent&	DefaultKernel::component ( const tstring& key_string ) const
{
	if( key_string.empty() )
		ThrowException2( NoExistError,key_string,0 );
	tstring::size_type slash = key_string.find( '/' );
	if( tstring::npos == slash )
	{
		key_type key( key_string );
		return component( key );
	}
	tstring contextName = key_string.substr( 0 , slash );
	ComponentContextConstPtr context = this->childs().find( contextName );
	if( is_null( context ) )
	{
		key_type key( key_string );
		return component( key );
	}
	else
	{
		return context->component( key_string.substr( slash + 1) );
	}
}

bool		DefaultKernel::has_component ( const key_type& key ) const
{
	return is_null( NamingSubSystem().find( key ) );
}

bool		DefaultKernel::has_component ( const tstring& key_string ) const
{
	if( key_string.empty() )
		return false;
	key_type key( key_string );
	return has_component( key );
}

size_t		DefaultKernel::size (void) const
{
	return NamingSubSystem().size();
}

void		DefaultKernel::walk( walker_type& walker )
{
	component_walker w( walker );
	NamingSubSystem().walk( w );
}

void		DefaultKernel::walk( walker_type& walker ) const
{
	component_walker w( walker );
	NamingSubSystem().walk( w );
}

DefaultKernel::IContextContainer& DefaultKernel::childs()
{
	return childs_;
}

const DefaultKernel::IContextContainer& DefaultKernel::childs() const
{
	return childs_;
}

IComponentContext* DefaultKernel::parent()
{
	return parent_;
}

const IComponentContext* DefaultKernel::parent() const
{
	return parent_;
}

INamingSubSystem& DefaultKernel::NamingSubSystem()
{
	return NamingSubSystem_;
}

const INamingSubSystem& DefaultKernel::NamingSubSystem() const
{
	return NamingSubSystem_;
}

IComponentModelFactory& DefaultKernel::ComponentModelFactory()
{
	if( !is_null(ComponentModelBuilder_) )
		return *ComponentModelBuilder_;
	if( !is_null(parent_) )
		return parent_->ComponentModelFactory();
	ThrowException( NullException );
}

IHandlerFactory& DefaultKernel::HandlerFactory()
{
	if( !is_null(HandlerBuilder_) )
		return *HandlerBuilder_;
	if( !is_null(parent_) )
		return parent_->HandlerFactory();
	ThrowException( NullException );
}

const tstring&	DefaultKernel::toString() const
{
	return name_;
}


_micro_kernel_end
