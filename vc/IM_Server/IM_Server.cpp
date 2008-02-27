// IM_Server.cpp : 定义控制台应用程序的入口点。
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

