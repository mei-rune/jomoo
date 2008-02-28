

/**
* -*- C++ -*-
* Factory.h,v 1.0 2004/09/08 10:27:54
*/

#ifndef _Factory_H_
#define _Factory_H_

#include "config.h"

#if !defined (BOE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* BOE_LACKS_PRAGMA_ONCE */

#include <map>


_bt_begin

namespace detail
{

	template <typename IdentifierType, class AbstractProduct>
	struct DefaultFactoryError
	{        
		static AbstractProduct* OnUnknownType(IdentifierType)
		{
			return 0;
		}
	};

};

//#ifndef FACTORY_INC_
//#define FACTORY_INC_

//#ifdef Delete
//
//#pragma push_macro("Delete")
//#undef Delete
//#include "loki/LokiTypeInfo.h"
//#include "loki/AssocVector.h"
//#pragma pop_macro("Delete")
//
//#else
//
//#include "loki/LokiTypeInfo.h"
//#include "loki/AssocVector.h"
//
//#endif


#include <exception>


    //template <typename IdentifierType, class AbstractProduct>
    //struct DefaultFactoryError
    //{
    //    struct Exception : public std::exception
    //    {
    //        const char* what() const throw() { return "Unknown Type"; }
    //    };
    //    
    //    static AbstractProduct* OnUnknownType(IdentifierType)
    //    {
    //        throw Exception();
    //    }
    //};

////////////////////////////////////////////////////////////////////////////////
// class template Factory
// Implements a generic object factory
////////////////////////////////////////////////////////////////////////////////

    template
    <
        class AbstractProduct, 
        typename IdentifierType,
        typename ProductCreator = AbstractProduct* (*)(),
        template<typename, class>
		class FactoryErrorPolicy = detail:: DefaultFactoryError
    >
    class Factory 
        : public FactoryErrorPolicy<IdentifierType, AbstractProduct>
    {
    public:
		Factory( const char* name = "Factory" )
			: name_( name )
		{
		}
        bool Register(const IdentifierType& id, ProductCreator creator)
        {
            return associations_.insert(
                IdToProductMap::value_type(id, creator)).second;
        }
        
        bool Unregister(const IdentifierType& id)
        {
            return associations_.erase(id) == 1;
        }
        
        AbstractProduct* CreateObject(const IdentifierType& id) const
        {
			typename IdToProductMap::const_iterator i = associations_.find(id);
            if (i != associations_.end())
            {
                return (i->second)();
            }
            return OnUnknownType(id);
        }
        
		const char* name( ) const
		{
			return name_;
		}

    private:
		typedef std::map<IdentifierType, ProductCreator> IdToProductMap;
        IdToProductMap associations_;

		const char* name_;
    };

////////////////////////////////////////////////////////////////////////////////
// class template CloneFactory
// Implements a generic cloning factory
////////////////////////////////////////////////////////////////////////////////

  //  template
  //  <
  //      class AbstractProduct, 
  //      class ProductCreator = 
  //          AbstractProduct* (*)(const AbstractProduct*),
  //      template<typename, class>
  //          class FactoryErrorPolicy = DefaultFactoryError
  //  >
  //  class CloneFactory
  //      : public FactoryErrorPolicy<TypeInfo, AbstractProduct>
  //  {
  //  public:
		//CloneFactory( const char* name = "CloneFactory" )
		//	: name_( name )
		//{
		//}

  //      bool Register(const TypeInfo& ti, ProductCreator creator)
  //      {
  //          return associations_.insert(
  //              IdToProductMap::value_type(ti, creator)).second;
  //      }
  //      
  //      bool Unregister(const TypeInfo& id)
  //      {
  //          return associations_.erase(id) == 1;
  //      }
  //      
  //      AbstractProduct* CreateObject(const AbstractProduct* model)
  //      {
  //          if (model == 0) return 0;
  //          
  //          typename IdToProductMap::iterator i = 
  //              associations_.find(typeid(*model));
  //          if (i != associations_.end())
  //          {
  //              return (i->second)(model);
  //          }
  //          return OnUnknownType(typeid(*model));
  //      }
  //      	
		//const char* name( ) const
		//{
		//	return name_;
		//}

  //  private:
		//typedef std::map<TypeInfo, ProductCreator> IdToProductMap;
  //      IdToProductMap associations_;

		//const char* name_;

  //  };



	template <typename IdentifierType, typename ParameterType, class AbstractProduct>
    struct FactoryError
    {
        struct Exception : public std::exception
        {
            const char* what() const throw() { return "Unknown Type"; }
        };
        
        static AbstractProduct* OnUnknownType(IdentifierType,ParameterType)
        {
            throw Exception();
        }
    };

    template
    <
        class AbstractProduct, 
        typename IdentifierType,
		typename ParameterType,
        typename ProductCreator = AbstractProduct* (*)( ParameterType ),
        template<typename,typename, class>
            class FactoryErrorPolicy = FactoryError
    >
    class Parameter_Factory 
        : public FactoryErrorPolicy<IdentifierType,ParameterType, AbstractProduct>
    {
    public:
		Parameter_Factory( const char* name = "Parameter_Factory" )
			: name_( name )
		{
		}

        bool Register(const IdentifierType& id,ProductCreator creator)
        {
			/*if( id == -1 )
				throw ( new std::runtime_error( "Cache_Factory  id²»ÄÜÎª£­1" ) );*/

            return associations_.insert(
                IdToProductMap::value_type(id, creator)).second;
        }
        
        bool Unregister(const IdentifierType& id)
        {
            return associations_.erase(id) == 1;
        }

		AbstractProduct* CreateObject(const IdentifierType& id,const ParameterType& arg ) const
        {
			typename IdToProductMap::const_iterator i = associations_.find(id);
            if (i != associations_.end())
            {
                return (i->second)( arg );
            }
            return OnUnknownType(id,arg);
        }

		const char* name( ) const
		{
			return name_;
		}
    private:

		typedef std::map<IdentifierType, ProductCreator> IdToProductMap;
        IdToProductMap associations_;

		const char* name_;
    };

_bt_end

////////////////////////////////////////////////////////////////////////////////
// Change log:
// June 20, 2001: ported by Nick Thurn to gcc 2.95.3. Kudos, Nick!!!
// May  10, 2002: ported by Rani Sharoni to VC7 (RTM - 9466)
////////////////////////////////////////////////////////////////////////////////

//#endif // FACTORY_INC_

#define btfactory bt::Factory

#endif // _Factory_H_
