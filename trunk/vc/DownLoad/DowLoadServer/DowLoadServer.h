// DowLoadServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CDowLoadServerApp:
// �йش����ʵ�֣������ DowLoadServer.cpp
//

class CDowLoadServerApp : public CWinApp
{
public:
	CDowLoadServerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDowLoadServerApp theApp;
