
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
        // 初始化状态栏
        m_StatusBar.Create(WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, 101) ;
        int arWidth[2] = {260,-1} ;
        m_StatusBar.SetParts(2, arWidth) ;
        wchar_t szKernelName[MAX_PATH] = {0} ;

        m_StatusBar.SetText(TEXT("Copyright(c)2015 EvilKnight 所有"),0,0) ;

        GetDlgItem(BTN_COMPRESS)->EnableWindow(FALSE) ;
        GetDlgItem(BTN_UNCOMPRESS)->EnableWindow(FALSE) ;

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
                GetDlgItem(BTN_COMPRESS)->EnableWindow(TRUE) ;
                GetDlgItem(BTN_UNCOMPRESS)->EnableWindow(TRUE) ;
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
        gzipStream(false) ;
}

void CgzipToolsDlg::OnBnClickedUncompress()
{
        // TODO: 在此添加控件通知处理程序代码
        gzipStream(true) ;
}

/*******************************************************************************
*
*   函 数 名 : gzipStream
*  功能描述 : gzip压缩与解压功能,数据流形式
*  参数列表 : bMode       --  工作模式
*  说      明 :  bMode为false时为压缩工作模式，bMode为true为解压工作模式
*  返回结果 :  如果操作成功，返回0, 失败返回-1(解压或压缩结果为返回值)
*
*******************************************************************************/
int CgzipToolsDlg::gzipStream(bool bMode)
{
        UpdateData(TRUE) ;

        HANDLE hSrcFile = INVALID_HANDLE_VALUE ;
        HANDLE hDstFile = INVALID_HANDLE_VALUE ;
        DWORD dwError(0) ;
        DWORD dwFileSize(0) ;
        DWORD dwNeedBufSize(0) ;
        PBYTE pSrcBuffer(NULL), pDstBuffer(NULL) ;
        DWORD dwNumberOfBytesRead(0) ;
        DWORD dwNumberOfBytesWritten(0);
        int nResult(-1) ;
        BOOL bWriteFileRresult(false) ;

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

                // 如果没有指定目标路径，自己生成一个
                if (m_strDstPath.GetLength() == 0)
                {
                        m_strDstPath = m_strSrcPath ;
                        m_strDstPath += TEXT(".out") ;
                        UpdateData(FALSE) ;
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

                // bMode为true的话为解压模式，给大一点的空间
                // 其实压缩的话，内存的需求会更少的
                dwNeedBufSize = dwFileSize * (bMode?8:2) ;
                pDstBuffer = new Byte[dwNeedBufSize] ;

                if (bMode)
                {
                        nResult = httpgzdecompress(pSrcBuffer,
                                                                        dwFileSize,
                                                                        pDstBuffer,
                                                                        &dwNeedBufSize) ;
                }
                else
                {
                        nResult = gzcompress(pSrcBuffer,
                                                                dwFileSize,
                                                                pDstBuffer,
                                                                &dwNeedBufSize) ;
                }
                
                if (-1 != nResult)
                {
                        bWriteFileRresult = WriteFile(hDstFile,
                                                                                pDstBuffer,
                                                                                dwNeedBufSize,
                                                                                &dwNumberOfBytesWritten, 
                                                                                NULL) ;
                }
                else
                {
                        m_StatusBar.SetText(bMode?TEXT("解压数据出错"):TEXT("压缩数据出错"),1,0) ;
                        __leave ;
                }

                // 写入文件成功
                if (bWriteFileRresult && dwNumberOfBytesWritten == dwNeedBufSize)
                {
                        m_StatusBar.SetText(bMode?TEXT("解压数据成功并成功写入文件")
                                                                         :TEXT("压缩数据成功并成功写入文件"),1,0) ;
                }
                else
                {
                        m_StatusBar.SetText(bMode?TEXT("解压数据成功但是写入文件失败")
                                                                         :TEXT("压缩数据成功但是写入文件失败"),1,0) ;
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

        return nResult ;
}
