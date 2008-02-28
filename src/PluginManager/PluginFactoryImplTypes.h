#ifndef PLUGINFACTORYIMPLTYPES_H
#define PLUGINFACTORYIMPLTYPES_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "PluginInfo.H"
# include "PluginFactoryImplBase.h"

_seal_begin

template< typename R >
class PluginFactoryImplTypes
{
public:

};

template <>
class PluginFactoryImplTypes<void>
{
public:
};

template< typename T >
class AbstractFactory
{
public:
};

template< >
class AbstractFactory< void >
{
public:
};

_seal_end

#include "PluginFactoryImplTypes0.H"
#include "PluginFactoryImplTypes1.H"
#include "PluginFactoryImplTypes2.H"
#include "PluginFactoryImplTypes3.H"
#include "PluginFactoryImplTypes4.H"
#include "PluginFactoryImplTypes5.H"
#include "PluginFactoryImplTypes6.H"
#include "PluginFactoryImplTypes7.H"
#include "PluginFactoryImplTypes8.H"
#include "PluginFactoryImplTypes9.H"
#include "PluginFactoryImplTypes10.H"
#include "PluginFactoryImplTypes11.H"
#include "PluginFactoryImplTypes12.H"
#include "PluginFactoryImplTypes13.H"
#include "PluginFactoryImplTypes14.H"
#include "PluginFactoryImplTypes15.H"
#include "PluginFactoryImplTypes16.H"




//
//template <class R>
//class PluginFactoryImplTypes<R * (void)>
//{
//public:
//	typedef R Object;
//	class Factory {
//	public:
//		virtual ~Factory (void){}
//		virtual R *create (void) = 0;
//	};
//
//	template <class T> class AutoFactory : public Factory
//	{
//	public:
//		virtual R *create (void){ return new T; }
//	};
//
//	class Info : public PluginInfo
//	{
//	public:
//		Info (IModule& module, const tstring &name, const tstring &tag)
//			: PluginInfo (module, name, tag),
//			m_factory (0)
//		{ }
//
//		~Info (void)
//		{ detach (); }
//
//		R *		create (void)
//		{
//			return factory ()->create ();
//		}
//
//		/// 这个函数据是由插件自已调用注册工厂用的
//		void		attach (Factory *factory)
//		{
//			if ( m_factory)
//				throw PluginFactoryImplBase::FacetoryRegisterError( category(), name() );
//
//			m_factory = factory;
//		}
//
//		void	detach (void)
//		{
//			if( m_factory == 0 )
//				throw PluginFactoryImplBase::FacetoryNoRegisterError( category(), name() );
//
//			delete m_factory;
//			m_factory = 0;
//		}
//
//
//	private:
//		Factory *	factory (void) const
//		{
//			if (! m_factory)
//				module ()->attach ();
//
//			if (! m_factory)
//				noFactory ();
//
//			return m_factory;
//		}
//		Factory		*m_factory;
//	};
//};
//
//template <class R, class T1>
//class PluginFactoryImplTypes<R * (T1)>
//{
//public:
//	typedef R Object;
//	class Factory {
//	public:
//		virtual ~Factory (void){}
//		virtual R *create (T1 a1) = 0;
//	};
//
//	template <class T> class AutoFactory : public Factory
//	{
//	public:
//		virtual R *create (T1 a1){ return new T (a1); }
//	};
//
//	class Info : public PluginInfo
//	{
//	public:
//		Info (IModule& module, const ModuleDescriptor &details, const tstring &tag)
//			: PluginInfo (module, details.token (1), tag),
//			m_factory (0)
//		{  }
//
//		~Info (void)
//		{
//			detach ();
//		}
//
//		R *		create (T1 a1)
//		{
//			return factory ()->create (a1);
//		}
//		void		attach (Factory *factory)
//		{
//			if( m_facetory )
//				throw PluginFactoryImplBase::FacetoryRegisterError( category(), name() );
//			Hazel_ ASSERT (! m_factory);
//			m_factory = factory;
//		}
//
//		virtual void	detach (void)
//		{
//			if( m_factory == 0 )
//				throw PluginFactoryImplBase::FacetoryNoRegisterError( category(), name() );
//
//			delete m_factory;
//			m_factory = 0;
//		}
//	private:
//		Factory *	factory (void) const
//		{
//			if (! m_factory)
//				module ()->attach ();
//
//			if (! m_factory)
//				noFactory ();
//
//			return m_factory;
//		}
//
//		Factory		*m_factory;	
//	};
//};





#endif // PLUGINFACTORYIMPLTYPES_H
