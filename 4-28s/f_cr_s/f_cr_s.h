// f_cr_s.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cf_cr_sApp:
// �йش����ʵ�֣������ f_cr_s.cpp
//

class Cf_cr_sApp : public CWinApp
{
public:
	Cf_cr_sApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cf_cr_sApp theApp;