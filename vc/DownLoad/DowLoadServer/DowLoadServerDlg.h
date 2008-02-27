// DowLoadServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CDowLoadServerDlg 对话框
class CDowLoadServerDlg : public CDialog
{
// 构造
public:
	CDowLoadServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DOWLOADSERVER_DIALOG };

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
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedStart();
	CString m_Directory_;
	afx_msg void OnBnClickedDirectory();
	CButton m_StartButton_;
	DWORD m_serverip_;
	int m_ServerPort_;
};
