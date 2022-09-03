// f_cr_cDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "f_cr_c.h"
#include "f_cr_cDlg.h"
#include "union.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	void Initialize();
// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cf_cr_cDlg �Ի���




Cf_cr_cDlg::Cf_cr_cDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cf_cr_cDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cf_cr_cDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSGSHOW, MsgEdit);
}

BEGIN_MESSAGE_MAP(Cf_cr_cDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_INSET, &Cf_cr_cDlg::OnBnClickedInset)
	ON_BN_CLICKED(IDC_IN, &Cf_cr_cDlg::OnBnClickedIn)
	ON_BN_CLICKED(IDC_SEND, &Cf_cr_cDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_OUT, &Cf_cr_cDlg::OnBnClickedOut)
END_MESSAGE_MAP()


// Cf_cr_cDlg ��Ϣ�������

BOOL Cf_cr_cDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	DlgInitialize();
	NETExtendDiaog(FALSE);
	bShowAll=FALSE;
	ConnectThread=NULL;
	ConnectSock=INVALID_SOCKET;
	BN=0;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cf_cr_cDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cf_cr_cDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR Cf_cr_cDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL Cf_cr_cDlg::EnableWindow(UINT uID,BOOL bEnable)//able_unable_click
{
	return GetDlgItem(uID)->EnableWindow(bEnable);
}

void Cf_cr_cDlg::DlgInitialize()//��ʼ��ֵ����
{
	EnableWindow(IDC_SEND,FALSE);
	EnableWindow(IDC_OUT,FALSE);
	SetDlgItemText(IDC_IP,_T("127.0.0.1"));
	SetDlgItemText(IDC_PORT,_T("8008"));
}

void Cf_cr_cDlg::NETExtendDiaog(BOOL bshow)//net_size_set
{
	static CRect DlgRectLarge(0,0,0,0);
	static CRect DlgRectSmall(0,0,0,0);
	if(DlgRectLarge.IsRectNull())
	{
		GetWindowRect(&DlgRectLarge);
		DlgRectSmall=DlgRectLarge;
		DlgRectSmall.right-=202;
	}
	if(bshow)
	{
		bShowAll=TRUE;
		SetWindowPos(NULL,0,0,DlgRectLarge.Width(),DlgRectLarge.Height(),SWP_NOZORDER|SWP_NOMOVE);
	}
	else
	{
		bShowAll=FALSE;
		SetWindowPos(NULL,0,0,DlgRectSmall.Width(),DlgRectSmall.Height(),SWP_NOZORDER|SWP_NOMOVE);
	}
}


void Cf_cr_cDlg::OnBnClickedInset()
{
	if(bShowAll)
	{
		NETExtendDiaog(FALSE);
	}
	else
	{
		NETExtendDiaog(TRUE);
	}
}

void Cf_cr_cDlg::ShowMsg(CString strMsg)//�����¼��ʾ
{
	MsgEdit.SetSel(-1,-1);
	MsgEdit.ReplaceSel(strMsg+_T("\r\n"));
}


BOOL SOCKET_Select(SOCKET hSocket,int nTimeOut,BOOL bRead)
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);//��fdset��0 
	FD_SET(hSocket,&fdset);
	nTimeOut=nTimeOut>1000?1000:nTimeOut;
	tv.tv_sec=0;//��ʱ������ 
	tv.tv_usec=nTimeOut;//��ʱ�ĺ����� 
	int iRet=0;
	if(bRead)
	{
		iRet=select(0,&fdset,NULL,NULL,&tv);//�ɶ���socket 
	}
	else
	{
		iRet=select(0,NULL,&fdset,NULL,&tv);//��д��socket 
	}
	if(iRet<=0)//�д����ʱ 
	{
		return FALSE;
	}
	else if(FD_ISSET(hSocket,&fdset))//�ɶ����д��true 
	{
		return TRUE;	
	}
	return FALSE;
}

DWORD WINAPI connect_thread(LPVOID pParam)
{
	Cf_cr_cDlg *pf_cr_c=(Cf_cr_cDlg*)pParam;
	ASSERT(pf_cr_c!=NULL);
	pf_cr_c->ConnectSock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(pf_cr_c->ConnectSock==INVALID_SOCKET)
	{
		AfxMessageBox(_T("�½�SOCKETʧ��"));
		return FALSE;
	}
	CString strServIp;
	pf_cr_c->GetDlgItemText(IDC_IP,strServIp);
	int Port=pf_cr_c->GetDlgItemInt(IDC_PORT);
	if(Port<=0||Port>65535)
	{
		AfxMessageBox(_T("��������ȷ�Ķ˿�:1-65535"));
		closesocket(pf_cr_c->ConnectSock);
		return TRUE;
	}
	/*CString strAccount;
	pf_cr_c->GetDlgItemText(IDC_ACCOUNT,strAccount);
	if(strAccount)
	{
	AfxMessageBox(_T("�������˺�"));
	closesocket(pf_cr_c->ConnectSock);
	return TRUE;
	}

	CString strPassword;
	pf_cr_c->GetDlgItemText(IDC_PASSWORD,strPassword);
	if(strPassword)
	{
	AfxMessageBox(_T("����������"));
	closesocket(pf_cr_c->ConnectSock);
	return TRUE;
	}*/


	CString strName;
	pf_cr_c->GetDlgItemText(IDC_NAME,strName);
	if(strName.IsEmpty())
	{
		AfxMessageBox(_T("�������ǳ�"));
		closesocket(pf_cr_c->ConnectSock);
		return TRUE;
	}
	char szIpAddr[16]={0};
	USES_CONVERSION;
	strcpy_s(szIpAddr,16,T2A(strServIp));


	sockaddr_in service;
	service.sin_family=AF_INET;
	service.sin_addr.s_addr=inet_addr(szIpAddr);
	service.sin_port=htons(Port);//ת���ֽ�˳��

	if(connect(pf_cr_c->ConnectSock,(struct sockaddr*)&service,sizeof(struct sockaddr))==SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ʧ��"));
		closesocket(pf_cr_c->ConnectSock);
		return TRUE;
	}
	send(pf_cr_c->ConnectSock,(char*)strName.GetBuffer(),strName.GetLength()*sizeof(TCHAR),0);
	pf_cr_c->ShowMsg(_T("���ӳɹ�"));
	pf_cr_c->EnableWindow(IDC_SEND,TRUE);
	pf_cr_c->EnableWindow(IDC_OUT,TRUE);
	pf_cr_c->EnableWindow(IDC_IN,FALSE);
	pf_cr_c->EnableWindow(IDC_PORT,FALSE);
	pf_cr_c->EnableWindow(IDC_IP,FALSE);
	pf_cr_c->EnableWindow(IDC_NAME,FALSE);
	CString Name_error=_T("�ǳ��ظ�,������ǳƺ���������");
	pf_cr_c->BN=0;
	while(TRUE)
	{
		if(SOCKET_Select(pf_cr_c->ConnectSock))
		{
			TCHAR recvBuf[1024]={0};
			int iRet=recv(pf_cr_c->ConnectSock,(CHAR*)recvBuf,1024,0);
			if(iRet>0)
			{
				
				if(recvBuf==Name_error)
				{
					pf_cr_c->EnableWindow(IDC_SEND,FALSE);
					pf_cr_c->EnableWindow(IDC_OUT,FALSE);
					pf_cr_c->EnableWindow(IDC_IN,TRUE);
					pf_cr_c->EnableWindow(IDC_PORT,TRUE);
					pf_cr_c->EnableWindow(IDC_IP,TRUE);
					pf_cr_c->EnableWindow(IDC_NAME,TRUE);
				}
				pf_cr_c->ShowMsg(recvBuf);
			}
			else
			{
				if(pf_cr_c->BN==0)
					pf_cr_c->ShowMsg(_T("�������ر�,���ӶϿ�"));
				break;
			}
		}
		Sleep(500);
	}
	closesocket(pf_cr_c->ConnectSock);
	return TRUE;
}

void Cf_cr_cDlg::OnBnClickedIn()//�����¼
{
	ConnectThread=CreateThread(NULL,0,connect_thread,this,0,NULL);
}

void Cf_cr_cDlg::OnBnClickedSend()//���������Ϣ
{
	CString strMsg;
	CString strName;
	GetDlgItemText(IDC_MSGSEND,strMsg);
	GetDlgItemText(IDC_NAME,strName);
	if(strMsg.IsEmpty())
	{
		AfxMessageBox(_T("����������"));
		return;
	}

	send(ConnectSock,(char*)strMsg.GetBuffer(),strMsg.GetLength()*sizeof(TCHAR),0);
	SetDlgItemText(IDC_MSGSEND,_T(""));
}

void Cf_cr_cDlg::OnBnClickedOut()//����Ͽ�
{
	BN=1;
	closesocket(ConnectSock);
	ShowMsg(_T("�ѶϿ�����"));
	EnableWindow(IDC_NAME,TRUE);
	EnableWindow(IDC_IP,TRUE);
	EnableWindow(IDC_PORT,TRUE);
	EnableWindow(IDC_IN,TRUE);
	EnableWindow(IDC_OUT,FALSE);
	EnableWindow(IDC_SEND,FALSE);
}
