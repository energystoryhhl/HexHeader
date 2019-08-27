
// HeaxHeaderDlg.cpp : 实现文件
//

#include <map>

#include "stdafx.h"
#include "HeaxHeader.h"
#include "HeaxHeaderDlg.h"
#include "afxdialogex.h"

#include "AppendFile.h"
#include "openssl\sha.h"
#include "StringMethod.h"
#include "Command.h"
#include "Encrypt.h"

#include <io.h>
using namespace HexHeader;
using namespace FileUtil;
using namespace Detail;
using namespace Command;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma comment(lib,"libcrypto.lib")
#pragma comment(lib,"libssl.lib")

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
	DDX_Control(pDX, IDC_EDIT_Hex_Show, editHexShow_);
	DDX_Control(pDX, IDC_LIST1, listCtrlHexShow_);
	DDX_Control(pDX, IDC_EDIT1, editCtrlMsg_);
}

BEGIN_MESSAGE_MAP(CHeaxHeaderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CHeaxHeaderDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_Hex_Show, &CHeaxHeaderDlg::OnEnChangeEditHexShow)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDCANCEL, &CHeaxHeaderDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CHeaxHeaderDlg::OnOpenFileBnClicked)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CHeaxHeaderDlg::OnBtnSave)
	ON_BN_CLICKED(IDC_BUTTON_SAVEAS, &CHeaxHeaderDlg::On_BtnSaveAs)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CHeaxHeaderDlg::ON_CloseFile)
	ON_BN_CLICKED(IDC_BUTTON_DOSCRIPT, &CHeaxHeaderDlg::On_DoScript)
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
	SetListControl();

	p_fileOwner_.reset(new FileOwner);

	OpenPastFile();

	
	//if (LoadLibrary(_T("libcrypto-1_1.dll")) == NULL || LoadLibrary(_T("libssl-1_1.dll")) == NULL)
	//{
	//	MessageBox(_T("Load lib error"));
	//}
}

void CHeaxHeaderDlg::ShowConsole()
{
	AllocConsole();//打开控制台窗口
	freopen("CONOUT$", "w+t", stdout);
	freopen("CONIN$", "r+t", stdin);
	//TODO close consle on close app
}

void CHeaxHeaderDlg::SetListControl()
{
	listCtrlHexShow_.InsertColumn(0, CString(), LVCFMT_CENTER, 70);
	for (unsigned char i = 0; i < 16; i++)
	{
		char buf[3] = { 0 };
		sprintf(buf, "%02x", i);
		listCtrlHexShow_.InsertColumn(i+1, CString(buf), LVCFMT_CENTER, 30);
	}

	CImageList   m_l;
	m_l.Create(1, 8, TRUE | ILC_COLOR32, 1, 0);
	listCtrlHexShow_.SetImageList(&m_l, LVSIL_SMALL);

	listCtrlHexShow_.EnsureVisible(listCtrlHexShow_.GetItemCount() - 1, FALSE);
}

void CHeaxHeaderDlg::ListControlAddItems(vector<HexDataElemt_t>& v)
{

	for (int i = 0,j = 0; i < v.size(); i++,j++)
	{
		char buf[8] = { 0 };

		if ((i == 0) || ((i + 1) % 16 == 0))
		{
			unsigned char tmp = i;
			sprintf(buf, "%07x", tmp);
			//std::cout << buf;
			listCtrlHexShow_.InsertItem((i + 1) /16, CString(buf));
			//j++;
			
		}

		unsigned char tmp = v[i];
		sprintf(buf, "%02x", tmp);
		//std::cout << buf;
		listCtrlHexShow_.SetItemText(((i)/ 16), (i) / 16 == 0 ? j + 1:j, CString(buf));

		if (((i + 1) % 16 == 0))
		{
			j = 0;
		}
		

	}
}

void CHeaxHeaderDlg::OnOpenFile(CString &path)
{
	dropFilePath_ = path;

#ifdef HEXDEBUG
	USES_CONVERSION;
	char * pFileName = T2A(dropFilePath_);
	std::cout << "open file: " << pFileName << std::endl;
#endif

	editCtrlMsg_.SetWindowTextW(CString("open file: ") + dropFilePath_);

	assert(nullptr != p_fileOwner_);

	if (true == p_fileOwner_->ifOpen())
	{
		p_fileOwner_->close();
	}

	string spath(pFileName);

	p_fileOwner_->open(spath);

	listCtrlHexShow_.DeleteAllItems();

	ListControlAddItems(p_fileOwner_->file().buffer());

}

bool CHeaxHeaderDlg::SaveAs(CString & path)
{
	dropFilePath_ = path;

	if (path == CString())
		return false;

#ifdef HEXDEBUG
	USES_CONVERSION;
	char * pFileName = T2A(dropFilePath_);
	std::cout << "save file: " << pFileName << std::endl;
#endif

	assert(nullptr != p_fileOwner_);

	string spath(pFileName);
	return p_fileOwner_->saveAs(spath.c_str());
}

bool CHeaxHeaderDlg::Save()
{
	//dropFilePath_ = path;

//#ifdef HEXDEBUG
//	USES_CONVERSION;
//	char * pFileName = T2A(dropFilePath_);
//	std::cout << "open file: " << pFileName << std::endl;
//#endif

	//editCtrlMsg_.SetWindowTextW(CString("save "));

	//assert(nullptr != p_fileOwner_);

	//string spath(pFileName);
	return p_fileOwner_->save();

	//return false;
}

CString CHeaxHeaderDlg::FilePathBox()
{

	TCHAR szFilter[] = _T("hex文件(*.hex)|*.hex|bin文件(*.bin)|*.bin|dat文件(*.dat)|*.dat|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("OpenFile"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		dropFilePath_ = strFilePath;
		return strFilePath;
	}
	else 
	{
		return CString();
	}
}

CString CHeaxHeaderDlg::FilePathBoxSaveAs()
{
	CFileDialog fileDlg(FALSE, _T("hex"), _T("new.hex"));//FALSE表示为“另存为”对话框，否则为“打开”对话框
	if (fileDlg.DoModal() == IDOK)
	{

		CString strFile = fileDlg.GetPathName();//获取完整路径
		dropFilePath_ = strFile;
		return strFile;

#ifdef HEXDEBUG
		USES_CONVERSION;
		char * pFileName = T2A(strFile);
		std::cout << "open file: " << pFileName << std::endl;
#endif
		//CString  strEdit1, strEdit2;
		//GetDlgItemText(IDC_EDIT1, strEdit1);//获取指定ID的编辑框内容

		//GetDlgItemText(IDC_EDIT2,strEdit2);//同上
		//CStdioFile file;
		//if (file.Open(strFile, CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeWrite))//创建/打开文件
		//{
		//	file.WriteString(strEdit1);//写入内容
		//	file.WriteString(_T("\r\n"));//换行
		//	file.WriteString(strEdit2);//写入内容
		//	file.Close();//关闭输出文件
		//}
	}
	else
	{
		return CString();
	}
}


bool TraverseFiles(string path, int &file_num)
{
	_finddata_t file_info;
	string current_path = path + "/*.*"; //可以定义后面的后缀为*.exe，*.txt等来查找特定后缀的文件，*.*是通配符，匹配所有类型,路径连接符最好是左斜杠/，可跨平台
										 //打开文件查找句柄
	int handle = _findfirst(current_path.c_str(), &file_info);
	//返回值为-1则查找失败
	if (-1 == handle)
		return false;
	do
	{
		//判断是否子目录
		string attribute;
		if (file_info.attrib == _A_SUBDIR) //是目录
			attribute = "dir";
		else
			attribute = "file";
		//输出文件信息并计数,文件名(带后缀)、文件最后修改时间、文件字节数(文件夹显示0)、文件是否目录
		cout << file_info.name << ' ' << file_info.time_write << ' ' << file_info.size << ' ' << attribute << endl; //获得的最后修改时间是time_t格式的长整型，需要用其他方法转成正常时间显示
		file_num++;

	} while (!_findnext(handle, &file_info));  //返回0则遍历完
											   //关闭文件句柄
	_findclose(handle);
	return true;
}

bool FinDir(string path, string dir)
{
	_finddata_t file_info;
	string current_path = path + "/*"; //可以定义后面的后缀为*.exe，*.txt等来查找特定后缀的文件，*.*是通配符，匹配所有类型,路径连接符最好是左斜杠/，可跨平台
										 //打开文件查找句柄
	int handle = _findfirst(current_path.c_str(), &file_info);
	//返回值为-1则查找失败
	if (-1 == handle)
		return false;
	do
	{
		//判断是否子目录
		string attribute;
		if (file_info.attrib == _A_SUBDIR && ( dir == string(file_info.name))) //是目录
		{
			return true;
			//break;
		}
		
	} while (!_findnext(handle, &file_info));  //返回0则遍历完
											   //关闭文件句柄
	_findclose(handle);
	return false;
}

bool FindFile(string path, string file)
{
	_finddata_t file_info;
	string current_path = path + "/*"; //可以定义后面的后缀为*.exe，*.txt等来查找特定后缀的文件，*.*是通配符，匹配所有类型,路径连接符最好是左斜杠/，可跨平台
										 //打开文件查找句柄
	int handle = _findfirst(current_path.c_str(), &file_info);
	//返回值为-1则查找失败
	if (-1 == handle)
		return false;
	do
	{
		//判断是否子目录
		string attribute;
		if (file_info.attrib != _A_SUBDIR && (file == string(file_info.name)) ) //!目录
		{
			return true;
		}

	} while (!_findnext(handle, &file_info));  //返回0则遍历完
											   //关闭文件句柄
	_findclose(handle);
	return false;
}

bool CHeaxHeaderDlg::OpenPastFile()
{
	struct _finddata_t fileinfo;
	long hFile = 0;
	
	int a;
	//TraverseFiles(".\\", a);
	FILE * pFile = NULL;

	if (FinDir(".\\","Config") == false)
	{
		CreateDirectoryA("Config", NULL);
		pFile = fopen(".\\Config.\\lastOpen.dat","a+");
		fclose(pFile);
	}
	else
	{
		if (false == FindFile(".\\Config", "lastOpen.dat"))
		{
			pFile = fopen(".\\Config\\lastOpen.dat", "a+");
			fclose(pFile);
		}
	}
	AppendFile lastOpenFile(".\\Config\\lastOpen.dat","a+");
	editHexShow_.SetWindowTextW(CString(lastOpenFile.buffer().data()));
	return true;
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

	/*
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

	editHexShow_.SetWindowTextW(CString(file.bufferToString().c_str()).MakeUpper());
	*/


	//listCtrlHexShow_.InsertItem(0,  _T("ff"));
	//listCtrlHexShow_.SetItemText(1, 1, _T("item"));


	ListControlAddItems(file.buffer());

	////////////////
	char string1[] = "11223344";

	unsigned char md[33] = { 0 };

	SHA256( (const unsigned char *) string1, sizeof(string1)-1, md);

	for (int i = 0; i < 33; i++)
	{
		unsigned char tmp = md[i];
		printf("0x%02x ", tmp);
	}
	//////////////////

	

}


void CHeaxHeaderDlg::OnEnChangeEditHexShow()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CHeaxHeaderDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	UINT count;
	TCHAR filePath[MAX_PATH] = { 0 };

	count = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);//从成功的拖放操作中检索文件的名称。并取代被拖拽文件的数目
	if (count == 1)//如果只拖拽一个文件夹
	{
		DragQueryFile(hDropInfo, 0, filePath, sizeof(filePath));//获得拖拽的文件名
		dropFilePath_ = filePath;
		//UpdateData(FALSE);
		DragFinish(hDropInfo);//拖放成功后，释放内存

		CDialog::OnDropFiles(hDropInfo);

		OnOpenFile(dropFilePath_);

		//editCtrlMsg_.SetWindowTextW(_T("open file:") + dropFilePath_);
		return;

	}
	else//如果拖拽多个文件夹
	{
		//m_vectorFile.clear();
		for (UINT i = 0; i<count; i++)
		{
			int pathLen = DragQueryFile(hDropInfo, i, filePath, sizeof(filePath));
			dropFilePath_ = filePath;
			//m_vectorFile.push_back(filePath);
			//break;
		}
		OnOpenFile(dropFilePath_);
		//UpdateData(FALSE);
		DragFinish(hDropInfo);
	}
	
	
	CDialogEx::OnDropFiles(hDropInfo);
}


void CHeaxHeaderDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	AppendFile lastOpenFile(".\\Config\\lastOpen.dat", "w+");
	//editHexShow_.SetWindowTextW(CString(lastOpenFile.buffer().data()));
	CString cstr;
	editHexShow_.GetWindowTextW(cstr);
	
	string str = Wchr2str(cstr);

	str.append("\0");

	lastOpenFile.write((char *)str.c_str(), str.length()+1);

	
	CDialogEx::OnCancel();
}


void CHeaxHeaderDlg::OnOpenFileBnClicked()
{
	OnOpenFile(FilePathBox());
}


void CHeaxHeaderDlg::OnBtnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	if (true == Save())
	{
		USES_CONVERSION;
		char * pFileName = T2A(dropFilePath_);

		//p_fileOwner_->open(string(pFileName));

		listCtrlHexShow_.DeleteAllItems();

		ListControlAddItems(p_fileOwner_->file().buffer());

		editCtrlMsg_.SetWindowTextW(CString("save ") + dropFilePath_);
	}
		
	else
		MessageBox(CString("Save Error"));
}


void CHeaxHeaderDlg::On_BtnSaveAs()
{
	// TODO: 在此添加控件通知处理程序代码
	if (p_fileOwner_->ifOpen() == false)
	{
		editCtrlMsg_.SetWindowTextW(CString("ERROR: No File opened! "));
		return;
	}
	if (true == SaveAs(FilePathBoxSaveAs()))
	{
		USES_CONVERSION;
		char * pFileName = T2A(dropFilePath_);
		p_fileOwner_->close();
		p_fileOwner_->open(string(pFileName));
		listCtrlHexShow_.DeleteAllItems();
		ListControlAddItems(p_fileOwner_->file().buffer());
		editCtrlMsg_.SetWindowTextW(CString("save as: ") + dropFilePath_);
	}	
	else
		MessageBox(CString("Save Error"));
}

BOOL  CHeaxHeaderDlg::PreTranslateMessage(MSG * pMsg)
{
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{

		if (GetFocus() == GetDlgItem(IDC_EDIT_Hex_Show))
		{
			CString strChat;
			editHexShow_.GetWindowTextW(strChat);
			strChat.Append(_T("\r\n"));
			editHexShow_.SetWindowTextW(strChat);
			editHexShow_.SetSel(100000, 100000);
		}
		return true;
	}
	return CDialogEx::PreTranslateMessage(pMsg);	
}


void CHeaxHeaderDlg::ON_CloseFile()
{
	if (p_fileOwner_->ifOpen() == false)
	{
		editCtrlMsg_.SetWindowTextW(CString("ERROR: No File opened! "));
		return;
	}

	p_fileOwner_->close();
	listCtrlHexShow_.DeleteAllItems();

	editCtrlMsg_.SetWindowTextW(CString("Close File ") + dropFilePath_);
	//p_fileOwner_->ifOpen = false;
}


void CHeaxHeaderDlg::On_DoScript()
{
	// TODO: 在此添加控件通知处理程序代码

	if (p_fileOwner_->ifOpen() == false)
	{
		editCtrlMsg_.SetWindowTextW(CString("No File Opened"));
		return;
	}
		

	CString scriptLines;
	editHexShow_.GetWindowTextW(scriptLines);
	string cmdLines = Wchr2str(scriptLines);
	
	if (cmdLines == "")
		return;

	std::cout << cmdLines << endl;

	vector<string> lines = CmdLine(cmdLines, "\r\n").elemts();

	/*start script*/
	//map<string, unsigned int> envVar;

	int num = 0;
	bool opFlag = false;
	bool encryptFlag = false;
	///*pre */
	//for (auto i : lines)
	//{
	//	if (i.find("="))
	//	{
	//		vector<string> eles = CmdLine(i, "=").elemts();
	//		for (auto ee : eles)
	//		{
	//			cout << ee << endl;
	//		}
	//		//envVar.insert(pair<string, unsigned int>(eles[0], string_as_T<unsigned int>(eles[1])));
	//		cmdLines.replace(cmdLines.begin(), cmdLines.end(),"hexaddr=256","0xff");
	//		//cmdLines.replace()
	//		continue;
	//	}
	//}
	vector<HexDataElemt_t> hex;
	for (auto i : lines)
	{
		std::cout << "opcode_ " << num <<": "<< i << endl;

		if (i.size() <= 1)
			continue;

		for (auto op : opcodes)
		{
			if (i.find(op) != std::string::npos)
			{
				opFlag = true;
				break;
			}
		}

		for (auto enc : encryptcodes)
		{
			if (i.find(enc) != std::string::npos)
			{
				encryptFlag = true;
				break;
			}
		}


		if ((i.find("0x") != std::string::npos))
		{
			str2UcArray(hex, i);
			continue;
		}

		if (opFlag)
		{
			
			vector<string> op= CmdLine(i, " ").elemts();  //demli the string

			AppendFile * file = &p_fileOwner_->file();

			Operation operation(file, hex, op);

			
			int ret = operation.doOperation();
			if (ret!= 1)
			{
				cout << ErrorCodeString[ret * -1 -1].c_str() <<endl;
				MessageBox(CString(ErrorCodeString[-1*ret-1].c_str()));
				hex.clear();
			}
			else
			{
				listCtrlHexShow_.DeleteAllItems();
				ListControlAddItems(p_fileOwner_->file().buffer());
				hex.clear();
				editCtrlMsg_.SetWindowTextW( CString(op[0].c_str()) + CString(" Done"));
			}
			opFlag = false;
		}

		if (encryptFlag == true)
		{
			//SHA256()
			vector<string> op = CmdLine(i, " ").elemts();
			Encrypt::EncryptBase encry(op, hex, p_fileOwner_->file());
			if (encry.doEncrypt() == false)
			{
				cout << "encrypt ERROR" << endl;
			}

			for (auto i : hex)
			{
				printf(" %02x ", i);
			}

			encryptFlag = false;
		}




		num++;
	}
	
	

}
