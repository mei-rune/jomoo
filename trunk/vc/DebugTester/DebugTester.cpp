// DebugTester.cpp : �������̨Ӧ�ó������ڵ㡣
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

