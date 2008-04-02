

/**
* -*- C++ -*-
* Factory.h,v 1.0 2004/09/08 10:27:54
*/

#ifndef _Factory_H_
#define _Factory_H_

#include "jomoo/config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

#include <map>
#include <exception>

_jomoo_begin

namespace detail
{

	template <typename IdentifierType , class AbstractProduct>
	struct FactoryError
	{
		struct Exception : public std::exception
		{
			const char* what() const throw() { return "Unknown Type"; }
		};

		static AbstractProduct OnUnknownType( IdentifierType )
		{
			throw Exception();
		}
	};

	template <typename IdentifierType, typename ParameterType, class AbstractProduct>
	struct FactoryError
	{
		struct Exception : public std::exception
		{
			const char* what() const throw() { return "Unknown Type"; }
		};

		static AbstractProduct OnUnknownType(IdentifierType,ParameterType)
		{
			throw Exception();
		}
	};

};

template
<
	class AbstractProduct, 
		typename IdentifierType,
		typename ProductCreator = AbstractProduct (*)(),
		template<typename, class>
		class FactoryErrorPolicy = detail:: FactoryError
>
class Factory 
	: public FactoryErrorPolicy<IdentifierType, AbstractProduct>
{
public:

	bool Register( IdentifierType id, ProductCreator creator)
	{
		return associations_.insert(
			IdToProductMap::value_type(id, creator)).second;
	}

	bool Unregister( IdentifierType id)
	{
		return associations_.erase(id) == 1;
	}

	AbstractProduct CreateObject( IdentifierType id) const
	{
		typename IdToProductMap::const_iterator i = associations_.find(id);
		if (i != associations_.end())
		{
			return (i->second)();
		}
		return OnUnknownType(id);
	}

private:
	typedef std::map<IdentifierType, ProductCreator> IdToProductMap;
	IdToProductMap associations_;
};

template
<
	class AbstractProduct, 
		typename IdentifierType,
		typename ParameterType,
		typename ProductCreator = AbstractProduct (*)( ParameterType ),
		template<typename,typename, class>
		class FactoryErrorPolicy = detail:: FactoryError
>
class Parameter_Factory 
	: public FactoryErrorPolicy<IdentifierType,ParameterType, AbstractProduct>
{
public:

	bool Register( IdentifierType id,ProductCreator creator)
	{
		/*if( id == -1 )
		throw ( new std::runtime_error( "Cache_Factory  id²»ÄÜÎª£­1" ) );*/

		return associations_.insert(
			IdToProductMap::value_type(id, creator)).second;
	}

	bool Unregister( IdentifierType id)
	{
		return associations_.erase(id) == 1;
	}

	AbstractProduct CreateObject( IdentifierType id, ParameterType arg ) const
	{
		typename IdToProductMap::const_iterator i = associations_.find(id);
		if (i != associations_.end())
		{
			return (i->second)( arg );
		}
		return OnUnknownType(id,arg);
	}

private:

	typedef std::map<IdentifierType, ProductCreator> IdToProductMap;
	IdToProductMap associations_;
};

_jomoo_end

#endif // _Factory_H_
