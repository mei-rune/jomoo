#ifndef ENUMERATOR_H
# define ENUMERATOR_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */

// Include files
# include <list>

_jomoo_begin

namespace detail
{
	template< typename T , typename W >
	inline void walk( T* t, W& w)
	{
		t->walk( w );
	}
	
	template< typename T , typename W >
	inline void walk( const T* t, W& w)
	{
		t->walk( w );
	}

	template< typename T , typename W >
	inline void walk( T& t, W& w)
	{
		t.walk( w );
	}
	
	template< typename T , typename W >
	inline void walk( const T& t, W& w)
	{
		t.walk( w );
	}
}

template< typename W >
class enumerator
{
public:
	typedef W walker_type;
	typedef typename walker_type::value_type value_type ;
	typedef std::list< value_type* > collection_type;
	typedef typename collection_type::iterator iterator;

	class walker : walker_type
	{
	public :
		walker( collection_type& collection )
			: collection_( collection )
		{
		}

		void on_walk( value_type& value )
		{
			collection_.push_back( &value );
		}

		void on_walk( const value_type& value )
		{
			//collection_.push_back( &value );
		}
	private:
		DECLARE_NO_COPY_CLASS( walker );
		collection_type& collection_;
	};

	template< typename T >
	enumerator( T container )
	{
		walker w( collection_ );
		detail::walk( container , w );
	}

	iterator begin()
	{
		return collection_.begin();
	}

	iterator end()
	{
		return collection_.end();
	}

private:
	DECLARE_NO_COPY_CLASS( enumerator );
	collection_type collection_;
};

template< typename W >
class const_enumerator
{
public:
	typedef W walker_type;
	typedef typename walker_type::value_type value_type ;
	typedef std::list< const value_type* > collection_type;
	typedef typename collection_type::const_iterator iterator;

	class walker : walker_type
	{
	public :
		walker( collection_type& collection )
			: collection_( collection )
		{
		}

		void on_walk( value_type& value )
		{
			//collection_.push_back( &value );
		}

		void on_walk( const value_type& value )
		{
			collection_.push_back( &value );
		}
	private:
		DECLARE_NO_COPY_CLASS( walker );
		collection_type& collection_;
	};

	template< typename T >
	const_enumerator( T container )
	{
		walker w( collection_ );
		detail::walk( container , w );
	}

	iterator begin()
	{
		return collection_.begin();
	}

	iterator end()
	{
		return collection_.end();
	}

private:
	DECLARE_NO_COPY_CLASS( const_enumerator );
	collection_type collection_;
};

_jomoo_end

#endif // ENUMERATOR_H
