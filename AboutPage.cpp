// AboutPage.cpp : implementation file
//

#include "stdafx.h"
#include "Unfrag.h"
#include "AboutPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutPage property page

IMPLEMENT_DYNCREATE(CAboutPage, CPropertyPage)

CAboutPage::CAboutPage() : CPropertyPage(CAboutPage::IDD)
{
	//{{AFX_DATA_INIT(CAboutPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_psp.dwFlags &= ~PSP_HASHELP;
}

CAboutPage::~CAboutPage()
{
}

void CAboutPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutPage, CPropertyPage)
	//{{AFX_MSG_MAP(CAboutPage)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutPage message handlers

BOOL CAboutPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	LOGFONT lf;
	::ZeroMemory (&lf, sizeof (lf));

	lf.lfHeight = 200;
	lf.lfWeight = FW_BOLD;
	lf.lfItalic = TRUE;
	::lstrcpy (lf.lfFaceName, _T ("Arial"));

	m_font.CreatePointFontIndirect (&lf);
	GetDlgItem (IDC_TITLE)->SetFont (&m_font, FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CAboutPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hBrush = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	if (GetDlgItem (IDC_TITLE)->m_hWnd == pWnd->m_hWnd)
		pDC->SetTextColor (RGB (255, 0, 0));

	return hBrush;
}
