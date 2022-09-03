// f_cr_cDlg.h : ͷ�ļ�
//

#pragma once
#include "Resource.h"
#include "winsock2.h"
#include "union.h"
#include "afxwin.h"

// Cf_cr_cDlg �Ի���
class Cf_cr_cDlg : public CDialog
{
// ����
public:
	Cf_cr_cDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_F_CR_C_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL EnableWindow(UINT uID,BOOL bEnable=TRUE);
	void DlgInitialize();
	void NETExtendDiaog(BOOL bshow);
	BOOL bShowAll;
	afx_msg void OnBnClickedInset();
	afx_msg void OnBnClickedIn();
	HANDLE ConnectThread;
	SOCKET ConnectSock;
	CEdit MsgEdit;
	CArray<CClientItem,CClientItem>ClientArray;
	BOOL SOCKET_Select(SOCKET hSocket,int nTimeOut,BOOL bRead);
	void ShowMsg(CString strMsg);
	//void SendMsg(CString strMsg,CClientItem *pNotSend=NULL);
	afx_msg void OnBnClickedSend();
	BOOL BN;
	afx_msg void OnBnClickedOut();
};
