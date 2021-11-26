#if !defined(AFX_PROGRESSDIALOG_H__F89964C1_109C_11D1_B2D9_444553540000__INCLUDED_)
#define AFX_PROGRESSDIALOG_H__F89964C1_109C_11D1_B2D9_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// ProgressDialog.h : header file
//

#define WM_USER_CANCEL			WM_USER+0x100

/////////////////////////////////////////////////////////////////////////////
// CProgressDialog dialog

class CProgressDialog : public CDialog
{
// Construction
public:
	BOOL CancelRequested ();
	CProgressDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgressDialog)
	enum { IDD = IDD_PROGRESS_DIALOG };
	CProgressCtrl	m_wndProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bCancelRequested;

	// Generated message map functions
	//{{AFX_MSG(CProgressDialog)
	virtual void OnCancel();
	//}}AFX_MSG
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDIALOG_H__F89964C1_109C_11D1_B2D9_444553540000__INCLUDED_)
