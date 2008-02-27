// DebugTester.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


void Crash(void)
{
int i = 1;
int j = 0;
i /= j;
}
int _tmain(int argc, _TCHAR* argv[])
{
	Crash();

	return 0;
}

