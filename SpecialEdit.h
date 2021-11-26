#if !defined(AFX_SPECIALEDIT_H__C243B0A1_2498_11D1_B2D9_444553540000__INCLUDED_)
#define AFX_SPECIALEDIT_H__C243B0A1_2498_11D1_B2D9_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SpecialEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpecialEdit window

class CSpecialEdit : public CEdit
{
// Construction
public:
	CSpecialEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpecialEdit)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSpecialEdit();

	// Generated message map functions
protected:
	CBrush m_brush;
	//{{AFX_MSG(CSpecialEdit)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	HBRUSH CtlColor (CDC* pDC, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECIALEDIT_H__C243B0A1_2498_11D1_B2D9_444553540000__INCLUDED_)
