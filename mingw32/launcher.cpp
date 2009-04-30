// make.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <process.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>


const char* drive ="/cygdrive/";
size_t driveLen = 0;
std::ofstream *_logger = NULL;

std::string decodePath( const std::string& second  )
{
	std::string::size_type index = second.find( drive );
	if( std::string::npos == index )
		return second;

	if( ( index + driveLen ) >= second.size() )
		return second;

	std::string value = second.substr( 0, index );
	value += second[ index + driveLen ];
	value += ":";
	value += second.substr( index + driveLen + 1 );
	return value;
}

void readFile( std::map<std::string,std::string>& environMap
			  , const char* path )
{

	if( NULL != _logger)
		*_logger << std::endl << "File:"<< std::endl;

	std::string filePath = path;
	filePath += ".conf";

	std::ifstream config( filePath.c_str() );

	if( !config )
	{
		if( NULL != _logger)
			*_logger << "读文件 '" <<  filePath << "' 失败!" << std::endl;
		return;
	}


	if( NULL != _logger)
		*_logger << "开始读文件 '" <<  filePath << "'" << std::endl;

	std::string line;
	while( std::getline( config,line ) )
	{
		std::string::size_type index = line.find( "=" );
		if( std::string::npos != index )
		{
			std::string key = line.substr( 0, index );
			std::string value = line.substr( index + 1 );
			environMap[ key ] = value;

			if( NULL != _logger)
				*_logger << "\t" << key << "='" << value << "'" << std::endl;
		}
		else
		{
			environMap.erase( line );

			if( NULL != _logger)
				*_logger << "\tdel " << line << std::endl;
		}
	}


	if( NULL != _logger)
		*_logger << "读文件 '" <<  filePath << "' 结束!" << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	driveLen = strlen( drive );

	std::vector<char*> arguments( argc );
	std::vector<char*> environments;

	{
		std::string logPath = argv[ 0 ];
		logPath += ".log";
		std::ofstream logger( logPath.c_str() );
		if( logger )
			_logger = &logger;

		logger << "Old_Arguments:" << std::endl;
		for( int i = 0; i < argc; ++ i )
		{
			arguments[ i ] = argv[ i ];
			logger  << i << ":\t" << argv[ i ] << std::endl;
		}

		logger << std::endl << "Old_Environments:" << std::endl;
		std::map<std::string,std::string> environMap;
		for( int i = 0; NULL != _environ[ i ]; ++ i )
		{
			logger << _environ[ i ] << std::endl;

			char* p = strstr( _environ[ i ], "=" );
			if( NULL == p )
			{
				environMap[ _environ[ i ] ] = "";
				continue;
			}

			std::string key = std::string( _environ[ i ], p - _environ[ i ]  );
			environMap[ key ] = ++p;
		}

		readFile( environMap, argv[0] );
		for( std::map<std::string, std::string>::iterator it = environMap.begin()
			; it != environMap.end(); ++ it)
		{
			std::string line  = it->first + "="+ decodePath( it->second );
			environments.push_back( ::strdup( line.c_str() ) );
		}

		arguments[0] = "e:\\tools\\MinGW\\bin\\mingw32-make.exe";
		std::map<std::string,std::string>::iterator it = environMap.find( "Command" );
		if( environMap.end() != it )
			arguments[ 0 ] =( char*) it->second.c_str();

		for( int i = 0; i < arguments.size(); ++ i )
		{
			arguments[ i ] =::strdup( decodePath( arguments[ i ] ).c_str() );
		}


		environments.push_back( 0 );
		arguments.push_back( 0 );

		logger << std::endl << "Environments:" << std::endl;
		for( char** ptr = &(environments[0]) ; 0 != *ptr; ++ ptr )
		{
			logger << *ptr << std::endl;
		}

		logger << std::endl << "Arguments:" << std::endl;
		for( char** ptr = &(arguments[0]) ; 0 != *ptr; ++ ptr )
		{
			logger << *ptr << std::endl;
		}
	}


	return ::_spawnve( _P_WAIT, arguments[0], &(arguments[0]), &(environments[0]) );
	//std::cout << "执行结束!" << std::endl;
	//return 0;
}

