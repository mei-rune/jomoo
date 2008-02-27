#ifndef __FACTORY_KEY__
#define __FACTORY_KEY__

# include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"


_seal_begin

class FactoryKey
{
public:
	FactoryKey( int32_t first, const tstring& second )
		: first_( first )
		, second_( second )
	{
	}

	int32_t first() const
	{
		return first_;
	}

	const tstring& second() const
	{
		return second_;
	}

private:
	int32_t first_;
	tstring second_;
};


inline bool operator==( const FactoryKey& key1, const FactoryKey& key2 )
{
	if( key1.first() != key2.first() )
		return false;
	return key1.second() == key2.second();
}

inline bool operator!=( const FactoryKey& key1, const FactoryKey& key2 )
{
	return !( key1 == key2 );
}

inline bool operator<( const FactoryKey& key1, const FactoryKey& key2 )
{
	if( key1.first() != key2.first() )
		return key1.first() < key2.first();
	return key1.second() < key2.second();
}

inline bool operator>( const FactoryKey& key1, const FactoryKey& key2 )
{
	return key2 < key1;
}

inline bool operator<=( const FactoryKey& key1, const FactoryKey& key2 )
{
	return ( ( key1 < key2) || ( key1 == key2 ) );
}

inline bool operator>=( const FactoryKey& key1, const FactoryKey& key2 )
{
	return ( ( key1 > key2) || ( key1 == key2 ) );
}

_seal_end

#endif // __FACTORY_KEY__