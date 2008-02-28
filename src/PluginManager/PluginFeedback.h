#ifndef PLUGIN_MANAGER_PLUGIN_FEEDBACK_H
# define PLUGIN_MANAGER_PLUGIN_FEEDBACK_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
# include "config_PluginManager.h"
# include "Hazel.Base/Exception.hpp"
# include "Hazel.Base/Threading/Threading.H"
# include <set>

_seal_begin

class PluginException : public _hazel Exception
{
public:
	PluginException( const   char* const         srcFile
            , size_t        srcLine
			, int code
			, const tstring& scope
			, const tstring& message )
			: _hazel Exception( srcFile, srcLine ,message )
			, code_( code )
			, scope_( scope )
	{
	}

	const tstring& scope() const
	{
		return scope_;
	}

	int code() const
	{
		return code_;
	}

	virtual Exception* clone()
	{
		return new PluginException( *this );
	}

	virtual void rethrow()
	{
		Raise( *this );
	}

	virtual void print(std::ostream& Target ) const
	{
		Target << BT_TEXT( "PluginException[ file:" )
			<< getFile()
			<< BT_TEXT( " line:" )
			<< ( int ) getLine()
			<< BT_TEXT(" ] ")
			<< what()
			<< std::endl
			<< BT_TEXT( "\t[ scope=" )
			<< scope()
			<< BT_TEXT( ", code=" )
			<< code()
			<< BT_TEXT( " ]" );
	}
private:
	tstring scope_;
	int code_;
};

class IPluginFeedback
{
public:

    enum FeedbackCode
    {
	StatusLoading,		//
	StatusUnloading,	//
	StatusEntries,		//
	StatusAttaching,	//
	StatusDetaching,	//
	StatusQuerying,		//

	ErrorVersionFailure,
	ErrorLoadFailure,	//
	ErrorEntryFailure,	//
	ErrorBadModule,		//
	ErrorBadCacheFile,	//
	ErrorNoFactory,		//

	Other
    };

	typedef counter_ptr< IPluginFeedback > ptr_type;

	virtual ~IPluginFeedback( ){}

	virtual void feedback( int code,
		    		  const tstring &scope,
					  const tstring& error ) = 0;

	virtual void feedback( int code,
		    		  const tstring &scope,
					  const Exception &error ) = 0;

	virtual void feedback( int code,
		    		  const tstring &scope ) = 0;


};

typedef IPluginFeedback::ptr_type FeedbackCB;


class PluginFeedback_Group : public IPluginFeedback
{
public:

	void feedback( int code,
		    		  const tstring &scope,
					  const Exception& error )
	{
		Hazel_GUARD( guard,mutex_ );
		for( std::set< FeedbackCB >::iterator it = group_.begin()
			; it != group_.end()
			; it ++  )
			(*it)->feedback( code, scope, error );
	}

	void feedback( int code,
		    		  const tstring &scope )
	{
		Hazel_GUARD( guard,mutex_ );
		for( std::set< FeedbackCB >::iterator it = group_.begin()
			; it != group_.end()
			; it ++  )
			(*it)->feedback( code, scope );
	}

	void feedback( int code,
		    		  const tstring &scope,
					  const tstring &error )
	{
		Hazel_GUARD( guard,mutex_ );
		for( std::set< FeedbackCB >::iterator it = group_.begin()
			; it != group_.end()
			; it ++  )
			(*it)->feedback( code, scope ,error);
	}


	void add( FeedbackCB cb )
	{
		Hazel_GUARD( guard,mutex_ );
		group_.insert( cb );
	}

	void remove( FeedbackCB cb )
	{
		Hazel_GUARD( guard,mutex_ );
		group_.erase( cb );
	}

private:

	Hazel_MUTEX_MUTABLE( mutex_ );
	std::set< FeedbackCB > group_;

};

_seal_end

#endif // PLUGIN_MANAGER_PLUGIN_FEEDBACK_H
