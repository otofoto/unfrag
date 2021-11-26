// SpecialEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Unfrag.h"
#include "SpecialEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpecialEdit

CSpecialEdit::CSpecialEdit()
{
	m_brush.CreateSolidBrush (::GetSysColor (COLOR_WINDOW));
}

CSpecialEdit::~CSpecialEdit()
{
}


BEGIN_MESSAGE_MAP(CSpecialEdit, CEdit)
	//{{AFX_MSG_MAP(CSpecialEdit)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR_REFLECT ()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpecialEdit message handlers

void CSpecialEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
	SetSel (-1, 0);
	HideCaret ();
}

BOOL CSpecialEdit::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= ES_READONLY;	// Make sure this bit is set...
	cs.style &= ~ES_NOHIDESEL;	// and this one is clear
	return CEdit::PreCreateWindow(cs);
}

void CSpecialEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	ShowCaret ();
}

HBRUSH CSpecialEdit::CtlColor (CDC* pDC, UINT nCtlColor) 
{
	return (HBRUSH) m_brush;
}
