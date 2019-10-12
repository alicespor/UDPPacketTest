// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "afxsock.h"
#include "udpClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

//CWinApp theApp;

using namespace std;

unsigned int StartClient2(LPVOID lParam)
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

	while (1)
	{
		printf("请输入一个数字：");
		char buf = 0;
		scanf_s("%hhd", &buf);
		sendto(sockfd, &buf,
			sizeof(buf), 0, (struct sockaddr*) & addr, sizeof(addr));
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

unsigned int StartClient(LPVOID lParam)
{
	//初始化
	AfxSocketInit();

	//创建 CSocket 对象
	CSocket aSocket;
	CString strIP = _T("127.0.0.1");
	CString strPort;
	CString strText = _T("I am client\n");

	int nPort = 5000;

	//初始化 CSocket 对象, 因为客户端不需要绑定任何端口和地址, 所以用默认参数即可
	if (!aSocket.Create(nPort, SOCK_DGRAM, L"127.0.0.1"))
	{
		char szMsg[1024] = { 0 };
		sprintf_s(szMsg, "create faild: %d", aSocket.GetLastError());
		printf(szMsg);
		return 1;
	}

	printf("===Create done\n");

	//连接指定的地址和端口
	if (aSocket.Connect(strIP, nPort))
	{
		char szRecValue[1024] = { 0 };

		printf("===Connect done\n");

		//发送内容给服务器
		aSocket.Send(strText, strText.GetLength());

		//接收服务器发送回来的内容(该方法会阻塞, 在此等待有内容接收到才继续向下执行)
		aSocket.Receive((void*)szRecValue, 1024);

		printf(szRecValue);
	}
	else
	{
		char szMsg[1024] = { 0 };
		sprintf_s(szMsg, "create faild: %d", aSocket.GetLastError());
		printf(szMsg);
	}

	//关闭
	aSocket.Close();
}

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

	StartClient2(0);

	return nRetCode;
}
*/