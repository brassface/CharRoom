#pragma once

class Cf_cr_cDlg;
class CClientItem
{
public:
	CString m_strIp;//client_ip
	SOCKET m_Socket;//client_socket
	HANDLE hThread;
	Cf_cr_cDlg *m_pMainWnd;
	char m_name[20];
	CClientItem()
	{
		m_pMainWnd=NULL;
		m_Socket=INVALID_SOCKET;
		hThread=NULL;
	}
};
struct Message
{
	char strfrom[20];
	char strto[20];
	char strMsg[984];
};
BOOL SOCKET_Select(SOCKET hSocket,int nTimeOut=100,BOOL bRead=FALSE);