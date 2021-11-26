// UnfragPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "Unfrag.h"
#include "SpecialEdit.h"
#include "UnfragPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnfragPropertySheet

IMPLEMENT_DYNAMIC(CUnfragPropertySheet, CPropertySheet)

CUnfragPropertySheet::CUnfragPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags &= ~PSH_HASHELP;
	AddPage (&m_aboutPage);
	AddPage (&m_helpPage);
}

CUnfragPropertySheet::CUnfragPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_psh.dwFlags &= ~PSH_HASHELP;
	AddPage (&m_aboutPage);
	AddPage (&m_helpPage);
}

CUnfragPropertySheet::~CUnfragPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CUnfragPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CUnfragPropertySheet)
	//}}AFX_MSG_MAP
	ON_MESSAGE (WM_INITDIALOG, OnInitDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnfragPropertySheet message handlers

LONG CUnfragPropertySheet::OnInitDialog (UINT wParam, LONG lParam)
{
	LRESULT lResult = DefWindowProc (WM_INITDIALOG, wParam, lParam);

	GetDlgItem (IDCANCEL)->DestroyWindow ();	
	GetDlgItem (ID_APPLY_NOW)->DestroyWindow ();	

	CRect rcSheet;
	GetClientRect (&rcSheet);

	CRect rcButton;
	CWnd* pButton = GetDlgItem (IDOK);
	pButton->GetWindowRect (rcButton);
	ScreenToClient (&rcButton);

	int x = (rcSheet.Width () - rcButton.Width ()) / 2;
	int y = rcButton.top;
	int cx = rcButton.Width ();
	int cy = rcButton.Height ();

	pButton->SetWindowPos (NULL, x, y, cx, cy, SWP_NOZORDER);
	return lResult;
}
