// f_cr_sDlg.h : 头文件
//

#pragma once

#include "Resource.h"
#include "winsock2.h"
#include "union.h"
#include "afxwin.h"
// Cf_cr_sDlg 对话框
class Cf_cr_sDlg : public CDialog
{
// 构造
public:
	Cf_cr_sDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_F_CR_S_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickedConnect();
	void DlgInitialize();
	HANDLE ListenThread;
	SOCKET ListenSock;
	BOOL SOCKET_Select(SOCKET hSocket,int nTimeOut,BOOL bRead);
	BOOL EnableWindow(UINT uID,BOOL bEnable=TRUE);
	CArray<CClientItem,CClientItem>ClientArray;
	CEdit MsgEdit;
	void RemoveClient(CClientItem in_Item);
	void SendMsg(CString strMsg,CClientItem *pNotSend);

};