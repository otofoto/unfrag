// Unfrag.h : main header file for the UNFRAG application
//

#if !defined(AFX_UNFRAG_H__17AA75E5_0E43_11D1_B2D9_444553540000__INCLUDED_)
#define AFX_UNFRAG_H__17AA75E5_0E43_11D1_B2D9_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUnfragApp:
// See Unfrag.cpp for the implementation of this class
//

class CUnfragApp : public CWinApp
{
public:
	BOOL m_bAutoClose;
	BOOL m_bAutoRun;
	CUnfragApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnfragApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUnfragApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNFRAG_H__17AA75E5_0E43_11D1_B2D9_444553540000__INCLUDED_)
