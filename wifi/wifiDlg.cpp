// wifiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "wifi.h"
#include "wifiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include < mmsystem.h >          //���ͷ�ļ��Ǹ�ʲô�ļǲ����ˣ��Ǻ�

#define WM_NOTIFYICON	WM_USER+5  //�Զ�����Ϣ��ID
#define IDI_ICON		0x0005     //ͼ��ID



CString ip;
int doit() 
{
	ip="";
	char host_name[255]; 
	//��ȡ������������ 
	if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR) { 
		return 1; 
	} 
	//�����������ݿ��еõ���Ӧ�ġ������� 
	struct hostent *phe = gethostbyname(host_name); 
	if (phe == 0) { 
		return 1; 
	} 
	//ѭ���ó����ػ�������IP��ַ 
	for (int i = 0; phe->h_addr_list[i] != 0; ++i) { 
		struct in_addr addr; 
		memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr)); 
		//printf("%s\n", inet_ntoa(addr)); 
		ip += inet_ntoa(addr);
		ip += "\r\n";
	}
	return 0;
} 
int back_ip() 
{ 
	WSAData wsaData; 
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) 
	{
		return 255; 
	} 
	doit(); 
	WSACleanup(); 
} 

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

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


// CwifiDlg �Ի���




CwifiDlg::CwifiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CwifiDlg::IDD, pParent)
	, m_name(_T(""))
	, m_passwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CwifiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT1, m_passwd);
}

BEGIN_MESSAGE_MAP(CwifiDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CwifiDlg::OnBnClickedButton1)
	ON_WM_NOTIFYFORMAT()
	ON_MESSAGE(WM_NOTIFYICON, &CwifiDlg::OnNotifyIcon)
	ON_EN_CHANGE(IDC_EDIT3, &CwifiDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON2, &CwifiDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CwifiDlg ��Ϣ�������

BOOL CwifiDlg::OnInitDialog()
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

	ShowWindow(SW_NORMAL);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	back_ip();
	SetDlgItemText(IDC_EDIT3,ip);  //��ʾ�����Ϣ���༭��,��ˢ�´���
	UpdateWindow();

	NOTIFYICONDATA nd;
	nd.cbSize	= sizeof (NOTIFYICONDATA);
	nd.hWnd	= m_hWnd;
	nd.uID	= IDI_ICON;
	nd.uFlags	= NIF_ICON|NIF_MESSAGE|NIF_TIP;
	nd.uCallbackMessage= WM_NOTIFYICON;
	nd.hIcon	= m_hIcon;

	strcpy(nd.szTip, "wifi����");

	Shell_NotifyIcon(NIM_ADD, &nd);

	UpdateData(TRUE);
	m_help="�����鿴����";
	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CwifiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else  if(nID==SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
		
	}
	else if(nID==SC_CLOSE)
	{
		if(MessageBox("ȷ��Ҫ�˳���","",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
		{
			NOTIFYICONDATA nd;
			nd.cbSize	= sizeof (NOTIFYICONDATA);
			nd.hWnd	= m_hWnd;

			nd.uID	= IDI_ICON;
			nd.uFlags	= NIF_ICON|NIF_MESSAGE|NIF_TIP;
			nd.uCallbackMessage	= WM_NOTIFYICON;
			nd.hIcon	= m_hIcon;

			Shell_NotifyIcon(NIM_DELETE, &nd);
			

			CString cmd_c;
			cmd_c="netsh wlan set hostednetwork mode=disallow";
			//MessageBox(cmd_c,"aa",0);
			//cmd_c="net user "+m_name+" /add";

			SECURITY_ATTRIBUTES sa;
			HANDLE hRead,hWrite;  
			sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
			sa.lpSecurityDescriptor = NULL;  //ʹ��ϵͳĬ�ϵİ�ȫ������ 
			sa.bInheritHandle = TRUE;  //�����Ľ��̼̳о��

			if (!CreatePipe(&hRead,&hWrite,&sa,0))  //���������ܵ�
			{  
				MessageBox("CreatePipe Failed!","��ʾ",MB_OK | MB_ICONWARNING);  
				return;
			}

			STARTUPINFO si; 
			PROCESS_INFORMATION pi;

			ZeroMemory(&si,sizeof(STARTUPINFO));
			si.cb = sizeof(STARTUPINFO); 
			GetStartupInfo(&si); 
			si.hStdError = hWrite; 
			si.hStdOutput = hWrite;  //�´������̵ı�׼�������д�ܵ�һ��
			si.wShowWindow = SW_HIDE;  //���ش��� 
			si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;


			char cmdline[200]; 
			CString tmp;
			tmp.Format("cmd /C %s",cmd_c);
			sprintf(cmdline,"%s",tmp);
			if (!CreateProcess(NULL,cmdline,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))  //�����ӽ���
			{
				MessageBox("CreateProcess Failed!","��ʾ",MB_OK | MB_ICONWARNING);  
				return;
			}
			CloseHandle(hWrite);  //�رչܵ����

			//Sleep(1000);

			CDialog::OnSysCommand(nID, lParam);
		}
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CwifiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CwifiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CwifiDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString cmd_c;
	cmd_c="netsh wlan set hostednetwork mode=allow ssid="+m_name+" key="+m_passwd+"&&netsh wlan start hostednetwork";
	//MessageBox(cmd_c,"aa",0);
	//cmd_c="net user "+m_name+" /add";

	SECURITY_ATTRIBUTES sa;
	HANDLE hRead,hWrite;  
	sa.nLength = sizeof(SECURITY_ATTRIBUTES); 
	sa.lpSecurityDescriptor = NULL;  //ʹ��ϵͳĬ�ϵİ�ȫ������ 
	sa.bInheritHandle = TRUE;  //�����Ľ��̼̳о��

	if (!CreatePipe(&hRead,&hWrite,&sa,0))  //���������ܵ�
	{  
		MessageBox("CreatePipe Failed!","��ʾ",MB_OK | MB_ICONWARNING);  
		return;
	}

	STARTUPINFO si; 
	PROCESS_INFORMATION pi;

	ZeroMemory(&si,sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO); 
	GetStartupInfo(&si); 
	si.hStdError = hWrite; 
	si.hStdOutput = hWrite;  //�´������̵ı�׼�������д�ܵ�һ��
	si.wShowWindow = SW_HIDE;  //���ش��� 
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;


	char cmdline[200]; 
	CString tmp;
	tmp.Format("cmd /C %s",cmd_c);
	sprintf(cmdline,"%s",tmp);
	

	if (!CreateProcess(NULL,cmdline,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))  //�����ӽ���
	{
		MessageBox("CreateProcess Failed!","��ʾ",MB_OK | MB_ICONWARNING);  
		return;
	}
	CloseHandle(hWrite);  //�رչܵ����
	Sleep(2000);
	

	char buffer[4096] = {0};
	DWORD bytesRead;
	

	MessageBox("����wifi�ѽ������������ڴ˻������״�ʹ������wifi�����ҵ����������ӡ��Ҽ����������ӵ�Internet���������ӣ�ѡ�����ԡ��������������ϡ���������*****����(N)����ѡ������WiFi��","",0);
	Sleep(4000);
	back_ip();
	SetDlgItemText(IDC_EDIT3,ip);  //��ʾ�����Ϣ���༭��,��ˢ�´���
	UpdateWindow();
	CloseHandle(hRead);
}



UINT CwifiDlg::OnNotifyFormat(CWnd *pWnd, UINT nCommand)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CDialog::OnNotifyFormat(pWnd, nCommand);
}

LRESULT CwifiDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
	if ((wParam == IDI_ICON)&&(lParam == WM_LBUTTONDOWN))
		ShowWindow(SW_SHOWNORMAL);
	return NULL;
}
void CwifiDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

bool f=true;

void CwifiDlg::OnEnSetfocusEdit5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(f)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	f=!f;

}

void CwifiDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(NULL,"open","http://blog.qiaoy.net",NULL,NULL,SW_SHOWNORMAL);
}
