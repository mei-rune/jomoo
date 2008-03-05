
#include "Communicator.H"
#include "JOMOO_sap.H"


#ifdef _MEMORY_DEBUG
#undef THIS_FILE
#define new	   DEBUG_NEW  
#define malloc DEBUG_MALLOC  
static char THIS_FILE[] = __FILE__;  
#endif // _MEMORY_DEBUG

_networks_begin
//
//PlugIn_Server::PlugIn_Server(  const tstring& name ,Instance_Networks& instance )
//: instance_( instance )
//, module_( name )
//{
//}
//
//int PlugIn_Server::load( _util PropertiesPtr config )
//{
//	if( pServer_.get() != 0 )
//		LOG_ERROR_RETURN( instance_.getLogger(), BT_TEXT("PlugIn> �������[")
//			<< module_ << BT_TEXT( "]ʱ�������Ѿ�������" ) ,-1 );
//
//	try
//	{
//		tstring file = config->getProperty( "ModuleName" );
//		if( file.empty() )
//			LOG_ERROR_RETURN( instance_.getLogger(), BT_TEXT("PlugIn> �������[")
//			<< module_ << BT_TEXT( "]ʱ������û���ļ���." ) ,-1 );
//
//		tstring enterpoint = config->getProperty( "ModulePoint" );
//		if( enterpoint.empty() )
//			LOG_ERROR_RETURN( instance_.getLogger(), BT_TEXT("PlugIn> �������[")
//			<< module_ << BT_TEXT( "]ʱ������û�н����." ) ,-1 );
//
//		if( library_.open( file ) != 0 )
//			LOG_ERROR_RETURN( instance_.getLogger(), 
//			BT_TEXT("PlugIn> �������[") << module_ << BT_TEXT( "]ʱ������[") 
//			<< file <<BT_TEXT("]ʧ��," << library_.error() ) ,-1 );
//
//		MODULE_POINT module_point = ( MODULE_POINT ) library_.symbol( enterpoint.c_str() );
//		if( module_point == 0 )
//			LOG_ERROR_RETURN( instance_.getLogger(), BT_TEXT("PlugIn> �������[")
//			<< module_ << BT_TEXT( "]ʱ��ȡ������ַʧ��," << library_.error() ) ,-1 );
//
//		pServer_.reset( (*module_point)( instance_ ) );
//		if( pServer_.get() == 0 )
//			LOG_ERROR_RETURN( instance_.getLogger(), BT_TEXT("PlugIn> �������[")
//			<< module_ << BT_TEXT( "]ʱ�����ɷ���ʵ��ʧ��" ) ,-1 );
//
//		int r = pServer_->open( config );
//		if( r == -1 )
//			LOG_ERROR( instance_.getLogger(), BT_TEXT("PlugIn> �������[")
//			<< module_ << BT_TEXT( "]ʱ����������ʧ��" ) );
//		return r;
//
//	}
//	catch( std::runtime_error & e )
//	{
//		LOG_ERROR( instance_.getLogger(), BT_TEXT("PlugIn> �������[")
//			<< module_ << BT_TEXT( "]ʱ����������," ) << e.what() );
//	}
//	catch( ... )
//	{
//		LOG_ERROR( instance_.getLogger(), BT_TEXT("PlugIn> �������[")
//			<< module_ << BT_TEXT( "]ʱ������δ֪�쳣") );
//	}
//	return -1;
//}
//
//void PlugIn_Server::close()
//{
//	if( pServer_.get() == 0 )
//		LOG_ERROR( instance_.getLogger(), BT_TEXT("PlugIn> ֹͣ���[")
//			<< module_ << BT_TEXT( "]ʱ������û������" ) );
//	pServer_->close();
//
//}
//
//void PlugIn_Server::unload( )
//{
//	if( pServer_.get() == 0 )
//		LOG_ERROR( instance_.getLogger(), BT_TEXT("PlugIn> ֹͣ���[")
//			<< module_ << BT_TEXT( "]ʱ������û������" ) );
//	try
//	{
//		close();
//	}
//	catch( std::runtime_error & e )
//	{
//		LOG_ERROR( instance_.getLogger(), BT_TEXT("PlugIn> ֹͣ���[")
//			<< module_ << BT_TEXT( "]ʱ����������," ) << e.what() );
//	}
//	catch( ... )
//	{
//		LOG_ERROR( instance_.getLogger(), BT_TEXT("PlugIn> ֹͣ���[")
//			<< module_ << BT_TEXT( "]ʱ������δ֪�쳣") );
//	}
//}
//
//const tstring& PlugIn_Server::toString() const
//{
//	return module_;
//}

int Communicator::init_ = 0;

Communicator::Communicator()
: toString_( "Communicator" )
{
	if( init_ == 0 )
		JOMOO_sap::initsocket();

	init_ ++;
}

Communicator::~Communicator()
{
	init_ --;
	if( init_ == 0 )
		JOMOO_sap::shutdownsock();
}

int Communicator::open( _util ConfigurationSettings& config )
{
	int r = instance_.open( config );
	if( r != 0 )
		return r;
	return r;
}

void Communicator::close( )
{
	//std::list< PlugIn_Server* >::iterator it = servers_.begin();
	//for( ; it != servers_.end() ; it ++ )
	//		(*it)->close();

	instance_.close();

	//it = servers_.begin();
	//for( ; it != servers_.end() ; it ++ )
	//{
	//		(*it)->unload();
	//		delete (*it);
	//}
	//servers_.clear();
}
int Communicator::run( u_long milli_seconds )
{
	return instance_.run( milli_seconds );
}

JOMOO_Operation_Proactor& Communicator::getProactor()
{
	return instance_.getProactor();
}

Communicator::LoggerPtr Communicator::getLogger()
{
	return instance_.getLogger();
}

void Communicator::setLogger( LoggerPtr logger )
{
	return instance_.setLogger( logger );
}

JOMOO_Endpoint_Ptr Communicator::create(const tstring& addr )
{
	return instance_.create( addr );
}

const std::string& Communicator::toString() const
{
	return toString_;
}

_networks_end

JOMOO_Export_C _networks JOMOO_Communicator* initializeCommunicator_NoArg( )
{
	std::auto_ptr< JOMOO_Communicator > ptr( new Communicator() );
	return ptr.release();
}