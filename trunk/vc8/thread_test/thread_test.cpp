// thread_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "jomoo/threading/threading.h"

class runner
{
public:
	void run()
	{
		std::cout << "runer::run()" << std::endl;
	}

	void run(int i)
	{
		std::cout << "runer::run( " << i << ")" << std::endl;
	}

	void run(int i,int j)
	{
		std::cout << "runer::run(" << i "," << j << ")" << std::endl;
	}
};

void _run()
{
	std::cout << "_run()" << std::endl;
}

void _run(int i)
{
	std::cout << "_run( " << i << ")" << std::endl;
}

void _run(int i,int j)
{
	std::cout << "_run(" << i << "," << j << ")" << std::endl;
}

void _run(int i,int j, int k)
{
	std::cout << "_run(" << i << "," << j "," << k << ")" << std::endl;
}


int _tmain(int argc, _TCHAR* argv[])
{

	return 0;
}

