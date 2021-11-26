// Unfrag.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <string.h>
#include "Unfrag.h"
#include "ProgressDialog.h"
#include "UnfragDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnfragApp

BEGIN_MESSAGE_MAP(CUnfragApp, CWinApp)
	//{{AFX_MSG_MAP(CUnfragApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnfragApp construction

CUnfragApp::CUnfragApp()
{
	m_bAutoRun = FALSE;
	m_bAutoClose = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUnfragApp object

CUnfragApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUnfragApp initialization

BOOL CUnfragApp::InitInstance()
{
	//
	// Initialize the OLE libraries.
	//
	if (!AfxOleInit ()) {
		AfxMessageBox (_T ("UNFRAG was unable to initialize your " \
			"system's OLE libraries.\nWindows might need to be reinstalled " \
			"on this PC."), MB_ICONSTOP | MB_OK);
		return FALSE;
	}

	//
	// Parse the command line.
	//
	BOOL bDone = FALSE;
	BOOL bHavePathName = FALSE;
	BOOL bDoSubfolders = FALSE;
	BOOL bInQuotes = FALSE;
	TCHAR* pszEntry = m_lpCmdLine;
	TCHAR szPath[MAX_PATH];
	szPath[0] = 0;

	while (!bDone) {
		while ((*pszEntry == 0x20) || (*pszEntry == 0x09))
			pszEntry++;
		if (*pszEntry == 0)
			bDone = TRUE;
		else {
			if ((*pszEntry == _T ('-')) || (*pszEntry == _T ('/'))) { // Switch character?
				pszEntry++;
				if ((*pszEntry == _T ('S')) || (*pszEntry == _T ('s'))) {
					bDoSubfolders = TRUE;
					pszEntry++;
				}
				else if ((*pszEntry == _T ('R')) || (*pszEntry == _T ('r'))) {
					m_bAutoRun = TRUE;
					pszEntry++;
				}
				else if ((*pszEntry == _T ('C')) || (*pszEntry == _T ('c'))) {
					m_bAutoClose = TRUE;
					pszEntry++;
				}
				else {
					CString string;
					string.Format (_T ("Invalid command line switch: %c%c"),
						*(pszEntry - 1), *pszEntry);
					AfxMessageBox (string, MB_ICONSTOP | MB_OK);
					return FALSE;
				}
			}
			else if (*pszEntry == _T ('\"')) { // Quotation mark?
				if (bInQuotes)
					bInQuotes = FALSE;
				else
					bInQuotes = TRUE;
				pszEntry++;
			}
			else { // Must be a path name
				if (!bHavePathName) { // Copy the path name
					int i = 0;
					if (bInQuotes) { // Ignore separators
						while ((*pszEntry != _T ('\"')) && (*pszEntry != 0))
							szPath[i++] = *pszEntry++;
					}
					else { // Don't ignore separators
						while ((*pszEntry != 0x20) && (*pszEntry != 0x09) &&
							(*pszEntry != 0))
							szPath[i++] = *pszEntry++;
					}
					szPath[i] = 0;
					bHavePathName = TRUE;
				}
				else { // Error: already have a path name
					AfxMessageBox (_T ("Only one path name may be entered " \
						"on the command line"), MB_ICONSTOP | MB_OK);
					return FALSE;
				}
			}
		}
	}

	//
	// Make sure the command line included a path name if it also
	// included a /R switch.
	//
	if (m_bAutoRun && !bHavePathName) {
		AfxMessageBox (_T ("You must supply a path name in order " \
			"to use the /R switch"), MB_ICONSTOP | MB_OK);
		return FALSE;
	}

	//
	// If a path name was entered on the command line, separate the path
	// from the file name specification (if present).
	//
	TCHAR szFolder[MAX_PATH];
	TCHAR szFile[MAX_PATH];
	szFolder[0] = 0;
	szFile[0] = 0;

	if (::lstrlen (szPath) != 0) {
		TCHAR szHome[MAX_PATH];
	    ::GetCurrentDirectory (sizeof (szHome) / sizeof (TCHAR), szHome);
		BOOL bResult = ::SetCurrentDirectory (szPath);
		::SetCurrentDirectory (szHome);

		if (bResult) { // It's a folder name
			::lstrcpy (szFolder, szPath);
			::lstrcpy (szFile, _T ("*.*"));
		}
		else { // Assume szPath includes a file specification
			LPTSTR pszFileName;
			TCHAR szTemp[MAX_PATH];
			::GetFullPathName (szPath, sizeof (szTemp) / sizeof (TCHAR),
				szTemp, &pszFileName);
			*(pszFileName - 1) = 0; // Split the path name
			::lstrcpy (szFile, pszFileName);
			::lstrcpy (szFolder, szTemp);
			int nLen = ::lstrlen (szFolder);
			if (szFolder[nLen - 1] == _T (':'))
				::lstrcat (szFolder, _T ("\\"));
		}
	}

	//
	// Display the dialog that serves as the application's main window.
	//
	CUnfragDlg dlg;
	m_pMainWnd = &dlg;

	dlg.m_strFile = szFile;
	dlg.m_strFolder = szFolder;
	dlg.m_bDoSubfolders = bDoSubfolders;

	dlg.DoModal();
	return FALSE;
}
