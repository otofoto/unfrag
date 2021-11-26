// ProgressDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Unfrag.h"
#include "ProgressDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDialog dialog


CProgressDialog::CProgressDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bCancelRequested = FALSE;
}


void CProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDialog)
	DDX_Control(pDX, IDC_PROGRESS, m_wndProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDialog, CDialog)
	//{{AFX_MSG_MAP(CProgressDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDialog message handlers

void CProgressDialog::OnCancel() 
{
	m_bCancelRequested = TRUE;
}

void CProgressDialog::OnOK() 
{
	// Eat the message so EndDialog won't be called.
}

BOOL CProgressDialog::CancelRequested()
{
	//
	// Pump waiting messages through the message queue.
	//
	MSG msg;
	while (::PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
		AfxGetApp ()->PumpMessage ();

	//
	// Simulate the framework's idle processing mechanism.
	//
	LONG lIdle = 0;
	while (AfxGetApp ()->OnIdle (lIdle++));

	//
	// Return the value of the m_bCancelRequested flag.
	//
	return m_bCancelRequested;
}
