
// HeaxHeaderDlg.h : ͷ�ļ�
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

// CHeaxHeaderDlg �Ի���
class CHeaxHeaderDlg : public CDialogEx
{
// ����
public:
	CHeaxHeaderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HEAXHEADER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
