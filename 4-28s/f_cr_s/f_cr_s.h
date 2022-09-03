// f_cr_s.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// Cf_cr_sApp:
// 有关此类的实现，请参阅 f_cr_s.cpp
//

class Cf_cr_sApp : public CWinApp
{
public:
	Cf_cr_sApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern Cf_cr_sApp theApp;