
// HeaxHeaderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HeaxHeader.h"
#include "HeaxHeaderDlg.h"
#include "afxdialogex.h"

#include "AppendFile.h"

using namespace HexHeader;
using namespace FileUtil;

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


// CHeaxHeaderDlg 对话框



CHeaxHeaderDlg::CHeaxHeaderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HEAXHEADER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHeaxHeaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHeaxHeaderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHeaxHeaderDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHeaxHeaderDlg 消息处理程序

BOOL CHeaxHeaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	DoUserInit();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHeaxHeaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHeaxHeaderDlg::OnPaint()
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
HCURSOR CHeaxHeaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHeaxHeaderDlg::DoUserInit()
{
	ShowConsole();
}

void CHeaxHeaderDlg::ShowConsole()
{
	AllocConsole();//打开控制台窗口
	freopen("CONOUT$", "w+t", stdout);
	freopen("CONIN$", "r+t", stdin);
	//TODO close consle on close app
}

void CHeaxHeaderDlg::OnBnClickedOk()
{


	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	
	//BinaryFile file("data.dat");


	char buf[254];
	for (unsigned char i = 0; i < 254; i++)
	{
		buf[i] = i;
	}
	
	/*
		BinaryFile bfile("data.dat");
	bfile.write(buf, 254);
	bfile.close();
	*/



	AppendFile file("data.dat");
	std::cout<<file.bufferToString();

	std::cout << endl;
	std::cout << "file.size()"<<file.size();
	std::cout << endl;
	std::cout << "file.fileSize()" << file.fileSize();
	std::cout << endl;

	char buffer[] = { 0xaa,0xaa,0xaa,0xaa };


	HexData_t data(buffer,buffer+4);

	file.insert(0, data.begin(), 4);

	std::cout << "after insert\n";

	std::cout << file.bufferToString();

	char buffer2[] = { 0xaa,0xbb,0xcc,0xee ,0xff};

	HexData_t data2(buffer2, buffer2 + sizeof(buffer2));

	file.cover(2, data2.begin(), data2.size());

	std::cout << "after cover\n";

	std::cout << file.bufferToString();



}
