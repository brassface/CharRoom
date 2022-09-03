// f_cr_sDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "f_cr_s.h"
#include "f_cr_sDlg.h"
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


// Cf_cr_sDlg 对话框




Cf_cr_sDlg::Cf_cr_sDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cf_cr_sDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cf_cr_sDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cf_cr_sDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_DISCONNECT, &Cf_cr_sDlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_CONNECT, &Cf_cr_sDlg::OnBnClickedConnect)
END_MESSAGE_MAP()


// Cf_cr_sDlg 消息处理程序

BOOL Cf_cr_sDlg::OnInitDialog()
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
	DlgInitialize();
	ListenThread=NULL;
	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cf_cr_sDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cf_cr_sDlg::OnPaint()
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
HCURSOR Cf_cr_sDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void Cf_cr_sDlg::DlgInitialize()//firstset
{
	EnableWindow(IDC_DISCONNECT,FALSE);
	SetDlgItemText(IDC_PORT,_T("8008"));
}

BOOL Cf_cr_sDlg::EnableWindow(UINT uID,BOOL bEnable)
{
	return GetDlgItem(uID)->EnableWindow(bEnable);
}

BOOL SOCKET_Select(SOCKET hSocket,int nTimeOut,BOOL bRead)//监视的socket,超时时间,监视可读性socket还是可写性socket 
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);//对fdset清0 
	FD_SET(hSocket,&fdset);//把监听的socket放到fdset中 
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

void Cf_cr_sDlg::SendMsg(CString strMsg,CClientItem *pNotSend)//发送函数
{
	TCHAR szBuf[1024]={0};
	_tcscpy_s(szBuf,1024,strMsg);

	for(INT_PTR idx=0;idx<ClientArray.GetCount();idx++)
	{
			send(ClientArray.GetAt(idx).m_Socket,(char*)szBuf,_tcslen(szBuf)*sizeof(TCHAR),0);
	}
}

DWORD WINAPI listen_thread(LPVOID pParam)
{
	Cf_cr_sDlg *pf_cr_s=(Cf_cr_sDlg*)pParam;
	ASSERT(pf_cr_s!=NULL);
	pf_cr_s->ListenSock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(pf_cr_s->ListenSock==INVALID_SOCKET)
	{
		AfxMessageBox(_T("新建SOCKET失败"));
		return FALSE;
	}
	int port=pf_cr_s->GetDlgItemInt(IDC_PORT);
	if(port<=0||port>65535)
	{
		AfxMessageBox(_T("输入的端口超出范围(1-65535)"));
		closesocket(pf_cr_s->ListenSock);
		return TRUE;
	}
	sockaddr_in service;
	service.sin_family=AF_INET;
	service.sin_addr.s_addr=INADDR_ANY;
	service.sin_port=htons(port);

	if(bind(pf_cr_s->ListenSock,(sockaddr*)&service,sizeof(sockaddr_in))==SOCKET_ERROR)
	{
		AfxMessageBox(_T("绑定端口失败"));
		closesocket(pf_cr_s->ListenSock);
		return TRUE;
	}
	if(listen(pf_cr_s->ListenSock,5)==SOCKET_ERROR)
	{
		AfxMessageBox(_T("监听失败"));
		closesocket(pf_cr_s->ListenSock);
		return TRUE;
	}
	pf_cr_s->EnableWindow(IDC_DISCONNECT,TRUE);
	pf_cr_s->EnableWindow(IDC_PORT,FALSE);
	pf_cr_s->EnableWindow(IDC_CONNECT,FALSE);
	while(TRUE)
	{
		if(SOCKET_Select(pf_cr_s->ListenSock,100,TRUE))
		{
			sockaddr_in clientAddr;
			int iLen=sizeof(sockaddr_in);
			SOCKET accSock=accept(pf_cr_s->ListenSock,(struct sockaddr*)&clientAddr,&iLen);
			if(accSock==INVALID_SOCKET)
				continue;
			//收到连接后的工作
			//添加客户端到队列
			CString RecvName;
			TCHAR NameBuf[1024]={0};
			recv(accSock,(char*)NameBuf,1024,0);
			RecvName.Format(_T("%s"),NameBuf);
			BOOL count=0;
			for(int idx=0;idx<pf_cr_s->ClientArray.GetCount();idx++)//name重复验证
			{
				CClientItem tItem=pf_cr_s->ClientArray.GetAt(idx);
				if(tItem.m_name==RecvName)
				{
					CString SndName=_T("昵称重复,请更改昵称后重新连接");
					send(accSock,(char*)SndName.GetBuffer(),SndName.GetLength()*sizeof(TCHAR),0);
					count=1;
				}
			}
			if(count==1)
				continue;
			CClientItem tItem;
			tItem.m_name=RecvName;
			tItem.m_Socket=accSock;//用户socket
			tItem.m_strIp=inet_ntoa(clientAddr.sin_addr);//inet_ntoa 将网络字节换成本地字符串 用户ip
			tItem.m_pMainWnd=pf_cr_s;
			INT_PTR idx=pf_cr_s->ClientArray.Add(tItem);
			tItem.hThread=CreateThread(NULL,0,ClientThreadProc,&(pf_cr_s->ClientArray.GetAt(idx)),CREATE_SUSPENDED,NULL);
			//创建显示信息线程(安全性(NULL),堆栈大小(默认0),线程地址,//,线程初始化状态,线程id默认null) 
			pf_cr_s->ClientArray.GetAt(idx).hThread=tItem.hThread;
			ResumeThread(tItem.hThread);
			Sleep(100);
		}
	}
	closesocket(pf_cr_s->ListenSock);
	return TRUE;
}


void Cf_cr_sDlg::RemoveClient(CClientItem in_Item)//移除用户连接函数
{
	for(int idx=0;idx<ClientArray.GetCount();idx++)
	{
		CClientItem tItem=ClientArray.GetAt(idx);
		if(tItem.m_Socket==in_Item.m_Socket&&
			tItem.hThread==in_Item.hThread&&
			tItem.m_strIp==in_Item.m_strIp)
		{
			ClientArray.RemoveAt(idx);
		}
	}
}

DWORD WINAPI ClientThreadProc(LPVOID IpParameter)//服务器发出发消息
{
	CString strMsg;
	CClientItem m_ClientItem=*(CClientItem*)IpParameter;
	while(TRUE)
	{
		if(SOCKET_Select(m_ClientItem.m_Socket,100,TRUE))
		{
			TCHAR szBuf[1024]={0};
			int iRet=recv(m_ClientItem.m_Socket,(char*)szBuf,1024,0);
			if(iRet>0)
			{
				strMsg.Format(_T("%s"),szBuf);
				strMsg=m_ClientItem.m_name+_T(":")+strMsg;
				m_ClientItem.m_pMainWnd->SendMsg(strMsg,&m_ClientItem);
			}
			else
			{
				strMsg=m_ClientItem.m_name+_T("离开了聊天室");
				m_ClientItem.m_pMainWnd->SendMsg(strMsg,&m_ClientItem);
				m_ClientItem.m_pMainWnd->RemoveClient(m_ClientItem);
				break;
			}
		}
		Sleep(500);
	}
	return TRUE;
}

void Cf_cr_sDlg::OnBnClickedConnect()//点击连接
{
	ListenThread=CreateThread(NULL,0,listen_thread,this,0,NULL);
}
void Cf_cr_sDlg::OnBnClickedDisconnect()//断开连接
{
	closesocket(ListenSock);
	for(INT_PTR idx=0;idx<ClientArray.GetCount();idx++)
	{
		closesocket(ClientArray.GetAt(idx).m_Socket);
	}
	EnableWindow(IDC_DISCONNECT,FALSE);
	EnableWindow(IDC_PORT,TRUE);
	EnableWindow(IDC_CONNECT,TRUE);
}
