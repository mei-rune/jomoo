//
//
//_micro_kernel_begin
//
//inline ContextKey::ContextKey ( const ContextKeyManager& manager, ContextKeyManager::key_type value )
//: manager_( manager )
//, m_value (value)
//{
//}
//
//inline ContextKey::ContextKey( const ContextKeyManager& manager,const tstring& label )
//: manager_( manager )
//, m_value ( manager.find( label ) )
//{
//}
//
//inline tstring ContextKey::label (void) const
//{
//	return manager_.label( m_value );
//}
//
//inline ContextKey::operator ContextKeyManager::key_type (void) const
//{
//	return m_value;
//}
//
//inline ContextKeyManager::key_type ContextKey::value (void) const
//{
//	return m_value;
//}
//
//inline const ContextKeyManager& ContextKey::getKeyManager() const
//{
//	return manager_;
//}
//
//inline ContextKeyDef::ContextKeyDef ( ContextKeyManager& manager,const std::string &label)
//    : ContextKey ( manager , manager.create( label ) )
//	, m_label (label)
//{
//}
//
//inline ContextKeyDef::~ContextKeyDef (void)
//{ 
//	manager_.remove (m_label);
//}
//
//
//
//_micro_kernel_end