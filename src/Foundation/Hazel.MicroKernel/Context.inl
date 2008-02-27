//
//
//_micro_kernel_begin
//
//inline  Context::Context ( ContextKeyManager& km
//	    , const tstring& name
//		, Context *parent
//		, std::auto_ptr< ContextImplBase >& impl
//		)
//: m_parent_(parent)
//, m_components_( impl )
//, km_( km )
//, name_( name )
//, toString_( name + "/Context" )
//{
//	if (m_parent_)
//		m_parent_->addChild (this);
//
//	if( m_components_.get() == 0 )
//		m_components_.reset( new ContextImpl( km ) );
//}
//
//inline  Context::~Context (void)
//{
//	if (m_parent_)
//		m_parent_->detachChild (this);
//	m_children_.clear();
//}
//
//
//inline  void Context::addChild (Context *child)
//{
//	m_children_.push_back (child);
//}
//
//inline  void Context::detachChild (Context *child)
//{
//	Children::iterator pos
//		= std::find (m_children_.begin (), m_children_.end (), child);
//	m_children_.erase (pos);
//}
//inline  Context * Context::root (void)
//{
//	Context *c = this;
//	while (c->m_parent_)
//		c = c->m_parent_;
//
//	return (c);
//}
//
//inline  const Context * Context::root (void) const
//{
//	const Context *c = this;
//	while (c->m_parent_)
//		c = c->m_parent_;
//	return (c);
//}
//
//inline  Context * Context::parent (void)
//{
//	return m_parent_;
//}
//
//inline  const Context * Context::parent (void) const
//{
//	return m_parent_;
//}
//
//inline  Context * Context::child (size_t index)
//{
//	return m_children_ [index];
//}
//
//inline  const Context * Context::child (size_t index) const
//{
//	return m_children_ [index];
//}
//
//inline  size_t Context::children (void) const
//{
//	return m_children_.size ();
//}
//
//inline  ContextKeyManager& Context::manager()
//{
//	return km_;
//}
//
//inline const tstring& Context::server() const
//{
//	return name_;
//}
//
//inline  ComponentPtr  Context::component ( const ContextKey& index )
//{
//	ComponentPtr object( ( Component*) 0 );
//	for (const Context *c = this; c && is_null( object ); c = c->parent ())
//	{
//		object = c->m_components_->component( index );
//		if ( !is_null( object ) )
//			break;
//	}
//
//	return object;
//}
//
//
//inline ComponentPtr  Context::component (const tstring &index)
//{
//	ContextKey key( manager(), index );
//	return component( key );
//}
//
//inline ComponentPtr Context::component ( const ContextKey& index, Context* &context)
//{
//	ComponentPtr	object( ( Component*)0 );
//	context = this;
//
//	for ( ; context && is_null( object ); context = context->parent ())
//	{
//		object =context->m_components_->component( index );
//		if ( !is_null( object ) )
//			return object;
//	}
//	context = 0;
//	return object;
//}
//
//inline ComponentPtr Context::component (const tstring &index, Context* &context)
//{
//	ContextKey key( manager(), index );
//	return component( key ,context );
//}
//
//inline ComponentPtr Context::componentLocal ( const ContextKey& index )
//{
//	return m_components_->component( index );
//}
//
//inline ComponentPtr Context::componentLocal (const tstring &index )
//{
//	ContextKey key( manager(), index );
//	return componentLocal( key );
//}
//
//inline  void Context::put ( const ContextKey& index, ComponentPtr component)
//{
//	m_components_->put( index , component );
//}
//
//inline  void Context::put ( const tstring& index, ComponentPtr component)
//{
//	ContextKey key( manager(), index );
//	put( key ,component );
//}
//
//inline  void Context::erase ( const ContextKey& index)
//{
//	m_components_->erase (index );
//}
//
//inline  void Context::erase ( const tstring& index)
//{
//	ContextKey key( manager(), index );
//	erase( key );
//}
//
//inline  size_t Context::size (void) const
//{
//	return m_components_->size ();
//}
//
//inline const tstring& Context::toString() const
//{
//	return toString_;
//}
//
//_micro_kernel_end