// UnfragDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Unfrag.h"
#include "SpecialEdit.h"
#include "ProgressDialog.h"
#include "UnfragDlg.h"
#include "AboutPage.h"
#include "HelpPage.h"
#include "UnfragPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnfragDlg dialog

CUnfragDlg::CUnfragDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnfragDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUnfragDlg)
	m_bDoSubfolders = FALSE;
	m_strFolder = _T("");
	m_strFile = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pDialog = NULL;
}

void CUnfragDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnfragDlg)
	DDX_Check(pDX, IDC_SUBFOLDERS, m_bDoSubfolders);
	DDX_CBString(pDX, IDC_FOLDER, m_strFolder);
	DDX_Text(pDX, IDC_FILE, m_strFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUnfragDlg, CDialog)
	//{{AFX_MSG_MAP(CUnfragDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_UNFRAG, OnUnfrag)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_CBN_EDITCHANGE(IDC_FOLDER, OnChangeFolder)
	ON_CBN_SELCHANGE(IDC_FOLDER, OnFolderSelChange)
	//}}AFX_MSG_MAP
	ON_COMMAND (ID_HELP, OnHelp)
	ON_WM_QUERYNEWPALETTE ()
	ON_WM_PALETTECHANGED ()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnfragDlg message handlers

BOOL CUnfragDlg::OnInitDialog()
{
	// Palette colors for splash image
	static const BYTE byVals[16][3] = {
		  0,   0,   0,
		  0,   8,  41,
		 16,  41,  49,
		  0,  16,  90,
		  0,  57, 123,
		 16,  41, 115,
		  0, 107, 165,
		 33,  82, 140,
		 66,  90, 140,
		 49, 132, 189,
		 74, 140, 189,
		107, 156, 198,
		132, 165, 206,
		173, 206, 231,
		198, 231, 247,
		255, 255, 255
	};

	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//
	// Populate the combo box with a list of local drives.
	//
    DWORD dwDriveList = ::GetLogicalDrives ();

	int i = 0;
    while (dwDriveList) {
        if (dwDriveList & 1) {
			CString string = "A:\\";
			string.SetAt (0, string[0] + i);
			UINT nType = ::GetDriveType ((LPCTSTR) string);
			if ((nType == DRIVE_REMOVABLE) || (nType == DRIVE_FIXED)) {
				GetDlgItem (IDC_FOLDER)->SendMessage (CB_ADDSTRING, 0,
					(LPARAM) (LPCTSTR) string);
			}
		}
        dwDriveList >>= 1;
        i++;
    }

	//
	// Destroy the dummy static control that serves as a placeholder for
	// the splash image and store its coordinates in m_rcImage.
	//
	CWnd* pWnd = GetDlgItem (IDC_IMAGE);
	pWnd->GetWindowRect (&m_rcImage);
	ScreenToClient (&m_rcImage);
	pWnd->DestroyWindow ();

	//
	// Load the splash image.
	//
	HANDLE hImage = ::LoadImage (AfxGetInstanceHandle (),
		MAKEINTRESOURCE (IDB_SPLASH), IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION);

	ASSERT (hImage != NULL);
	m_bmSplash.Attach (hImage);

	BITMAP bm;
	m_bmSplash.GetObject (sizeof (bm), &bm);
	m_cxSplash = bm.bmWidth;
	m_cySplash = bm.bmHeight;

	//
	// Create a palette to go with the splash image.
	//
	struct {
	    LOGPALETTE lp;
	    PALETTEENTRY ape[15];   // Number of palette entries minus 1
	} pal;

	LOGPALETTE* plp = (LOGPALETTE*) &pal;
	plp->palVersion = 0x300;
	plp->palNumEntries = 16;    // Number of palette entries

	for (i=0; i<plp->palNumEntries; i++) {
	    plp->palPalEntry[i].peRed = byVals[i][0];
	    plp->palPalEntry[i].peGreen = byVals[i][1];
	    plp->palPalEntry[i].peBlue = byVals[i][2];
	    plp->palPalEntry[i].peFlags = 0;
	}

	m_palSplash.CreatePalette (plp);
	ASSERT ((HPALETTE) m_palSplash != NULL);

	//
	// If the Folder field contains a path name, enable the Unfrag button.
	// If the Unfrag button is enabled, begin unfragging if the application
	// object's m_bAutoRun flag is set.
	//
	CString string;
	GetDlgItemText (IDC_FOLDER, string);

	if (!string.IsEmpty ()) {
		GetDlgItem (IDC_UNFRAG)->EnableWindow (TRUE);
		if (((CUnfragApp*) AfxGetApp ())->m_bAutoRun)
			PostMessage (WM_COMMAND, MAKEWPARAM (IDC_UNFRAG, BN_CLICKED),
				(LPARAM) GetDlgItem (IDC_UNFRAG)->m_hWnd);
	}

	return TRUE;
}

void CUnfragDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUnfragPropertySheet ps ("About Unfrag");
		ps.DoModal ();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUnfragDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		//
		// First let the base class do its thing.
		//
		CDialog::OnPaint ();

		//
		// Now paint the splash image.
		//
		CClientDC dc (this);
		dc.Draw3dRect (m_rcImage, RGB (128, 128, 128), RGB (230, 230, 230));

		CRect rect = m_rcImage;
		rect.DeflateRect (1, 1);

		CDC dcMem;
		dcMem.CreateCompatibleDC (&dc);
		CBitmap* pOldBitmap = dcMem.SelectObject (&m_bmSplash);

		CPalette* pOldPalette = dc.SelectPalette (&m_palSplash, FALSE);
		dc.RealizePalette ();

		dc.StretchBlt (rect.left, rect.top, rect.Width (), rect.Height (),
			&dcMem, 0, 0, m_cxSplash, m_cySplash, SRCCOPY);		

		dc.SelectPalette (pOldPalette, FALSE);
		dcMem.SelectObject (pOldBitmap);
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUnfragDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUnfragDlg::OnHelp() 
{
	CUnfragPropertySheet ps (_T ("About Unfrag"));
	ps.SetActivePage (1);
	ps.DoModal ();
}

void CUnfragDlg::OnUnfrag() 
{
	//
    // Change to the target folder.
	//
	CString string;
	GetDlgItemText (IDC_FOLDER, string);

	if (string.IsEmpty ()) {
		MessageBox (_T ("You must enter a drive or folder name"),
			_T ("Error"), MB_ICONINFORMATION | MB_OK);
		GetDlgItem (IDC_FOLDER)->SetFocus ();
		return;
	}

	TCHAR szHome[MAX_PATH];
    ::GetCurrentDirectory (sizeof (szHome) / sizeof (TCHAR), szHome);

    if (!::SetCurrentDirectory ((LPCTSTR) string)) {
		CString errmsg;
		errmsg.Format (_T ("%s is not a valid path name"), string);
		MessageBox (errmsg, _T ("Error"), MB_ICONSTOP | MB_OK);
        return;
	}

	//
	// Make sure this is not a CD-ROM drive.
	//
	TCHAR szPath[MAX_PATH];
	::GetFullPathName ((LPCTSTR) string, sizeof (szPath) / sizeof (TCHAR),
		szPath, NULL);

	CString drive = szPath;
	drive = drive.Left (3);

	if (::GetDriveType (drive) == DRIVE_CDROM) {	
		MessageBox (_T ("Can't unfrag a read-only drive"), _T ("Error"),
			MB_ICONSTOP | MB_OK);
		GetDlgItem (IDC_FOLDER)->SetFocus ();
		::SetCurrentDirectory (szHome);
		return;
	}

	//
	// Get the file name specification (if any).
	//
	CString strFile;
	GetDlgItemText (IDC_FILE, strFile);

	strFile.TrimLeft ();
	strFile.TrimRight ();

	if (strFile.IsEmpty ())
		strFile = _T ("*.*");

	//
	// Determine whether the directory scan will be recursive.
	//
	BOOL bDoSubfolders = IsDlgButtonChecked (IDC_SUBFOLDERS);

	//
	// Initialize counters.
	//
	m_nFiles = 0;
	m_nCompoundFiles = 0;
	m_nBytesSaved = 0;
	m_nTotalFiles = 0;

	//
	// Display the Unfragging dialog and disable the main window.
	//
	m_pDialog = new CProgressDialog;
	m_pDialog->Create (IDD_PROGRESS_DIALOG);
	EnableWindow (FALSE);

	//
	// Get a file count.
	//
	CountFiles (bDoSubfolders, (LPCTSTR) strFile);	
	m_pDialog->GetDlgItem (IDC_INITTEXT)->DestroyWindow ();

	//
	// Unfrag!
	//
	if (!m_pDialog->CancelRequested ())
	    ProcessDirectory (bDoSubfolders, (LPCTSTR) strFile);

	m_pDialog->m_wndProgress.SetPos (0);

	//
	// If the Cancel button hasn't been clicked and the m_bAutoClose flag
	// isn't set, change the Cancel button into an OK button and pause until
	// the user clicks it.
	//
	if (!m_pDialog->CancelRequested () &&
		!((CUnfragApp*) AfxGetApp ())->m_bAutoClose) {

		m_pDialog->SetDlgItemText (IDCANCEL, _T ("OK"));
		m_pDialog->SetWindowText (_T ("Done!"));
		while (!m_pDialog->CancelRequested ()) {
			MSG msg;
			while (::PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
				AfxGetApp ()->PumpMessage ();
			LONG lIdle = 0;
			while (AfxGetApp ()->OnIdle (lIdle++));
		}
	}

	//
	// Reenable the main window and destroy the dialog.
	//
	EnableWindow (TRUE);
	if (m_pDialog != NULL) {
		m_pDialog->DestroyWindow ();
		delete m_pDialog;
		m_pDialog = NULL;
	}

	//
	// Restore the current directory.
	//
  ::SetCurrentDirectory (szHome);

	//
	// If the m_bAutoClose flag is set, end the application.
	//
	if (((CUnfragApp*) AfxGetApp ())->m_bAutoClose)
		PostMessage (WM_CLOSE, 0, 0);
}

void CUnfragDlg::CountFiles (BOOL bDoSubfolders, LPCTSTR pszFile)
{
	//
	// Count the number of files in the current directory.
	//
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile (pszFile, &fd);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (m_pDialog->CancelRequested ()) {
				::FindClose (hFind);
				return;
			}

            if (!(fd.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY |
				FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM |
				FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_OFFLINE |
				FILE_ATTRIBUTE_TEMPORARY)))

				m_nTotalFiles++;

        } while (::FindNextFile (hFind, &fd));
		::FindClose (hFind);
	}

	//
	// If bDoSubfolders is nonzero, count files in the current directory's
	// descendants, too.
	//
	if (bDoSubfolders) {
	    HANDLE hFind = ::FindFirstFile (_T ("*.*"), &fd);

		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (m_pDialog->CancelRequested ()) {
					::FindClose (hFind);
					return;
				}

	            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
	                CString dir = (LPCTSTR) &fd.cFileName;
	                if ((dir != _T (".")) && (dir != _T (".."))) {
				        ::SetCurrentDirectory ((LPCTSTR) dir);
				        CountFiles (bDoSubfolders, pszFile);
				        ::SetCurrentDirectory (_T (".."));
					}
				}
	        } while (::FindNextFile (hFind, &fd));
			::FindClose (hFind);
		}
	}
}

void CUnfragDlg::ProcessDirectory (BOOL bDoSubfolders, LPCTSTR pszFile)
{
	//
	// Unfrag all compound files in the current directory.
	//
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile (pszFile, &fd);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (m_pDialog->CancelRequested ()) {
				::FindClose (hFind);
				return;
			}

            if (!(fd.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY |
				FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM |
				FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_OFFLINE |
				FILE_ATTRIBUTE_TEMPORARY))) {

				CString count = FormatString (++m_nFiles);
				m_pDialog->SetDlgItemText (IDC_FILES, (LPCTSTR) count);

				WCHAR wszFile[MAX_PATH];
				#ifdef UNICODE
				::lstrcpy (wszFile, &fd.cFileName);
				#else
				::MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED,
					(LPCSTR) &fd.cFileName, -1, wszFile,
					sizeof (wszFile) / sizeof (WCHAR));
				#endif

				if (::StgIsStorageFile (wszFile) == S_OK) {
					count = FormatString (++m_nCompoundFiles);
					m_pDialog->SetDlgItemText (IDC_COMPOUNDFILES,
						(LPCTSTR) count);
					int nBytesSaved = UnfragFile ((LPCTSTR) &fd.cFileName);
					if (nBytesSaved != -1) {
						m_nBytesSaved += nBytesSaved;
						count = FormatString (m_nBytesSaved);
						m_pDialog->SetDlgItemText (IDC_BYTESSAVED,
							(LPCTSTR) count);
					}
				}

				int nPercentDone = m_nFiles * 100 / m_nTotalFiles;
				m_pDialog->m_wndProgress.SetPos (nPercentDone);
			}
        } while (::FindNextFile (hFind, &fd));
		::FindClose (hFind);
	}

	//
	// Now do the same in this directory's subdirectories if the
	// bDoSubfolders flag is nonzero.
	//
	if (bDoSubfolders) {
	    HANDLE hFind = ::FindFirstFile (_T ("*.*"), &fd);

		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (m_pDialog->CancelRequested ()) {
					::FindClose (hFind);
					return;
				}

	            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
	                CString dir = (LPCTSTR) &fd.cFileName;
	                if ((dir != _T (".")) && (dir != _T (".."))) {
				        ::SetCurrentDirectory ((LPCTSTR) dir);
				        ProcessDirectory (bDoSubfolders, pszFile);
				        ::SetCurrentDirectory (_T (".."));
					}
				}
	        } while (::FindNextFile (hFind, &fd));
			::FindClose (hFind);
		}
	}
}

CString CUnfragDlg::FormatString(UINT nVal)
{
	CString string;
	string.Format (_T ("%u"), nVal);

	int nLength = string.GetLength ();
	int nCount = (nLength - 1) / 3;

	if (!nCount)
		return string;

	CString strResult;
	for (int i=1; i<=nCount; i++) {
		string = string.Left (nLength - (i * 3)) + _T (',') +
			string.Right ((i * 3) + (i - 1));
	}
	return string;
}

int CUnfragDlg::UnfragFile (LPCTSTR pszFile)
{
	//
	// Open the input file for reading.
	//
	WCHAR wszInput[MAX_PATH];
	#ifdef UNICODE
	::lstrcpy (wszInput, pszFile);
	#else
	::MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, pszFile, -1, wszInput,
		sizeof (wszInput) / sizeof (WCHAR));
	#endif

	IStorage* pIn;
	HRESULT hr = ::StgOpenStorage (wszInput, NULL, STGM_DIRECT | STGM_READ |
		STGM_SHARE_DENY_WRITE, NULL, 0, &pIn);

	if (FAILED (hr))
		return 0;

	//
	// Create a new compound file for output.
	//
	TCHAR szPath[MAX_PATH];
	if (!::GetTempPath (sizeof (szPath) / sizeof (TCHAR), szPath)) {
		pIn->Release ();
		return 0;
	}

	TCHAR szTemp[MAX_PATH];
	if (!::GetTempFileName (szPath, _T ("TMP"), 0, szTemp)) {
		pIn->Release ();
		return 0;
	}

	WCHAR wszOutput[MAX_PATH];
	#ifdef UNICODE
	::lstrcpy (wszOutput, szTemp);
	#else
	::MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, szTemp, -1, wszOutput,
		sizeof (wszOutput) / sizeof (WCHAR));
	#endif

	IStorage* pOut;
	hr = ::StgCreateDocfile (wszOutput, STGM_DIRECT | STGM_WRITE |
		STGM_SHARE_EXCLUSIVE | STGM_CREATE, 0, &pOut);

	if (FAILED (hr)) {
		pIn->Release ();
		return 0;
	}

	//
	// Copy the contents of the input file to the output file.
	//
	hr = pIn->CopyTo (0, NULL, NULL, pOut);
	pOut->Release ();
	pIn->Release ();

	if (FAILED (hr)) {
		::DeleteFile (szTemp);
		return 0;
	}

	//
	// Compute the number of bytes saved and replace the original file
	// with the new, unfragmented copy if the unfragmented file is smaller.
	//
	int nBytesSaved = GetFileSize (pszFile) - GetFileSize (szTemp);
	if (nBytesSaved > 0) {
		::DeleteFile (pszFile);
		::CopyFile (szTemp, pszFile, FALSE);
	}

	::DeleteFile (szTemp);
	return nBytesSaved;
}

int CUnfragDlg::GetFileSize (LPCTSTR pszFile)
{
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile (pszFile, &fd);

	if (hFind == INVALID_HANDLE_VALUE)
		return 0;

	int nSize = (int) fd.nFileSizeLow;
	::FindClose (hFind);
	return nSize;
}

void CUnfragDlg::OnBrowse() 
{
	//
	// Display the Browse dialog.
	//
	BROWSEINFO bi;
	::ZeroMemory (&bi, sizeof (bi));

	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = _T ("Select a Folder");
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = BrowseCallbackProc;

	LPITEMIDLIST pidl = ::SHBrowseForFolder (&bi);

	//
	// Extract the results.
	//
	if (pidl != NULL) {
		TCHAR szPath[MAX_PATH];
		::SHGetPathFromIDList (pidl, szPath);
		SetDlgItemText (IDC_FOLDER, szPath);
		GetDlgItem (IDC_UNFRAG)->EnableWindow (TRUE);
	}

	//
	// Free the pidl returned by SHBrowseForFolder.
	//
	LPMALLOC pMalloc;
	if (SUCCEEDED (::SHGetMalloc (&pMalloc))) {
		pMalloc->Free (pidl);
		pMalloc->Release ();
	}
}

void CUnfragDlg::OnChangeFolder() 
{
	CString string;
	GetDlgItemText (IDC_FOLDER, string);
	GetDlgItem (IDC_UNFRAG)->EnableWindow (string.IsEmpty () ? FALSE : TRUE);
}

void CUnfragDlg::OnFolderSelChange() 
{
	GetDlgItem (IDC_UNFRAG)->EnableWindow (TRUE);
}

BOOL CUnfragDlg::OnQueryNewPalette ()
{
	CClientDC dc (this);
	CPalette* pOldPalette = dc.SelectPalette (&m_palSplash, FALSE);

	UINT nCount;
	if (nCount = dc.RealizePalette ())
		InvalidateRect (m_rcImage);

	dc.SelectPalette (pOldPalette, FALSE);
	return nCount;
}

void CUnfragDlg::OnPaletteChanged (CWnd* pFocusWnd)
{
	if (pFocusWnd != this) {
		CClientDC dc (this);
		CPalette* pOldPalette = dc.SelectPalette (&m_palSplash, FALSE);

		if (dc.RealizePalette ())
			InvalidateRect (m_rcImage);

		dc.SelectPalette (pOldPalette, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// Global functions

int CALLBACK BrowseCallbackProc (HWND hwnd, UINT uMsg, LPARAM lParam,
	LPARAM lpData)
{
	//
	// When the selection changes in the Browse for Folder dialog, enable
	// the OK button if the selected item is a file system object that's not
	// a CD-ROM drive.
	//
	if (uMsg == BFFM_SELCHANGED) {
		TCHAR szPath[MAX_PATH];
		::SHGetPathFromIDList ((LPITEMIDLIST) lParam, szPath);

		BOOL bOK = TRUE;
		if (::lstrlen (szPath) < 3)
			bOK = FALSE;
		else {
			szPath[3] = 0;
			if (::GetDriveType (szPath) == DRIVE_CDROM)
				bOK = FALSE;
		}
		::SendMessage (hwnd, BFFM_ENABLEOK, 0, bOK ? 1 : 0);
	}
	return 0;
}
