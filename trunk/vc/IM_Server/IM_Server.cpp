// IM_Server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "BOE/IM/IM.H"
#include "BOE/IM/Router.H"

int _tmain(int argc, _TCHAR* argv[])
{
	IM_Server svr( argc, argv );

	svr.run();
	return 0;
}

