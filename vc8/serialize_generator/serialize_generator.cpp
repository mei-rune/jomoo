// serialize_generator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

void printRecord( int record , std::ostream& target )
{
	target << "#define register_class( object";
	for( int i = 0; i < record; i ++ )
	{
		target << ", member" << i;
	}
	target << " ) \\" << std::endl;
	target << "inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \\" << std::endl;
    target << "{ return strm.open( context, #object, name) \\" << std::endl;
	for( int i = 0; i < record; i ++ )
	{
		target << "  && serialize(strm, context, s1.##member" << i << ", #member" << i << ") \\" << std::endl;
	}
	target << "  && strm.close( context); } \\" << std::endl;
	target << "inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \\" << std::endl;
    target << "{ return serialize_##object(strm, context, s1, name);} \\" << std::endl;
	
	target << "inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \\" << std::endl;
    target << "{ return strm.open( context, #object, name) \\" << std::endl;
	for( int i = 0; i < record; i ++ )
	{
		target << "  && deserialize(strm, context, s1.##member" << i << ", #member" << i << ") \\" << std::endl;
	}
	target << "  && strm.close(context); } \\" << std::endl;
	target << "inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \\" << std::endl;
    target << "{ return deserialize_##object(strm, context, s1, name);}" << std::endl;

	target << "" << std::endl;
}

void printRecordv2( int record , std::ostream& target )
{
	target << "#define register_class_v2( object";
	for( int i = 0; i < record; i ++ )
	{
		target << ", member" << i << ", member_type" << i;
	}
	target << " ) \\" << std::endl;

	target << "inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \\" << std::endl;
    target << "{ return strm.open( context, #object, name) \\" << std::endl;
	for( int i = 0; i < record; i ++ )
	{
		target << "  && serialize_##member_type" << i<< "(strm, context, s1.##member" << i << ", #member" << i << ") \\" << std::endl;
	}
	target << "  && strm.close( context); } \\" << std::endl;
	target << "inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \\" << std::endl;
    target << "{ return serialize_##object(strm, context, s1, name);} \\" << std::endl;
	
	target << "inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \\" << std::endl;
    target << "{ return strm.open( context, #object, name) \\" << std::endl;
	for( int i = 0; i < record; i ++ )
	{
		target << "  && deserialize_##member_type" << i<< "(strm, context, s1.##member" << i << ", #member" << i << ") \\" << std::endl;
	}
	target << "  && strm.close(context); } \\" << std::endl;
	target << "inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \\" << std::endl;
    target << "{ return deserialize_##object(strm, context, s1, name);}" << std::endl;

	target << "" << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if( argc < 3 )
	{
		std::cout << "参数错误!使用方法:" << std::endl;
		std::cout << argv[0] << " 最大字段个数 文件名" << std::endl;
		return -1;
	}

	int maxRecord = atoi( argv[1] );
	std::ofstream st( argv[2] );

	for( int i = 1; i < maxRecord; i ++ )
	{
		printRecord( i ,st );
		printRecordv2( i , st );
	}

	return 0;
}



