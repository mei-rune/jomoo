
#include "ContextKey.h"
#include "DebugAids.H"

//#ifdef _MEMORY_DEBUG
//#undef THIS_FILE
//#define new	   DEBUG_NEW  
//#define malloc DEBUG_MALLOC  
//static char THIS_FILE[] = __FILE__;  
//#endif // _MEMORY_DEBUG

//_micro_kernel_begin

//class HazelContextKeyManager : public ContextKeyManager
//{
//public:
//	typedef ContextKeyManager::key_type key_type;
//
//	HazelContextKeyManager();
//
//	const tstring& label( key_type value ) const;
//
//	key_type	find (const tstring &label) const;
//
//	key_type	allocate (const tstring &label) const;
//
//	key_type	create (const tstring &label) const;
//
//	void	remove (const tstring &label) const;
//
//private:
//
//	typedef std::map<std::string, ContextKeyManager::key_type > KeyMap;
//
//    KeyMap &	keymap (void) const
//	{
//		return m_map_;
//	}
//
//    mutable ContextKeyManager::key_type	s_next;
//	mutable KeyMap m_map_;
//};
//
//HazelContextKeyManager::HazelContextKeyManager()
//: s_next( 0 )
//{
//}
//
//const tstring& HazelContextKeyManager::label( HazelContextKeyManager::key_type value ) const
//{
//	HazelContextKeyManager::KeyMap &keys = keymap ();
//    for (HazelContextKeyManager::KeyMap::iterator pos = keys.begin (); pos != keys.end (); ++pos)
//	if ((pos->second & HazelContextKeyManager::KEY_MAX) == value)
//	    return pos->first;
//	static tstring UNDEFINED = "<UNDEFINED>";
//    return UNDEFINED;
//}
//
//HazelContextKeyManager::key_type HazelContextKeyManager::create(const std::string &label)const
//{
//
//    COMPONENT_ASSERT (! label.empty ());
//
//    HazelContextKeyManager::KeyMap &keys = keymap ();
//
//	if (! keys.count (label))
//	{
//
//		COMPONENT_ASSERT (s_next < HazelContextKeyManager::KEY_MAX);
//
//		HazelContextKeyManager::key_type value = s_next++;
//		keys [label] = value;
//		return value;
//	}
//	else
//	{
//
//		HazelContextKeyManager::key_type &value = keys [label];
//		COMPONENT_ASSERT (! (value & HazelContextKeyManager::KEY_NOLIFE_BIT));
//		COMPONENT_ASSERT (value & HazelContextKeyManager::KEY_REMOVED_BIT);
//		value &= ~HazelContextKeyManager::KEY_REMOVED_BIT;
//		return value;
//	}
//}
//
//
//HazelContextKeyManager::key_type	HazelContextKeyManager::find (const tstring &label)const
//{
//	COMPONENT_ASSERT (! label.empty ());
//    HazelContextKeyManager::KeyMap &keys = keymap ();
//    HazelContextKeyManager::KeyMap::iterator pos = keys.find (label);
//    return pos == keys.end () ? HazelContextKeyManager::KEY_NONE : (pos->second & HazelContextKeyManager::KEY_MAX);
//}
//
//HazelContextKeyManager::key_type	HazelContextKeyManager::allocate (const tstring &label)const
//{
//	COMPONENT_ASSERT (! label.empty ());
//	HazelContextKeyManager::KeyMap &keys = keymap ();
//	if (! keys.count (label))
//	{
//		COMPONENT_ASSERT (s_next < HazelContextKeyManager::KEY_MAX);
//		HazelContextKeyManager::key_type value = s_next++;
//		keys [label] = value | HazelContextKeyManager::KEY_NOLIFE_BIT;
//		return value;
//	}
//	else
//	{
//		HazelContextKeyManager::key_type &value = keys [label];
//		COMPONENT_ASSERT (value & HazelContextKeyManager::KEY_NOLIFE_BIT);
//		COMPONENT_ASSERT (! (value & HazelContextKeyManager::KEY_REMOVED_BIT));
//		return value & ~ HazelContextKeyManager::KEY_NOLIFE_BIT;
//	}
//}
//
//void HazelContextKeyManager::remove (const tstring &label)const
//{
//	COMPONENT_ASSERT (! label.empty ());
//    HazelContextKeyManager::KeyMap &keys = keymap ();
//    COMPONENT_ASSERT (keys.count (label));
//    COMPONENT_ASSERT (! (keys [label] & HazelContextKeyManager::KEY_REMOVED_BIT));
//    keys [label] |= HazelContextKeyManager::KEY_REMOVED_BIT;
//}
//
//Hazel_Export_C ContextKeyManager* ___createContextKeyManager( void* arg )
//{
//	return new HazelContextKeyManager;
//}
//
//Hazel_Export_C void __freeContextKeyManager( ContextKeyManager* p )
//{
//	if( p != 0 )
//		delete p;
//}
//
//HazelContextKeyManager gkeymanager_;
//
//Hazel_Export_C ContextKeyManager& ___getContextKeyManager( )
//{
//	return gkeymanager_;
//}
//
//_micro_kernel_end