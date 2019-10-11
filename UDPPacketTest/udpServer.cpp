// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include "afxsock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// The one and only application object


using namespace std;

unsigned int StartServer(LPVOID lParam)
{
	//SOCKET aSocket;
	UINT nPort = 8080;
#if 1
	//初始化Winscok
	if (!AfxSocketInit())
	{
		printf("AfxSocketInit failed\n");
		return 1;
	}

	printf("====AfxSocketInit done\n");
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

	//aSockaddr.sin_addr.s_addr = inet_addr("172.16.8.28");

	//aSockaddr.sin_addr = s;
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

	while (1)
	{
		char buf = 0;
		recvfrom(aSocket, &buf, sizeof(buf), 0, (struct sockaddr*) & cli, &len);
		printf("recv num =%hhd\n", buf);
	}

	//关闭
	closesocket(aSocket);

	return 0;
}
#if 0
unsigned int StartServer2(LPVOID lParam)
{
	UINT nPort = 5000;

	//初始化Winscok
	if (!AfxSocketInit())
	{
		printf("AfxSocketInit failed\n");
		return 1;
	}

	printf("====AfxSocketInit done\n");

	//创建 CSocket 对象
	CSocket aSocket;
	CString strIP = _T("127.0.0.1");

	if (!aSocket.Create(nPort, SOCK_DGRAM, L"127.0.0.1"))
	{
		char szMsg[1024] = { 0 };
		sprintf_s(szMsg, "create faild: %d", aSocket.GetLastError());
		printf(szMsg);
		return 1;
	}

	SOCKADDR sockAddr;

	sockAddr.sa_family = AF_INET;
	strcpy_s(sockAddr.sa_data, "127.0.0.1");

	if (!aSocket.Bind(&sockAddr, strlen("127.0.0.1"))) {
		printf("Bind failed: %d\n", aSocket.GetLastError());
	}

	return 0;
}
#endif
/*int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: code your application's behavior here.
			wprintf(L"Fatal Error: MFC initialization failed\n");
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		wprintf(L"Fatal Error: GetModuleHandle failed\n");
		nRetCode = 1;
	}

	StartServer(0);

	return nRetCode;
}*/
