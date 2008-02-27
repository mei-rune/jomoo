
#include "Context.H"

//_micro_kernel_begin
//
// ContextImpl::ContextImpl ( ContextKeyManager& km )
//: keymanger_( km )
//{
//}
//
//ContextImpl::~ContextImpl (void)
//{
//	m_components.clear ();
//}
//
//ComponentPtr  ContextImpl::component ( const ContextKey& index )
//{
//	ComponentPtr object( ( Component*) 0 );
//	if ( index < m_components.size () )
//			object = m_components [index];
//	return object;
//}
//
//size_t ContextImpl::size (void) const
//{
//	return m_components.size ();
//}
//
//void ContextImpl::put ( const ContextKey& index, ComponentPtr component)
//{
//	if ( index < m_components.size () )
//			m_components [index] = component;
//}
//
//void ContextImpl::erase ( const ContextKey& index)
//{
//	put (index, ComponentPtr(( Component*)0));
//}
//
//_micro_kernel_end