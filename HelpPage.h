#if !defined(AFX_HELPPAGE_H__77C113A2_211F_11D1_B2D9_444553540000__INCLUDED_)
#define AFX_HELPPAGE_H__77C113A2_211F_11D1_B2D9_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HelpPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHelpPage dialog

class CHelpPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CHelpPage)

// Construction
public:
	CHelpPage();
	~CHelpPage();

// Dialog Data
	//{{AFX_DATA(CHelpPage)
	enum { IDD = IDD_HELP_PAGE };
	CSpecialEdit	m_wndEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHelpPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHelpPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPPAGE_H__77C113A2_211F_11D1_B2D9_444553540000__INCLUDED_)
