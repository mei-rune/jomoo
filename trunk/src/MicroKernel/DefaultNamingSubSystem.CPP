
// Include files
# include "DefaultNamingSubSystem.H"

_micro_kernel_begin

DefaultNamingSubSystem::DefaultNamingSubSystem( )
: kernel_( null_ptr )
, toString_( )
{
}

void DefaultNamingSubSystem::Initialize( IKernel& kernel )
{
	kernel_ = &kernel;
	toString_ = kernel.toString() + BT_TEXT("[NamingSubSystem]");
}

DefaultNamingSubSystem::~DefaultNamingSubSystem()
{
	for( container_type::iterator it = container_.begin()
		; it != container_.end()
		; it ++ )
	{
		for( vector_type::iterator vit = it->second.begin()
			; vit != it->second.end()
			; vit ++ )
		{
			if(!is_null(*vit))
			{
				kernel_->ComponentModelFactory().release( *vit );
			}
		}
		it->second.clear();
	}
	container_.clear();
}

ComponentModelPtr	DefaultNamingSubSystem::find ( const key_type& key )
{
	container_type::iterator it = container_.find( key.guid() );
	if( it == container_.end() )
		return null_ptr;
	if( it->second.size() <= key.position() )
		return null_ptr;
	return it->second[ key.position() ];
}

ComponentModelConstPtr	DefaultNamingSubSystem::find ( const key_type& key ) const
{
	container_type::const_iterator it = container_.find( key.guid() );
	if( it == container_.end() )
		return null_ptr;
	if( it->second.size() <= key.position() )
		return null_ptr;
	return it->second[ key.position() ];
}

ComponentModelPtr&		DefaultNamingSubSystem::add ( const key_type::guid_type& guid, size_t position )
{
	vector_type& v = container_[ guid ];
	if( v.size() <= position )
		v.resize( position + 1 , null_ptr);
	if( !is_null( v[position] ) )
		ThrowException3( NamingSubSystemException , guid, position, BT_TEXT("已经有一个了") );
	return v[position];
}

bool		DefaultNamingSubSystem::remove ( const key_type& key )
{
	container_type::iterator it = container_.find( key.guid() );
	if( it == container_.end() )
		return false;
	if( it->second.size() <= key.position() )
		return false;
	ComponentModelPtr ptr = it->second[ key.position() ];
	if( is_null(ptr) )
		return false;
	kernel_->ComponentModelFactory().release( ptr );
	return true;
}

size_t		DefaultNamingSubSystem::size (void) const
{
	return container_.size();
}
	
void DefaultNamingSubSystem::walk( walker_type& walker )
{
	for( container_type::iterator it = container_.begin()
		; it != container_.end()
		; it ++ )
	{
		for( vector_type::iterator vit = it->second.begin()
			; vit != it->second.end()
			; vit ++ )
		{
			if(!is_null(*vit))
			walker.on_walk( **vit );
		}
	}
}

void DefaultNamingSubSystem::walk( walker_type& walker ) const
{
	for( container_type::const_iterator it = container_.begin()
		; it != container_.end()
		; it ++ )
	{
		for( vector_type::const_iterator vit = it->second.begin()
			; vit != it->second.end()
			; vit ++ )
		{
			if(!is_null(*vit))
			walker.on_walk( **vit );
		}
	}
}

const tstring& DefaultNamingSubSystem::toString() const
{
	return toString_;
}
_micro_kernel_end