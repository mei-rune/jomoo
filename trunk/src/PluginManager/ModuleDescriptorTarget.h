#ifndef MODULE_DESCRIPTOR_TARGET_H
# define MODULE_DESCRIPTOR_TARGET_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "ModuleDescriptor.H"
# include <fstream>
# include "codes.h"

_seal_begin

class ModuleDescriptorTarget
{
public:

	ModuleDescriptorTarget ( const tstring& name )
		: ftarget_( name.c_str() )
		, target_( 0 )
		, level_( 0 )
	{
		target( ftarget_ );
	}
	ModuleDescriptorTarget ( const char* name )
		: ftarget_( name )
		, target_( 0 )
		, level_( 0 )
	{
		target( ftarget_ );
	}
	ModuleDescriptorTarget ( std::ostream& tg )
		: target_( 0 )
		, level_( 0 )
	{
		target( tg );
	}

	std::ostream& target()
	{
		return *target_;
	}

	void target( std::ostream& tg )
	{
		target_ = &tg;
	}

	ModuleDescriptorTarget& operator << ( ModuleDescriptor& descriptor )
	{
		writelevel();
		for( ModuleDescriptor::token_container_type::const_iterator it = descriptor.getToken().begin()
			; it != descriptor.getToken().end()
			; it ++ )
		{
			target() << encode( *it ) << " ";
		}
		target() << std::endl;
		print( descriptor );
		return *this;
	}

	void print( ModuleDescriptor& descriptor )
	{
		level_ ++;
		
		for( ModuleDescriptor::child_container_type::const_iterator it = descriptor.getChild().begin()
			; it != descriptor.getChild().end()
			; it ++ )
		{
			*this << *(*it);
		}
		level_ --;
	}

private:

	void writelevel( )
	{
		for( int i = 0; i < level_; i ++ )
			target() << " ";
	}

	std::ofstream ftarget_;
	std::ostream* target_;
	int level_;
};


_seal_end

#endif // MODULE_DESCRIPTOR_TARGET_H
 