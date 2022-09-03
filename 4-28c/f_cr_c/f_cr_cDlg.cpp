// f_cr_cDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "f_cr_c.h"
#include "f_cr_cDlg.h"
#include "union.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	void Initialize();
// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// Cf_cr_cDlg 对话框




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


// Cf_cr_cDlg 消息处理程序

BOOL Cf_cr_cDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	DlgInitialize();
	NETExtendDiaog(FALSE);
	bShowAll=FALSE;
	ConnectThread=NULL;
	ConnectSock=INVALID_SOCKET;
	BN=0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cf_cr_cDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR Cf_cr_cDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL Cf_cr_cDlg::EnableWindow(UINT uID,BOOL bEnable)//able_unable_click
{
	return GetDlgItem(uID)->EnableWindow(bEnable);
}

void Cf_cr_cDlg::DlgInitialize()//初始数值设置
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

void Cf_cr_cDlg::ShowMsg(CString strMsg)//聊天记录显示
{
	MsgEdit.SetSel(-1,-1);
	MsgEdit.ReplaceSel(strMsg+_T("\r\n"));
}


BOOL SOCKET_Select(SOCKET hSocket,int nTimeOut,BOOL bRead)
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);//对fdset清0 
	FD_SET(hSocket,&fdset);
	nTimeOut=nTimeOut>1000?1000:nTimeOut;
	tv.tv_sec=0;//超时的秒数 
	tv.tv_usec=nTimeOut;//超时的毫秒数 
	int iRet=0;
	if(bRead)
	{
		iRet=select(0,&fdset,NULL,NULL,&tv);//可读性socket 
	}
	else
	{
		iRet=select(0,NULL,&fdset,NULL,&tv);//可写性socket 
	}
	if(iRet<=0)//有错误或超时 
	{
		return FALSE;
	}
	else if(FD_ISSET(hSocket,&fdset))//可读或可写则true 
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
		AfxMessageBox(_T("新建SOCKET失败"));
		return FALSE;
	}
	CString strServIp;
	pf_cr_c->GetDlgItemText(IDC_IP,strServIp);
	int Port=pf_cr_c->GetDlgItemInt(IDC_PORT);
	if(Port<=0||Port>65535)
	{
		AfxMessageBox(_T("请输入正确的端口:1-65535"));
		closesocket(pf_cr_c->ConnectSock);
		return TRUE;
	}
	/*CString strAccount;
	pf_cr_c->GetDlgItemText(IDC_ACCOUNT,strAccount);
	if(strAccount)
	{
	AfxMessageBox(_T("请输入账号"));
	closesocket(pf_cr_c->ConnectSock);
	return TRUE;
	}

	CString strPassword;
	pf_cr_c->GetDlgItemText(IDC_PASSWORD,strPassword);
	if(strPassword)
	{
	AfxMessageBox(_T("请输入密码"));
	closesocket(pf_cr_c->ConnectSock);
	return TRUE;
	}*/


	CString strName;
	pf_cr_c->GetDlgItemText(IDC_NAME,strName);
	if(strName.IsEmpty())
	{
		AfxMessageBox(_T("请输入昵称"));
		closesocket(pf_cr_c->ConnectSock);
		return TRUE;
	}
	char szIpAddr[16]={0};
	USES_CONVERSION;
	strcpy_s(szIpAddr,16,T2A(strServIp));


	sockaddr_in service;
	service.sin_family=AF_INET;
	service.sin_addr.s_addr=inet_addr(szIpAddr);
	service.sin_port=htons(Port);//转换字节顺序

	if(connect(pf_cr_c->ConnectSock,(struct sockaddr*)&service,sizeof(struct sockaddr))==SOCKET_ERROR)
	{
		AfxMessageBox(_T("连接失败"));
		closesocket(pf_cr_c->ConnectSock);
		return TRUE;
	}
	send(pf_cr_c->ConnectSock,(char*)strName.GetBuffer(),strName.GetLength()*sizeof(TCHAR),0);
	pf_cr_c->ShowMsg(_T("连接成功"));
	pf_cr_c->EnableWindow(IDC_SEND,TRUE);
	pf_cr_c->EnableWindow(IDC_OUT,TRUE);
	pf_cr_c->EnableWindow(IDC_IN,FALSE);
	pf_cr_c->EnableWindow(IDC_PORT,FALSE);
	pf_cr_c->EnableWindow(IDC_IP,FALSE);
	pf_cr_c->EnableWindow(IDC_NAME,FALSE);
	CString Name_error=_T("昵称重复,请更改昵称后重新连接");
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
					pf_cr_c->ShowMsg(_T("服务器关闭,连接断开"));
				break;
			}
		}
		Sleep(500);
	}
	closesocket(pf_cr_c->ConnectSock);
	return TRUE;
}

void Cf_cr_cDlg::OnBnClickedIn()//点击登录
{
	ConnectThread=CreateThread(NULL,0,connect_thread,this,0,NULL);
}

void Cf_cr_cDlg::OnBnClickedSend()//点击发送消息
{
	CString strMsg;
	CString strName;
	GetDlgItemText(IDC_MSGSEND,strMsg);
	GetDlgItemText(IDC_NAME,strName);
	if(strMsg.IsEmpty())
	{
		AfxMessageBox(_T("请输入内容"));
		return;
	}

	send(ConnectSock,(char*)strMsg.GetBuffer(),strMsg.GetLength()*sizeof(TCHAR),0);
	SetDlgItemText(IDC_MSGSEND,_T(""));
}

void Cf_cr_cDlg::OnBnClickedOut()//点击断开
{
	BN=1;
	closesocket(ConnectSock);
	ShowMsg(_T("已断开连接"));
	EnableWindow(IDC_NAME,TRUE);
	EnableWindow(IDC_IP,TRUE);
	EnableWindow(IDC_PORT,TRUE);
	EnableWindow(IDC_IN,TRUE);
	EnableWindow(IDC_OUT,FALSE);
	EnableWindow(IDC_SEND,FALSE);
}
