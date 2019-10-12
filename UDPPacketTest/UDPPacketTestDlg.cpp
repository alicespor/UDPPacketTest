
// UDPPacketTestDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "UDPPacketTest.h"
#include "UDPPacketTestDlg.h"
#include "afxdialogex.h"
#include "udpServer.h"
#include "udpClient.h"
#include <afxwin.h>
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUDPPacketTestDlg 对话框


CUDPPacketTestDlg::CUDPPacketTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UDPPACKETTEST_DIALOG, pParent)
	, m_bStopClient(false)
	, m_bStopServer(false)
	, m_pFile(NULL)
	, m_bStopWrite(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDPPacketTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUDPPacketTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONCLIENT, &CUDPPacketTestDlg::OnBnClickedButtonClient)
	ON_BN_CLICKED(IDC_BUTTONSERVER, &CUDPPacketTestDlg::OnBnClickedButtonServer)
	ON_BN_CLICKED(IDC_BUTTONSTOP, &CUDPPacketTestDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CUDPPacketTestDlg 消息处理程序

BOOL CUDPPacketTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	WriteLogBegin();
	WriteLog("Start Log.");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUDPPacketTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
		switch (nID)
		{
		case SC_CLOSE:
		{
			OnUnInitDialog();
		}
		}
	}
}

void CUDPPacketTestDlg::OnUnInitDialog()
{
	WriteLog("OnUnInitDialog in.\r\n");
	if (m_pFile)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}


	WriteLog("OnUnInitDialog, End Log.\r\n");
	WriteLogEnd();

}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUDPPacketTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUDPPacketTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUDPPacketTestDlg::OnBnClickedButtonClient()
{
	AfxBeginThread(StartUDPClient, this, THREAD_PRIORITY_NORMAL, 0, 0);
}

UINT __cdecl CUDPPacketTestDlg::StartUDPClient(LPVOID lparam)
{
	int iRes = ERROR_NONE;
	CUDPPacketTestDlg *threadol = (CUDPPacketTestDlg*)lparam;
	threadol->StartClient2(0);
	return 0;
}

unsigned int CUDPPacketTestDlg::StartClient2(LPVOID lParam)
{
#if 1
	//初始化Winscok
	if (!AfxSocketInit())
	{
		printf("AfxSocketInit failed\n");
		return 1;
	}

	printf("====AfxSocketInit done\n");
#endif
	//创建socket对象
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == INVALID_SOCKET)
	{
		printf("Create failed\n");
		return 1;
	}

	printf("====Create done\n");
	//创建网络通信对象
	struct sockaddr_in addr;
	struct in_addr s;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	//addr.sin_addr.s_addr = inet_addr("192.168.0.143");
	inet_pton(AF_INET, "127.0.0.1", (void*) & (addr.sin_addr));

	while (!m_bStopClient)
	{
		char buf = 'a';
		sendto(sockfd, &buf,
			sizeof(buf), 0, (struct sockaddr*) & addr, sizeof(addr));
		WriteLog("char a.\r\n");
#if 0
		socklen_t len = sizeof(addr);
		recvfrom(sockfd, &buf, sizeof(buf), 0, (struct sockaddr*) & addr, &len);

		if (66 == buf)
		{
			printf(" server 成功接受\n");
		}
		else
		{
			printf("server 数据丢失\n");
		}
#endif
	}
	closesocket(sockfd);

}


void CUDPPacketTestDlg::OnBnClickedButtonServer()
{
	WriteLog("onBnClickedButtonServer in.\r\n");
	AfxBeginThread(StartUDPServer, this, THREAD_PRIORITY_NORMAL, 0, 0);
	if (!m_pFile)
	{
		m_pFile = fopen("c:\\UDPPacketTest.txt", "w+");
		if (NULL == m_pFile)
		{
			WriteLog("fopen failed.\r\n");
		}
	}
	AfxBeginThread(WriteDataThread, this, THREAD_PRIORITY_NORMAL, 0, 0);
}


UINT __cdecl CUDPPacketTestDlg::StartUDPServer(LPVOID lparam)
{
	CUDPPacketTestDlg * threadol = (CUDPPacketTestDlg*)lparam;
	threadol->StartServer(0);
	return 0;
}


unsigned int CUDPPacketTestDlg::StartServer(LPVOID lParam)
{
	//SOCKET aSocket;
	UINT nPort = 8080;
#if 1
	//初始化Winscok
	if (!AfxSocketInit())
	{
		WriteLog("AfxSocketInit failed\n");
		return 1;
	}

	WriteLog("====AfxSocketInit done\n");
#endif
	//寻址相关结构
	sockaddr_in serverSockaddr;
	memset(&serverSockaddr, 0, sizeof(serverSockaddr));
	int aSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (aSocket == INVALID_SOCKET)
	{
		printf("Create failed\n");
		return 1;
	}

	printf("====Create done\n");

	//寻址相关结构
	sockaddr_in aSockaddr;
	struct in_addr s;

	memset(&aSockaddr, 0, sizeof(aSockaddr));
	aSockaddr.sin_family = AF_INET;

	inet_pton(AF_INET, "127.0.0.1", (void *)&(aSockaddr.sin_addr));
	aSockaddr.sin_port = htons((u_short)nPort);

	//绑定: 注意参数的类型转换
	if (bind(aSocket, (sockaddr*)& aSockaddr, sizeof(aSockaddr)) == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		printf("Bind failed, err = %d.\n", err);
		return 1;
	}

	printf("===Bind done\n");

	struct sockaddr_in cli;
	socklen_t len = sizeof(cli);

	while (!m_bStopServer)
	{
		char buf = 0;
		recvfrom(aSocket, &buf, sizeof(buf), 0, (struct sockaddr*) & cli, &len);
		printf("recv character %c = %hhd, len = %d.\n", buf, buf, len);

		char * pData = (char*)malloc(sizeof(char));
		memcpy(pData, &buf, sizeof(char)*1);

		m_clsMutex.Lock();
		m_listDataUnit.push_back(pData);
		m_clsMutex.Unlock();
	}

	//关闭
	closesocket(aSocket);

	return 0;
}

UINT __cdecl CUDPPacketTestDlg::WriteDataThread(LPVOID lParam)
{
	CUDPPacketTestDlg* pThis = (CUDPPacketTestDlg*)lParam;

	while (!pThis->m_bStopWrite)
	{
        pThis->WriteData();
	}

	pThis->WriteData();

	if (pThis->m_pFile)
	{
		fclose(pThis->m_pFile);
		pThis->m_pFile = NULL;
	}
	return 0;

}

void CUDPPacketTestDlg::WriteData()
{
   WriteLog("WriteData,in.\r\n");
	while (m_listDataUnit.size() > 0)
	{
	    int len = m_listDataUnit.size();
	    WriteLog("WriteData,m_listDataUnit len = %d.\r\n", len);
		fwrite(m_listDataUnit[0], sizeof(char) * 1, 1, m_pFile);
		free(m_listDataUnit[0]);
		m_listDataUnit[0] = NULL;

		m_clsMutex.Lock();
		vector<char*>::iterator k = m_listDataUnit.begin();
		m_listDataUnit.erase(k);
		m_clsMutex.Unlock();
	}
	
	return;
}


void CUDPPacketTestDlg::OnBnClickedButtonStop()
{
	m_bStopServer = true;
	m_bStopClient = true;
	m_bStopWrite = true;
}
