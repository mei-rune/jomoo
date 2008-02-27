#ifndef __PLUG_MANAGER_FACTORY2__
#define __PLUG_MANAGER_FACTORY2__

# include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"

#define Hazel_NUM_ARGS	2
#include "PluginFactoryTemplates.h"
#undef Hazel_NUM_ARGS

//
//# include "config.h"
//
//#if !defined (Hazel_LACKS_PRAGMA_ONCE)
//# pragma once
//#endif /* Hazel_LACKS_PRAGMA_ONCE */
//
//// Include files
//# include "config_PluginManager.h"
//# include "PluginFactoryImpl.H"
//# include "MapUniqueIterator.h"
//# include <map>
//
//_seal_begin
//
////////////////////////////////////////////////////////////////////////
//template < typename R , typename T1,typename T2  >
//class PluginFactory< R ( T1,T2 ) >
//{
//public:
//	typedef typename PluginFactoryImpl<R ( T1,T2 )> factory_type;
//	typedef typename factory_type::Iterator Iterator;
//	typedef typename factory_type::ptr_type ptr_type;
//
//	PluginFactory ( PluginManagerPtr manager , const tstring &name )
//		: manager_( manager )
//		, ptr_( dynamicCast< factory_type >( manager_->locateFactory( name ) ) )
//	{
//		if( is_null( ptr_ ) )
//		{
//			ptr.reset( new factory_type( manager_, name ) );
//			manager_->addFactory( dynamicCast< PluginFactoryImplBase , factory_type >( ptr ) );
//		}
//	}
//
//	~PluginFactory ()
//	{
//		manager_->removeFactory( dynamicCast< PluginFactoryImplBase , factory_type >( ptr ) );
//	}
//
//	Iterator begin()
//	{
//		return pfactory_->begin();
//	}
//	
//	Iterator end()
//	{
//		return pfactory_->end();
//	}
//
//	virtual R *		create (const tstring &name , T1 t1,T2 t2 ) const
//	{ return info == pfactory_->end () ? 0 : (*info)->create (t1,t2); }
//	virtual R *		create (Iterator item , T1 t1,T2 t2 ) const
//	{ return create (pfactory_->locate (name), t1,t2); }
//
//	void	installFactory ( IModuleDef& def , const tstring& name,
//		typename factory_type::Factory *factory )
//	{
//		pfactory_->installFactory( def, name , factory );
//	}
//
//	void	uninstallFactory ( IModuleDef& def , const tstring& name )
//	{
//		pfactory_->uninstallFactory( def, name , factory );
//	}
//
//private:
//	PluginManagerPtr manager_;
//	ptr_type pfactory_;
//};
//
//_seal_end


#endif // __PLUG_MANAGER_FACTORY2__