
// gzipToolsDlg.h : 头文件
//

#pragma once


// CgzipToolsDlg 对话框
class CgzipToolsDlg : public CDialog
{
// 构造
public:
	CgzipToolsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GZIPTOOLS_DIALOG };

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
private:
        // 源文件路径
        CString m_strSrcPath;
        // 目标文件路径
        CString m_strDstPath;
        CStatusBarCtrl m_StatusBar; // 状态栏
protected:
        virtual void OnCancel();
        virtual void OnOK();
public:
        virtual BOOL PreTranslateMessage(MSG* pMsg);
        afx_msg void OnBnClickedSrcbrow();
        afx_msg void OnBnClickedDstbrow();
        afx_msg void OnBnClickedCompress();
        afx_msg void OnBnClickedUncompress();
        int gzipStream(bool bMode);
};
