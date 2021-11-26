#if !defined(AFX_ABOUTPAGE_H__77C113A1_211F_11D1_B2D9_444553540000__INCLUDED_)
#define AFX_ABOUTPAGE_H__77C113A1_211F_11D1_B2D9_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AboutPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAboutPage dialog

class CAboutPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CAboutPage)

// Construction
public:
	CAboutPage();
	~CAboutPage();

// Dialog Data
	//{{AFX_DATA(CAboutPage)
	enum { IDD = IDD_ABOUT_PAGE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAboutPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_font;
	// Generated message map functions
	//{{AFX_MSG(CAboutPage)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTPAGE_H__77C113A1_211F_11D1_B2D9_444553540000__INCLUDED_)
