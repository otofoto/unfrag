// HelpPage.cpp : implementation file
//

#include "stdafx.h"
#include "Unfrag.h"
#include "SpecialEdit.h"
#include "HelpPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpPage property page

IMPLEMENT_DYNCREATE(CHelpPage, CPropertyPage)

CHelpPage::CHelpPage() : CPropertyPage(CHelpPage::IDD)
{
	//{{AFX_DATA_INIT(CHelpPage)
	//}}AFX_DATA_INIT
	m_psp.dwFlags &= ~PSP_HASHELP;
}

CHelpPage::~CHelpPage()
{
}

void CHelpPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpPage)
	DDX_Control(pDX, IDC_HELPTEXT, m_wndEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHelpPage, CPropertyPage)
	//{{AFX_MSG_MAP(CHelpPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpPage message handlers

static const TCHAR szHelpText[] = {
	"If you’re a Windows 95 or Windows NT user, you may be losing " \
	"precious disk space without even knowing it. Most hard disks " \
	"today contain document files created by Microsoft Word, " \
	"Microsoft Excel, and other applications that support Object " \
	"Linking and Embedding (OLE). Part of a spectrum of technologies " \
	"known as ActiveX, OLE is the software protocol that lets objects " \
	"created by one application appear in documents created by " \
	"another. (A good example is a Word document containing an " \
	"Excel spreadsheet.)\r\n\r\n" \
	
	"Most such applications use compound files to store documents. " \
	"Internally, a compound file is organized into storages and " \
	"streams, in much the same way that a hard disk is organized " \
	"into folders and files. An OLE/ActiveX technology known as " \
	"structured storage provides the means for programmers to " \
	"create and manipulate compound files.\r\n\r\n" \

	"Compound files make an OLE programmer’s life immeasurably easier " \
	"because partitioning a file into storages and streams makes it " \
	"simple for two applications to write to the same file without " \
	"stepping on each other’s toes. But compound files have a dark " \
	"side, too. Like hard disks, compound files are subject to " \
	"fragmentation. But whereas a fragmented disk doesn’t rob you of " \
	"disk space, fragmented compound files often consume disk space " \
	"needlessly. A typical Word file contains about 4K of 'slop,' even " \
	"if that file contains no embedded objects. Theoretically, it’s " \
	"possible for a compound file containing just a few kilobytes of " \
	"actual data to consume a megabyte or more of disk space.\r\n\r\n" \

	"Unfrag combats this problem by hunting down compound " \
	"files and unfragmenting them. To begin an unfragging operation, enter " \
	"a file name or file name specification (for example, *.doc) in the " \
	"Named box and a path name identifying a drive or folder in the Folder " \
	"box. Then click the Unfrag button. If you’d like Unfrag to unfrag " \
	"compound files in the specified folder AND its subfolders, check the " \
	"'Include subfolders' box. To unfrag all the compound files on " \
	"a drive, simply leave the Named field blank (which is equivalent to " \
	"entering *.*), type the path to the drive’s root directory in the " \
	"Folder box (for example, C:\\), and check 'Include subfolders.'\r\n\r\n" \

	"You may click the downward-pointing arrow next to the Folder box to " \
	"see a list of available drives, or use the Browse button to pick a " \
	"specific drive or folder from a dialog box.\r\n\r\n" \

	"Unfrag also supports a full set of command line options that enable " \
	"it to be driven from a command line. This feature will come in handy " \
	"if you wish to use System Agent or a similar utility to launch " \
	"Unfrag and let it run unattended. Unfrag’s command-line syntax is:\r\n\r\n" \

	"  UNFRAG pathname [/S] [/R] [/C]\r\n\r\n" \

	"where pathname is the path to the folder containing the files to " \
	"be unfragged, /S tells Unfrag to process files in the specified " \
	"folder and its subfolders (equivalent to checking the 'Include " \
	"subfolders' box in the Unfrag window), /R means 'Run now' (the " \
	"command-line equivalent of clicking the Unfrag button in Unfrag's " \
	"main window), and /C tells Unfrag to close itself automatically " \
	"once unfragging is complete.\r\n\r\n" \

	"The pathname parameter may include a file " \
	"specification (for example, *.doc). Be sure to enclose pathname in " \
	"quotation marks if the path name includes spaces. Otherwise, Unfrag " \
	"will interpret a space embedded in a path name as a separator character " \
	"marking the end of a command-line parameter.\r\n\r\n"

	"Be sure to include a /R switch if you want Unfrag to start processing " \
	"files immediately. If you omit this switch, the options you entered on " \
	"the command line will show up in Unfrag’s window (for example, the " \
	"'Include subfolders' box will be checked if the command line includes a " \
	"/S switch), but unfragging won’t begin until the Unfrag button is clicked."
};

BOOL CHelpPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_wndEdit.SetMargins (3, 6);
	m_wndEdit.SetWindowText (szHelpText);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
