
// UDPPacketTestDlg.h: 头文件
//

#pragma once
#include "CommonDefine.h"
#include "vector"
#include "ChartCtrl/ChartCtrl.h"

using namespace std;


// CUDPPacketTestDlg 对话框
class CUDPPacketTestDlg : public CDialogEx
{
// 构造
public:
	CUDPPacketTestDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UDPPACKETTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonClient();
	afx_msg void OnBnClickedButtonServer();
	void OnUnInitDialog();
	static UINT __cdecl StartUDPClient(LPVOID lparam);
	unsigned int StartClient2(LPVOID lParam);
	static UINT __cdecl StartUDPServer(LPVOID lparam);
	unsigned int StartServer(LPVOID lParam);
	afx_msg void OnBnClickedButtonStop();
	static UINT __cdecl WriteDataThread(LPVOID lParam);
	void WriteData();

	bool m_bStopClient;
	bool m_bStopServer;
	bool m_bStopWrite;
	FILE* m_pFile;
	vector<char*> m_listDataUnit;
	CMutex m_clsMutex;
	long int m_lFileSize;
	
	CEdit m_CEFileSize;


	//define for chart
	void testChart();
	void testChartDynamic();
	void OnTimer(UINT_PTR nIDEvent);
	void ChartCtrlInit();
	void DataBuffInit();
	void DataShow(double *xb, double *yb, int len);

	CChartCtrl m_ChartCtrl;
	CChartCtrl m_ChartCtrl2;
};
