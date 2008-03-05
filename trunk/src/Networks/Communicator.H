
#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */


// Include files
#include "config_Networks.h"
#include "Instance_Networks.H"
#include "include/JOMOO_Communicator.H"
#include "Base/util/Share_Library.H"
#include <list>

//typedef _networks JOMOO_Server* (*MODULE_POINT)( _networks Instance_Networks& );

_networks_begin


//class PlugIn_Server
//{
//public:
//	PlugIn_Server(  const tstring& name ,Instance_Networks& instance );
//
//	int load( _util PropertiesPtr config );
//	void unload( );
//	void close();
//	
//	const tstring& toString() const;
//
//private:
//	const tstring module_;
//	Instance_Networks& instance_;
//	_util Share_Library library_;
//	std::auto_ptr< JOMOO_Server > pServer_; 
//};

/**
 * 
 */
class Communicator : public JOMOO_Communicator
{
public:

	Communicator();

	~Communicator();

	virtual int open( _util ConfigurationSettings& config );

	virtual void close( ) ;

	virtual int run( u_long milli_seconds );

	virtual JOMOO_Operation_Proactor& getProactor();

	virtual LoggerPtr getLogger();

	virtual void setLogger( LoggerPtr );

	virtual JOMOO_Endpoint_Ptr create(const tstring&);

    virtual const std::string& toString() const;


private:

	//std::list< PlugIn_Server* > servers_;

	InstanceNetworks instance_;

	tstring toString_;

	static int init_;
};

_networks_end

#endif // COMMUNICATOR_H
