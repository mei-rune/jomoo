// make.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

int _tmain(int argc, _TCHAR* argv[])
{

	std::ofstream ff( "c:\\aaaa.txt");
	for( int i = 0; i < argc; ++ i )
	{
		ff  << i << ":\t" << argv[ i ] << std::endl;
	}

	return 0;
}

