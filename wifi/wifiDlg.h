// wifiDlg.h : ͷ�ļ�
//

#pragma once


// CwifiDlg �Ի���
class CwifiDlg : public CDialog
{
// ����
public:
	CwifiDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WIFI_DIALOG };

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
	CString m_name;
	CString m_passwd;
	afx_msg void OnBnClickedButton1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg UINT OnNotifyFormat(CWnd *pWnd, UINT nCommand);
	afx_msg LRESULT OnNotifyIcon(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnChangeEdit3();
	CString m_help;
	afx_msg void OnEnSetfocusEdit5();
	afx_msg void OnBnClickedCommand1();
	afx_msg void OnBnClickedButton2();
};
