// f_cr_c.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cf_cr_cApp:
// �йش����ʵ�֣������ f_cr_c.cpp
//

class Cf_cr_cApp : public CWinApp
{
public:
	Cf_cr_cApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cf_cr_cApp theApp;