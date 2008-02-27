// DowLoadServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CDowLoadServerDlg �Ի���
class CDowLoadServerDlg : public CDialog
{
// ����
public:
	CDowLoadServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DOWLOADSERVER_DIALOG };

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
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedStart();
	CString m_Directory_;
	afx_msg void OnBnClickedDirectory();
	CButton m_StartButton_;
	DWORD m_serverip_;
	int m_ServerPort_;
};
