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

	{
		std::string logPath = argv[ 0 ];
		logPath += ".log";
		std::ofstream logger( logPath.c_str() );

		logger << "Arguments:" << std::endl;
		logger << "Arguments:" << std::endl;
		for( int i = 0; i < argc; ++ i )
		{
			logger  << i << ":\t" << argv[ i ] << std::endl;
			std::cout  << i << ":\t" << argv[ i ] << std::endl;
		}

		logger << std::endl << "Environments:" << std::endl;
		std::cout << std::endl << "Environments:" << std::endl;
		std::map<std::string,std::string> environMap;
		for( int i = 0; NULL != _environ[ i ]; ++ i )
		{
			logger << _environ[ i ] << std::endl;
			std::cout << _environ[ i ] << std::endl;
		}
	}

	return 0;
}

