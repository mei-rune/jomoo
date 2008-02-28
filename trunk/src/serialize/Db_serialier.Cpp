#include "StdAfx.h"
#include "DB_serializer.h"
#include "DB_Adapter_Base.H"
#include "serialize/serializer_factory.h"

_bt_serialize_begin

class DataBase_serializer :
	public Db_serializer
{
public:
	DataBase_serializer( const char* file_name );
	DataBase_serializer( bt_ostream& istream );
	~DataBase_serializer(void);

	bool open(const tchar* ClassName);
	bool open(const tchar* ClassName, const size_t& size);

	
private:
	PDbConnection conn_;
	PDbExecute pexecuter_;

	tstring nameId_;
	tstring sql_;
};


DataBase_serializer::DataBase_serializer( const char* file_name )
{
	DbManager* dm = ___get_DbManager( );
	if( dm == 0 )
		throw std::runtime_error( "初始化DataBase_serializer失败，DbManager没有初始化" );
	conn_ = dm->createConnection( file_name );
	pexecuter_ = conn_->execute();
	init( &(*pexecuter_) );
}

DataBase_serializer::DataBase_serializer( bt_ostream& istream )
{
	DB_Adapter_Base* adapter = dynamic_cast< DB_Adapter_Base* >( &istream );
	if( adapter == 0 )
		throw std::runtime_error( "初始化DataBase_serializer失败，DataBase_serializer不支持bt_ostream" );
	init( adapter->getExecute() );
}

DataBase_serializer::~DataBase_serializer(void)
{
}

bool DataBase_serializer::open(const tchar* ClassName)
{
	return false;
}

bool DataBase_serializer::open(const tchar* ClassName, const size_t& size)
{
	return false;
}

class DataBase_deserializer : public Db_deserializer
{
public:
	DataBase_deserializer( const char* file_name );
	DataBase_deserializer( bt_istream& istream );
	~DataBase_deserializer(void);
	bool open(const tchar* ClassName);
	bool open(const tchar* ClassName, size_t& size);

	private:
	PDbConnection conn_;
	PDbQuery pquery_;

	tstring nameId_;
	tstring sql_;
};


DataBase_deserializer::DataBase_deserializer( const char* file_name )
{
	DbManager* dm = ___get_DbManager( );
	if( dm == 0 )
		throw std::runtime_error( "初始化DataBase_deserializer失败，DbManager没有初始化" );
	conn_ = dm->createConnection( file_name );
	pquery_ = conn_->query();
	init( &(*pquery_) ); 
}

DataBase_deserializer::DataBase_deserializer( bt_istream& istream )
{
	DB_Adapter_Base* adapter = dynamic_cast< DB_Adapter_Base* >( &istream );
	if( adapter == 0 )
		throw std::runtime_error( "初始化DataBase_deserializer失败，DataBase_deserializer不支持bt_ostream" );
	init( adapter->getQuery() );
}

DataBase_deserializer::~DataBase_deserializer(void)
{
}

bool DataBase_deserializer::open(const tchar* ClassName)
{
	return false;
}

bool DataBase_deserializer::open(const tchar* ClassName, size_t& size)
{
	return false;
}

serialize_ostream_base* make_DataBase_serializer( BIN_OUT_Source* bos )
{
	if( bos == 0 )
		return 0;

	switch( bos->type_ )
	{
	case BIN_INPUT_Source::file_source:
		if( bos->file_name_ != 0 )
		return new DataBase_serializer( bos->file_name_ );
		break;
	case BIN_INPUT_Source::stream_source:
		if( bos->ostream_ != 0 )
		return new DataBase_serializer( *(bos->ostream_ ) );
	};

	throw std::runtime_error( "本类型的序列化器不支持这个接口" );
	return 0;
}

serialize_istream_base* make_DataBase_deserializer( BIN_INPUT_Source* bos )
{
	if( bos == 0 )
		return 0;

	switch( bos->type_ )
	{
	case BIN_INPUT_Source::file_source:
		if( bos->file_name_ != 0 )
		return new DataBase_deserializer( bos->file_name_ );
		break;
	case BIN_INPUT_Source::stream_source:
		if( bos->istream_ != 0 )
		return new DataBase_deserializer( *(bos->istream_ ) );
	};

	throw std::runtime_error( "本类型的序列化器不支持这个接口" );
	return 0;
}


#ifdef STATIC_INIT

bool DataBase_serializer = BTOUTSerializeFactory_Singleton::instance()->Register( db_stream, make_DataBase_serializer );
bool DataBase_deserializer = BTINPUTSerializeFactory_Singleton::instance()->Register( db_stream, make_DataBase_deserializer );

#endif // 

_bt_serialize_end