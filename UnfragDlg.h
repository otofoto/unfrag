// UnfragDlg.h : header file
//
//{{AFX_INCLUDES()
//}}AFX_INCLUDES

#if !defined(AFX_UNFRAGDLG_H__17AA75E7_0E43_11D1_B2D9_444553540000__INCLUDED_)
#define AFX_UNFRAGDLG_H__17AA75E7_0E43_11D1_B2D9_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

int CALLBACK BrowseCallbackProc (HWND hwnd, UINT uMsg, LPARAM lParam,
	LPARAM lpData);

/////////////////////////////////////////////////////////////////////////////
// CUnfragDlg dialog

class CUnfragDlg : public CDialog
{
// Construction
public:
	CUnfragDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUnfragDlg)
	enum { IDD = IDD_UNFRAG_DIALOG };
	BOOL	m_bDoSubfolders;
	CString	m_strFolder;
	CString	m_strFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnfragDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	UINT m_nFiles;
	UINT m_nCompoundFiles;
	UINT m_nBytesSaved;
	UINT m_nTotalFiles;
	UINT m_nFileCount;
	int m_cySplash;
	int m_cxSplash;
	CPalette m_palSplash;
	CBitmap m_bmSplash;
	CRect m_rcImage;
	void CountFiles (BOOL bDoSubfolders, LPCTSTR pszFile);
	void ProcessDirectory(BOOL bDoSubfolders, LPCTSTR pszFile);
	CString FormatString(UINT nVal);
	int UnfragFile (LPCTSTR pszFile);
	int GetFileSize (LPCTSTR pszFile);
	CProgressDialog* m_pDialog;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUnfragDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnUnfrag();
	afx_msg void OnBrowse();
	afx_msg void OnChangeFolder();
	afx_msg void OnFolderSelChange();
	//}}AFX_MSG
	afx_msg LONG OnCancelOperation (UINT wParam, LONG lParam);
	afx_msg LONG OnThreadFinished (UINT wParam, LONG lParam);
	afx_msg void OnHelp();
	afx_msg BOOL OnQueryNewPalette ();
	afx_msg void OnPaletteChanged (CWnd* pFocusWnd);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNFRAGDLG_H__17AA75E7_0E43_11D1_B2D9_444553540000__INCLUDED_)
