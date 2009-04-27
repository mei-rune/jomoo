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
	value += second.substr( index + driveLen );
	return value;
}

void readFile( std::map<std::string,std::string>& environMap
					, const char* path )
{
	std::string filePath = path;
	filePath += ".conf";

	std::ifstream config( filePath.c_str() );

	if( !config )
		return;

	std::string line;
	while( std::getline( config,line ) )
	{
		std::string::size_type index = line.find( "=" );
		if( std::string::npos != index )
			environMap[ line.substr( 0, index ) ] = line.substr( index + 1 );
		else
			environMap.erase( line );
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	driveLen = strlen( drive );

	std::vector<char*> arguments( argc );
	std::vector<char*> environments( argc, (char*)NULL );

	{
		std::string logPath = argv[ 0 ];
		logPath += ".log";
		std::ofstream logger( logPath.c_str() );

		logger << "Arguments:" << std::endl;
		for( int i = 0; i < argc; ++ i )
		{
			arguments[ i ] = argv[0];
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

		logger << std::endl << "Environments:" << std::endl;

		for( std::map<std::string, std::string>::iterator it = environMap.begin()
			; it != environMap.end(); ++ it)
		{
			std::string line  = it->first + "="+ decodePath( it->second );
			environments.push_back( ::strdup( line.c_str() ) );
			logger << line << std::endl;
		}

		arguments[0] = "e:\\tools\\MinGW\\bin\\mingw32-make.exe";
		std::map<std::string,std::string>::iterator it = environMap.find( "Command" );
		if( environMap.end() != it )
			arguments[ 0 ] =::strdup( decodePath( it->second ).c_str() );
	}

	arguments.push_back( 0 );
	environments.push_back( 0 );

	::_spawnve( _P_WAIT, arguments[0], &(arguments[0]), &(environments[0]) );
	std::cout << "执行结束!" << std::endl;
	return 0;
}

