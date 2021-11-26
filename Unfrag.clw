; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUnfragDlg
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Unfrag.h"

ClassCount=8
Class1=CUnfragApp
Class2=CUnfragDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDR_ACCELERATOR1
Resource2=IDR_MAINFRAME
Resource3=IDD_HELP_PAGE
Class4=CProgressDialog
Resource4=IDD_UNFRAG_DIALOG
Resource5=IDD_PROGRESS_DIALOG
Class5=CAboutPage
Class6=CHelpPage
Class7=CUnfragPropertySheet
Class8=CSpecialEdit
Resource6=IDD_ABOUT_PAGE

[CLS:CUnfragApp]
Type=0
HeaderFile=Unfrag.h
ImplementationFile=Unfrag.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CUnfragApp

[CLS:CUnfragDlg]
Type=0
HeaderFile=UnfragDlg.h
ImplementationFile=UnfragDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CUnfragDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=UnfragDlg.h
ImplementationFile=UnfragDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_UNFRAG_DIALOG]
Type=1
Class=CUnfragDlg
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_FILE,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_FOLDER,combobox,1344340290
Control8=IDC_BROWSE,button,1342242816
Control9=IDC_SUBFOLDERS,button,1342242819
Control10=IDC_UNFRAG,button,1476460545
Control11=IDC_IMAGE,static,1342312961

[DLG:IDD_PROGRESS_DIALOG]
Type=1
Class=CProgressDialog
ControlCount=10
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_FILES,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_COMPOUNDFILES,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BYTESSAVED,static,1342308352
Control8=IDCANCEL,button,1342242816
Control9=IDC_PROGRESS,msctls_progress32,1350565888
Control10=IDC_INITTEXT,static,1342308865

[CLS:CProgressDialog]
Type=0
HeaderFile=ProgressDialog.h
ImplementationFile=ProgressDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CProgressDialog
VirtualFilter=dWC

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=ID_HELP
CommandCount=1

[DLG:IDD_ABOUT_PAGE]
Type=1
Class=CAboutPage
ControlCount=4
Control1=IDC_TITLE,static,1342308481
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308481
Control4=IDC_STATIC,static,1342308481

[DLG:IDD_HELP_PAGE]
Type=1
Class=CHelpPage
ControlCount=1
Control1=IDC_HELPTEXT,edit,1352730692

[CLS:CAboutPage]
Type=0
HeaderFile=AboutPage.h
ImplementationFile=AboutPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CAboutPage
VirtualFilter=idWC

[CLS:CHelpPage]
Type=0
HeaderFile=HelpPage.h
ImplementationFile=HelpPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CHelpPage
VirtualFilter=idWC

[CLS:CUnfragPropertySheet]
Type=0
HeaderFile=UnfragPropertySheet.h
ImplementationFile=UnfragPropertySheet.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CUnfragPropertySheet
VirtualFilter=hWC

[CLS:CSpecialEdit]
Type=0
HeaderFile=SpecialEdit.h
ImplementationFile=SpecialEdit.cpp
BaseClass=CEdit
Filter=W
LastObject=CSpecialEdit
VirtualFilter=WC

