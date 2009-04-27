// make.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <process.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<char*> arguments( argc );
	{
		std::string logPath = argv[ 0 ];
		logPath += ".log";

		std::ofstream logger( logPath.c_str() );
		for( int i = 0; i < argc; ++ i )
		{
			arguments[ i ] = argv[0];
			logger  << i << ":\t" << argv[ i ] << std::endl;
		}
	}


	std::map<std::string,std::string> environMap;
	char* env;
	
	for( int i = 0; NULL != ( env = _environ[ i] ); ++ i )
	{
		char* p = strstr( env, "=" );
		if( NULL == p )
			continue;

		environMap[ std::string( env, p - env  ) ] = ++p;
	}

	std::string path = "";
	{
		std::string configPath = argv[ 0 ];
		configPath += ".conf";

		std::ifstream config( configPath.c_str() );
		
		if( config )
		{
			std::string line;
			while( std::getline( config,line ) )
			{
				std::string::size_type index = line.find( "=" );
				if( std::string::npos == index )
				{
					environMap[ line.substr( 0, index ) ] = line.substr( index + 1 );
				}
				else
				{
					environMap.erase( line );
				}
			}
		}
	}

	arguments[0] = "e:\\tools\\MinGW\\bin\\mingw32-make.exe";

	arguments.push_back( 0 );
	::_spawnv( _P_WAIT, arguments[0], &arguments[0] );
	std::cout << "执行结束!" << std::endl;
	return 0;
}

