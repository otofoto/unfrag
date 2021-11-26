#if !defined(AFX_UNFRAGPROPERTYSHEET_H__77C113A3_211F_11D1_B2D9_444553540000__INCLUDED_)
#define AFX_UNFRAGPROPERTYSHEET_H__77C113A3_211F_11D1_B2D9_444553540000__INCLUDED_

#include "AboutPage.h"	// Added by ClassView
#include "HelpPage.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// UnfragPropertySheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUnfragPropertySheet

class CUnfragPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CUnfragPropertySheet)

// Construction
public:
	CUnfragPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CUnfragPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnfragPropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	CHelpPage m_helpPage;
	virtual ~CUnfragPropertySheet();

	// Generated message map functions
protected:
	CAboutPage m_aboutPage;
	//{{AFX_MSG(CUnfragPropertySheet)
	//}}AFX_MSG
	afx_msg LONG OnInitDialog (UINT wParam, LONG lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNFRAGPROPERTYSHEET_H__77C113A3_211F_11D1_B2D9_444553540000__INCLUDED_)
