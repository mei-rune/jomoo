

#include "ComponentContextContainer.h"

_micro_kernel_begin

ComponentContextContainer::ComponentContextContainer()
: kernel_( null_ptr )
, toString_( )
{
}

void ComponentContextContainer::Initialize(IKernel& kernel)
{
	kernel_ = &kernel;
	toString_ = kernel.name() + "[child]";
}

ComponentContextContainer::~ComponentContextContainer()
{
	for( container_type::iterator it = map_.begin()
		; it != map_.end()
		; it ++ )
	{
		//// error
	}
}

void ComponentContextContainer::add( ComponentContextPtr child )
{
	if( is_null( child ) )
		ThrowException ( NullException );
	container_type::iterator it = map_.find( child->name() );
	if( map_.end() != it )
		ThrowException1(	ExistError , child->name() );
	map_.insert( std::make_pair( child->name(), child ) );
}

bool ComponentContextContainer::remove( const tstring& name )
{
	if( is_empty( name) )
		return false;
	container_type::iterator it = map_.find( name );
	if( map_.end() == it )
		return false;
	map_.erase( it );
	//// error
	return true;
}

ComponentContextPtr ComponentContextContainer::find( const tstring& name )
{
	if( is_empty( name) )
		return null_ptr;
	container_type::iterator it = map_.find( name );
	if( map_.end() == it )
		return null_ptr;
	return it->second;
}

IComponentContext::ComponentContextConstPtr ComponentContextContainer::find( const tstring& name ) const
{
	if( is_empty( name) )
		return null_ptr;
	container_type::const_iterator it = map_.find( name );
	if( map_.end() == it )
		return null_ptr;
	return it->second;
}
size_t ComponentContextContainer::size( ) const
{
	return map_.size();
}

void ComponentContextContainer::walk( walker_type& walker )
{
	for( container_type::iterator it = map_.begin()
		; it != map_.end()
		; it ++ )
	{
		walker.on_walk( *(it->second) );
	}
}

void ComponentContextContainer::walk( walker_type& walker ) const
{
	for( container_type::const_iterator it = map_.begin()
		; it != map_.end()
		; it ++ )
	{
		walker.on_walk( *(it->second) );
	}
}

const tstring& ComponentContextContainer::toString() const
{
	return toString_;
}

_micro_kernel_end
