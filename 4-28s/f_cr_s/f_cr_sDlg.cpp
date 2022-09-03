// f_cr_sDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "f_cr_s.h"
#include "f_cr_sDlg.h"
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


// Cf_cr_sDlg �Ի���




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


// Cf_cr_sDlg ��Ϣ�������

BOOL Cf_cr_sDlg::OnInitDialog()
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
	DlgInitialize();
	ListenThread=NULL;
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cf_cr_sDlg::OnPaint()
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

BOOL SOCKET_Select(SOCKET hSocket,int nTimeOut,BOOL bRead)//���ӵ�socket,��ʱʱ��,���ӿɶ���socket���ǿ�д��socket 
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);//��fdset��0 
	FD_SET(hSocket,&fdset);//�Ѽ�����socket�ŵ�fdset�� 
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

void Cf_cr_sDlg::SendMsg(CString strMsg,CClientItem *pNotSend)//���ͺ���
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
		AfxMessageBox(_T("�½�SOCKETʧ��"));
		return FALSE;
	}
	int port=pf_cr_s->GetDlgItemInt(IDC_PORT);
	if(port<=0||port>65535)
	{
		AfxMessageBox(_T("����Ķ˿ڳ�����Χ(1-65535)"));
		closesocket(pf_cr_s->ListenSock);
		return TRUE;
	}
	sockaddr_in service;
	service.sin_family=AF_INET;
	service.sin_addr.s_addr=INADDR_ANY;
	service.sin_port=htons(port);

	if(bind(pf_cr_s->ListenSock,(sockaddr*)&service,sizeof(sockaddr_in))==SOCKET_ERROR)
	{
		AfxMessageBox(_T("�󶨶˿�ʧ��"));
		closesocket(pf_cr_s->ListenSock);
		return TRUE;
	}
	if(listen(pf_cr_s->ListenSock,5)==SOCKET_ERROR)
	{
		AfxMessageBox(_T("����ʧ��"));
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
			//�յ����Ӻ�Ĺ���
			//��ӿͻ��˵�����
			CString RecvName;
			TCHAR NameBuf[1024]={0};
			recv(accSock,(char*)NameBuf,1024,0);
			RecvName.Format(_T("%s"),NameBuf);
			BOOL count=0;
			for(int idx=0;idx<pf_cr_s->ClientArray.GetCount();idx++)//name�ظ���֤
			{
				CClientItem tItem=pf_cr_s->ClientArray.GetAt(idx);
				if(tItem.m_name==RecvName)
				{
					CString SndName=_T("�ǳ��ظ�,������ǳƺ���������");
					send(accSock,(char*)SndName.GetBuffer(),SndName.GetLength()*sizeof(TCHAR),0);
					count=1;
				}
			}
			if(count==1)
				continue;
			CClientItem tItem;
			tItem.m_name=RecvName;
			tItem.m_Socket=accSock;//�û�socket
			tItem.m_strIp=inet_ntoa(clientAddr.sin_addr);//inet_ntoa �������ֽڻ��ɱ����ַ��� �û�ip
			tItem.m_pMainWnd=pf_cr_s;
			INT_PTR idx=pf_cr_s->ClientArray.Add(tItem);
			tItem.hThread=CreateThread(NULL,0,ClientThreadProc,&(pf_cr_s->ClientArray.GetAt(idx)),CREATE_SUSPENDED,NULL);
			//������ʾ��Ϣ�߳�(��ȫ��(NULL),��ջ��С(Ĭ��0),�̵߳�ַ,//,�̳߳�ʼ��״̬,�߳�idĬ��null) 
			pf_cr_s->ClientArray.GetAt(idx).hThread=tItem.hThread;
			ResumeThread(tItem.hThread);
			Sleep(100);
		}
	}
	closesocket(pf_cr_s->ListenSock);
	return TRUE;
}


void Cf_cr_sDlg::RemoveClient(CClientItem in_Item)//�Ƴ��û����Ӻ���
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

DWORD WINAPI ClientThreadProc(LPVOID IpParameter)//��������������Ϣ
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
				strMsg=m_ClientItem.m_name+_T("�뿪��������");
				m_ClientItem.m_pMainWnd->SendMsg(strMsg,&m_ClientItem);
				m_ClientItem.m_pMainWnd->RemoveClient(m_ClientItem);
				break;
			}
		}
		Sleep(500);
	}
	return TRUE;
}

void Cf_cr_sDlg::OnBnClickedConnect()//�������
{
	ListenThread=CreateThread(NULL,0,listen_thread,this,0,NULL);
}
void Cf_cr_sDlg::OnBnClickedDisconnect()//�Ͽ�����
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
