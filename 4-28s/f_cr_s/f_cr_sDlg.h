// f_cr_sDlg.h : ͷ�ļ�
//

#pragma once

#include "Resource.h"
#include "winsock2.h"
#include "union.h"
#include "afxwin.h"
// Cf_cr_sDlg �Ի���
class Cf_cr_sDlg : public CDialog
{
// ����
public:
	Cf_cr_sDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_F_CR_S_DIALOG };

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