
// gzipToolsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "gzipTools.h"
#include "gzipToolsDlg.h"
#include "ErrorMessage.h"

#ifdef __cplusplus
extern "C"
{
#include "zlib/gzip.h"
}
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CgzipToolsDlg 对话框




CgzipToolsDlg::CgzipToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CgzipToolsDlg::IDD, pParent)
        , m_strSrcPath(_T(""))
        , m_strDstPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgzipToolsDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        DDX_Text(pDX, EDT_SRCPATH, m_strSrcPath);
        DDV_MaxChars(pDX, m_strSrcPath, 260);
        DDX_Text(pDX, EDT_DSTPATH, m_strDstPath);
	DDV_MaxChars(pDX, m_strDstPath, 260);
}

BEGIN_MESSAGE_MAP(CgzipToolsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
        ON_BN_CLICKED(BTN_SRCBROW, &CgzipToolsDlg::OnBnClickedSrcbrow)
        ON_BN_CLICKED(BTN_DSTBROW, &CgzipToolsDlg::OnBnClickedDstbrow)
        ON_BN_CLICKED(BTN_COMPRESS, &CgzipToolsDlg::OnBnClickedCompress)
        ON_BN_CLICKED(BTN_UNCOMPRESS, &CgzipToolsDlg::OnBnClickedUncompress)
END_MESSAGE_MAP()


// CgzipToolsDlg 消息处理程序

BOOL CgzipToolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CgzipToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CgzipToolsDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CgzipToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CgzipToolsDlg::OnCancel()
{
        // TODO: 在此添加专用代码和/或调用基类

        CDialog::OnCancel();
}

void CgzipToolsDlg::OnOK()
{
        // TODO: 在此添加专用代码和/或调用基类

        CDialog::OnOK();
}

BOOL CgzipToolsDlg::PreTranslateMessage(MSG* pMsg)
{
        // TODO: 在此添加专用代码和/或调用基类
        if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE)
                return TRUE;
        if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
                return TRUE;

        return CDialog::PreTranslateMessage(pMsg);
}

void CgzipToolsDlg::OnBnClickedSrcbrow()
{
        // TODO: 在此添加控件通知处理程序代码
        CFileDialog dlg(TRUE,
                NULL,
                NULL,
                OFN_HIDEREADONLY,
                TEXT("All Files (*.*)|*.*||"),
                AfxGetMainWnd());

        if (dlg.DoModal()==IDOK)
        {
                m_strSrcPath = dlg.GetPathName();
                UpdateData(FALSE) ;
        }
}

void CgzipToolsDlg::OnBnClickedDstbrow()
{
        // TODO: 在此添加控件通知处理程序代码
        CFileDialog dlg(TRUE,
                NULL,
                NULL,
                OFN_HIDEREADONLY,
                TEXT("All Files (*.*)|*.*||"),
                AfxGetMainWnd());

        if (dlg.DoModal()==IDOK)
        {
                m_strDstPath = dlg.GetPathName();
                UpdateData(FALSE) ;
        }

}

void CgzipToolsDlg::OnBnClickedCompress()
{
        // TODO: 在此添加控件通知处理程序代码
        UpdateData(TRUE) ;
}

void CgzipToolsDlg::OnBnClickedUncompress()
{
        // TODO: 在此添加控件通知处理程序代码
        UpdateData(TRUE) ;
        
        HANDLE hSrcFile = INVALID_HANDLE_VALUE ;
        HANDLE hDstFile = INVALID_HANDLE_VALUE ;
        DWORD dwError(0) ;
        DWORD dwFileSize(0) ;
        DWORD dwNeedBufSize(0) ;
        PBYTE pSrcBuffer(NULL), pDstBuffer(NULL) ;
        DWORD dwNumberOfBytesRead(0) ;
        DWORD dwNumberOfBytesWritten(0);

        __try
        {
                hSrcFile = CreateFile(m_strSrcPath.GetBuffer(0),
                                                        GENERIC_READ,
                                                        FILE_SHARE_READ,
                                                        NULL,
                                                        OPEN_EXISTING,
                                                        FILE_ATTRIBUTE_NORMAL,
                                                        NULL) ;
                if (INVALID_HANDLE_VALUE == hSrcFile)
                {
                        dwError = GetLastError() ;
                        OutputDebugString(TEXT("create srcfile failed!\r\n")) ;
                        __leave ;
                }

                hDstFile = CreateFile(m_strDstPath.GetBuffer(0),
                                                        GENERIC_WRITE,
                                                        FILE_SHARE_WRITE,
                                                        NULL,
                                                        OPEN_ALWAYS,
                                                        FILE_ATTRIBUTE_NORMAL,
                                                        NULL) ;
                if (INVALID_HANDLE_VALUE == hDstFile)
                {
                        dwError = GetLastError() ;
                        OutputDebugString(TEXT("create desfile failed!\r\n")) ;
                        __leave ;
                }

                dwFileSize = GetFileSize(hSrcFile, NULL) ;

                pSrcBuffer = new Byte[dwFileSize] ;

                if (NULL == pSrcBuffer)
                {
                        OutputDebugString(TEXT("malloc memory failed!\r\n")) ;
                        __leave ;
                }

                if ( ! ReadFile(hSrcFile, pSrcBuffer, dwFileSize,&dwNumberOfBytesRead , NULL)
                        ||  dwNumberOfBytesRead == 0)
                {
                        OutputDebugString(TEXT("ReadFile failed!\r\n")) ;
                        __leave ;
                }

                dwNeedBufSize = dwFileSize * 8 ;
                pDstBuffer = new Byte[dwNeedBufSize] ;

                if(-1 != httpgzdecompress(pSrcBuffer, dwFileSize, pDstBuffer, &dwNeedBufSize))
                {
                        if( WriteFile(hDstFile, pDstBuffer, dwNeedBufSize, &dwNumberOfBytesWritten, NULL)
                                && dwNumberOfBytesWritten == dwNeedBufSize)
                        {
                                MessageBox(TEXT("解压成功并成功写入文件!"), TEXT("Tips"),MB_OK) ;
                        }
                        else
                        {
                                MessageBox(TEXT("解压成功但是写入文件失败!"), TEXT("Tips"),  MB_OK) ;
                        }
                }
        }

        __finally
        {
                if (INVALID_HANDLE_VALUE != hSrcFile)
                {
                        CloseHandle(hSrcFile) ;
                        hSrcFile = INVALID_HANDLE_VALUE ;
                }

                if (INVALID_HANDLE_VALUE != hDstFile)
                {
                        CloseHandle(hDstFile) ;
                        hDstFile = INVALID_HANDLE_VALUE ;
                }

                if (NULL != pSrcBuffer)
                {
                        delete [] pSrcBuffer ;
                        pSrcBuffer = NULL ;
                }

                if (NULL != pDstBuffer)
                {
                        delete [] pDstBuffer ;
                        pDstBuffer = NULL ;
                }
        }

}
