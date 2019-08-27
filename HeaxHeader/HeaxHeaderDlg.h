
// HeaxHeaderDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include <vector>
#include "FileOwner.h"
#include "AppendFile.h"
#include "BinaryFile.h"

#include <assert.h>
#include <memory>

using namespace HexHeader;

// CHeaxHeaderDlg 对话框
class CHeaxHeaderDlg : public CDialogEx
{
// 构造
public:
	CHeaxHeaderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HEAXHEADER_DIALOG };
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

	//user define
	void DoUserInit();

	void ShowConsole();

	void SetListControl();

	void ListControlAddItems(std::vector<HexDataElemt_t> & v);

	void OnOpenFile(CString &path);

	bool SaveAs(CString &path);

	bool Save();

	CString FilePathBox();

	CString FilePathBoxSaveAs();

	bool OpenPastFile();

	//FileOwner fileOwner_;
	std::unique_ptr<FileOwner> p_fileOwner_;
	//FILE * pFile;

public:
	//friend class HexHeader;

	afx_msg void OnBnClickedOk();
	CEdit editHexShow_;
	afx_msg void OnEnChangeEditHexShow();
	CListCtrl listCtrlHexShow_;
	afx_msg void OnDropFiles(HDROP hDropInfo);

	CString dropFilePath_;
	CEdit editCtrlMsg_;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnOpenFileBnClicked();

	afx_msg void OnBtnSave();
	afx_msg void On_BtnSaveAs();

	virtual BOOL  PreTranslateMessage(MSG* pMsg);
	afx_msg void ON_CloseFile();
	afx_msg void On_DoScript();
};
