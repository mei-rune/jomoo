
#ifndef JOMOO_COMMUNICATOR_H
#define JOMOO_COMMUNICATOR_H

#include "config.h"

#if !defined (JOMOO_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* JOMOO_LACKS_PRAGMA_ONCE */


// Include files
# include "../config_Networks.h"
# include "Base/Util/Configuration.H"
# include "JOMOO_Endpoint_Factory.H"
# include "HazelOperationProactor.H"
# include "Hazel.MicroKernel/MicroKernel.H"
# include "../JOMOO_Url.H"

_networks_begin

class Instance_Networks
{
public:

	typedef NetWorksLoggerPtr LoggerPtr;
	
	virtual ~Instance_Networks(void){}

	virtual int run( u_long milli_seconds ) = 0;

	virtual JOMOO_Operation_Proactor& getProactor() = 0;

	virtual bool isStop() = 0;

	virtual LoggerPtr getLogger() = 0;

	virtual void setLogger( LoggerPtr ) = 0;

	virtual const _util ConfigurationSettings& conf() const = 0;

	virtual JOMOO_Endpoint_Ptr create(const tstring&) = 0;

	virtual _micro_kernel IKernel& kernel( ) = 0;

	virtual _micro_kernel Component& findComponent( const JOMOO_Url_Base& url ) = 0;

	virtual const tstring& toString() const = 0;
};

//class JOMOO_Server
//{
//public:
//	virtual ~JOMOO_Server(){};
//	virtual int open( _util PropertiesPtr config ) = 0;
//	virtual void close( ) = 0;
//	virtual const tstring& toString() const = 0;
//};
//
//#define DEFINE_SERVER( X ) JOMOO_Export_C _io JOMOO_Server* make_##X( _io Instance_Networks& instance ){ return new X( instance ); }

/**
 * 
 */
class JOMOO_Communicator
{
public:

	typedef JOMOO_Transport::LoggerPtr LoggerPtr;
    	
	/**
	 * virtual destructor
	 */
	virtual ~JOMOO_Communicator(){}

	virtual int open( _util ConfigurationSettings& conf ) = 0;

	virtual void close( ) = 0;

	virtual int run( u_long milli_seconds ) = 0;

	virtual LoggerPtr getLogger() = 0;

	virtual void setLogger( LoggerPtr ) = 0;

	virtual JOMOO_Endpoint_Ptr create(const tstring&) = 0;

	/**
	 * 取得实例的描述
	 */
    virtual const std::string& toString() const = 0;
};

typedef counter_ptr< JOMOO_Communicator > JOMOO_Communicator_Ptr;

class JOMOO_Communicator_Factory : public _seal PluginFactory< JOMOO_Communicator* ( ) >
{
public:
	static JOMOO_Communicator_Factory& get (void)
	{
		return JOMOO_Singleton< JOMOO_Communicator_Factory , Threading::MUTEX >::get();
	}
private:

	friend class JOMOO_Singleton< JOMOO_Communicator_Factory , Threading::MUTEX >;

	JOMOO_Communicator_Factory ( ) : _seal PluginFactory< JOMOO_Communicator* ( ) > ( _seal getPluginManager(), BT_TEXT( "Hazel.Networks.Endpoint") , BT_TEXT( "1.0" ))
	{
	}
};

_networks_end

//JOMOO_Export_C _networks JOMOO_Communicator* initializeCommunicator_NoArg( );
//
//inline _networks JOMOO_Communicator_Ptr initializeCommunicator( )
//{
//	return JOMOO_Communicator_Ptr( initializeCommunicator_NoArg( ) );
//}

#endif // JOMOO_COMMUNICATOR_H
