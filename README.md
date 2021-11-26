# unfrag
Compact OLE compound files(docfile, structured storage,SSOLE)
________________________________________________________________ 
Unfrag (VERSION 1.0)
Copyright (c) 1997 Ziff-Davis Publishing Company
Written by Jeff Prosise
First Published in PC Magazine, US Edition, December 16, 1997.
________________________________________________________________ 

About Unfrag:
If you're a Windows 95 or Windows NT user, you may be losing 
precious disk space without even knowing it. Most hard disks 
today contain compound files created by Microsoft Word, 
Microsoft Excel, and other applications that support Object 
Linking and Embedding (OLE). Compound files, when fragmented, 
can waste a lot of disk space. This issue's free utility, which I've 
named Unfrag to distinguish it from conventional hard disk 
defraggers, hunts down compound files and unfragments them for you.

Usage:
To install Unfrag, copy Unfrag.exe to the folder of your choice. 
There are no auxiliary files or DLLs to copy, and Unfrag writes 
nothing to your system's registry. The entire program can be 
uninstalled simply by deleting Unfrag.exe.

When executed, Unfrag displays a simple dialog box. To begin 
the unfragging process, enter a file name or file name specification 
(for example, *.doc) in the Named box and a path name identifying 
a drive or folder in the Folder box. If you'd like Unfrag to unfrag 
compound files in the specified folder and its subfolders, check the 
"Include subfolders" box. Then click the Unfrag button.

When executed, Unfrag displays a simple dialog box. 
To begin the unfragging process, enter a file name or 
file name specification (for example, *.doc) in the Named 
box and a path name identifying a drive or folder in the 
Folder box. If you'd like Unfrag to unfrag compound files 
in the specified folder and its subfolders, check the 
"Include subfolders" box. Then click the Unfrag button.

As the unfragging process runs its course, Unfrag keeps 
you apprised of its progress with a dialog box. 
"Files examined" indicates how many files have thus far 
been found whose names match the pattern in the Named 
box. "Compound files found" tells you how many of those 
files are compound files. Each time it identifies a compound 
file, Unfrag unfragments the file, compares the new file size 
to the old, and adds the difference to the "Bytes saved" 
value displayed in the dialog. Note that not all compound 
files shrink when they're unfragmented because some have 
no dead space in them. Don't be alarmed if "Bytes saved" 
doesn't increase every time a compound file is processed.

You can cancel an unfragging operation at any time by 
clicking the Cancel button. When unfragging is complete, 
the Cancel button changes to an OK button. The dialog 
box remains on the screen until OK is clicked so you can 
review the results of the unfragging process.  You may 
invoke online help for Unfrag by selecting "Help" from 
the System menu or pressing function key F1.

Unfrag supports a full set of command line options that 
enable it to be run without user intervention. This feature 
will come in handy if you wish to use System Agent or a 
similar utility to schedule the launch of Unfrag and let it 
run unattended. Unfrag's command-line syntax is:

 UNFRAG pathname [/S] [/R]

where pathname is the path to the folder containing the 
files to be unfragged, /S tells Unfrag to process files in the 
specified folder and its subfolders (equivalent to checking 
the "Include subfolders" box in the Unfrag window), and 
/R means "Run now"-the command-line equivalent of 
clicking the Unfrag button in Unfrag's main window. 
The pathname parameter may include a file specification 
(for example, *.doc). Be sure to enclose pathname in 
quotation marks if the path name includes spaces. 
Otherwise, Unfrag will interpret a space embedded in a 
path name as a separator character marking the end of a 
command-line parameter.

A few examples will help to clarify Unfrag's command-line 
options. Suppose you're using System Agent to launch 
Unfrag in the wee hours of the morning, and you'd like 
Unfrag, when started, to unfrag all the .doc files on 
drive C:. Here's the command to use:

UNFRAG C:\*.DOC /S /R

If you'd rather have Unfrag unfrag all the files in drive 
C:'s My Documents folder and its subfolders, use this 
command instead:

UNFRAG "C:\My Documents" /S /R

To restrict Unfrag to just the My Documents folder 
(no subfolders), omit the /S switch:

UNFRAG "C:\My Documents" /R

Be sure to include a /R switch if you want Unfrag to 
start processing files immediately. If you omit this 
switch, the options you entered on the command line 
will show up in Unfrag's window (for example, the 
"Include subfolders" box will be checked if the 
command line includes a /S switch), but unfragging 
won't begin until the Unfrag button is clicked.

Note: The file UNFRAG_S.ZIP contained in UNFRAG.ZIP is the 
source code for Unfrag.  This will only be of interest 
to you if you are a programmer, and can be discarded 
if you choose.

Support for Unfrag:
Support for the free utilities offered by PC Magazine can be 
obtained electronically in the discussion area of PC 
Magazine's Web site. Go to the URL 
http://www.pcmag.com/discuss.htm/ and select the Utilities 
area. You can also access the Utilities discussion area from the 
utility's download page. The authors of current utilities 
generally monitor the discussion area every day. You may 
find an answer to your question simply by reading the 
messages previously posted. If the author is not available and 
you have a question that the sysops can't answer, the editor of 
the Utilities column, who also checks the area each day, will 
contact the author for you.

Jeff Prosise is a contributing editor of PC Magazine.
