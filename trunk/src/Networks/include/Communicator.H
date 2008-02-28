
#ifndef Hazel_COMMUNICATOR_H
#define Hazel_COMMUNICATOR_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */


// Include files
# include "../config_Networks.h"
# include "Hazel.Base/Util/Configuration.H"
# include "Hazel_Endpoint_Factory.H"
# include "HazelOperationProactor.H"
# include "Hazel.MicroKernel/MicroKernel.H"
# include "../Hazel_Url.H"

_networks_begin

class Instance_Networks
{
public:

	typedef NetWorksLoggerPtr LoggerPtr;
	
	virtual ~Instance_Networks(void){}

	virtual int run( u_long milli_seconds ) = 0;

	virtual Hazel_Operation_Proactor& getProactor() = 0;

	virtual bool isStop() = 0;

	virtual LoggerPtr getLogger() = 0;

	virtual void setLogger( LoggerPtr ) = 0;

	virtual const _util ConfigurationSettings& conf() const = 0;

	virtual Hazel_Endpoint_Ptr create(const tstring&) = 0;

	virtual _micro_kernel IKernel& kernel( ) = 0;

	virtual _micro_kernel Component& findComponent( const Hazel_Url_Base& url ) = 0;

	virtual const tstring& toString() const = 0;
};

//class Hazel_Server
//{
//public:
//	virtual ~Hazel_Server(){};
//	virtual int open( _util PropertiesPtr config ) = 0;
//	virtual void close( ) = 0;
//	virtual const tstring& toString() const = 0;
//};
//
//#define DEFINE_SERVER( X ) Hazel_Export_C _io Hazel_Server* make_##X( _io Instance_Networks& instance ){ return new X( instance ); }

/**
 * 
 */
class Hazel_Communicator
{
public:

	typedef Hazel_Transport::LoggerPtr LoggerPtr;
    	
	/**
	 * virtual destructor
	 */
	virtual ~Hazel_Communicator(){}

	virtual int open( _util ConfigurationSettings& conf ) = 0;

	virtual void close( ) = 0;

	virtual int run( u_long milli_seconds ) = 0;

	virtual LoggerPtr getLogger() = 0;

	virtual void setLogger( LoggerPtr ) = 0;

	virtual Hazel_Endpoint_Ptr create(const tstring&) = 0;

	/**
	 * 取得实例的描述
	 */
    virtual const std::string& toString() const = 0;
};

typedef counter_ptr< Hazel_Communicator > Hazel_Communicator_Ptr;

class Hazel_Communicator_Factory : public _seal PluginFactory< Hazel_Communicator* ( ) >
{
public:
	static Hazel_Communicator_Factory& get (void)
	{
		return Hazel_Singleton< Hazel_Communicator_Factory , Threading::MUTEX >::get();
	}
private:

	friend class Hazel_Singleton< Hazel_Communicator_Factory , Threading::MUTEX >;

	Hazel_Communicator_Factory ( ) : _seal PluginFactory< Hazel_Communicator* ( ) > ( _seal getPluginManager(), BT_TEXT( "Hazel.Networks.Endpoint") , BT_TEXT( "1.0" ))
	{
	}
};

_networks_end

//Hazel_Export_C _networks Hazel_Communicator* initializeCommunicator_NoArg( );
//
//inline _networks Hazel_Communicator_Ptr initializeCommunicator( )
//{
//	return Hazel_Communicator_Ptr( initializeCommunicator_NoArg( ) );
//}

#endif // Hazel_COMMUNICATOR_H
