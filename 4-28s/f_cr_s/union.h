#pragma once

class Cf_cr_sDlg;
class CClientItem
{
public:
	CString m_strIp;//ip
	SOCKET m_Socket;//socket
	HANDLE hThread;
	Cf_cr_sDlg *m_pMainWnd;
	CString m_name;
	CClientItem()
	{
		m_pMainWnd=NULL;
		m_Socket=INVALID_SOCKET;
		hThread=NULL;
	}
};
DWORD WINAPI listen_thread(LPVOID pParam);
DWORD WINAPI ClientThreadProc(LPVOID IpParameter);
BOOL SOCKET_Select(SOCKET hSocket,int nTimeOut=100,BOOL bRead=FALSE);