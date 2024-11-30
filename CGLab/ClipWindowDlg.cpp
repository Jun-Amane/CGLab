/*
 *
 * Dialogs/ClipWindowDlg.cpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 *
*/


#include "pch.h"
#include "ClipWindowDlg.hpp"

IMPLEMENT_DYNAMIC(ClipWindowDlg, CDialog)

ClipWindowDlg::ClipWindowDlg(CWnd* pParent)
    : CDialog(IDD_CLIP_WINDOW, pParent)
    , m_xmin(0)
    , m_ymin(0)
    , m_xmax(100)
    , m_ymax(100)
{
}

void ClipWindowDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_CLIP_XMIN, m_xmin);
    DDX_Text(pDX, IDC_CLIP_YMIN, m_ymin);
    DDX_Text(pDX, IDC_CLIP_XMAX, m_xmax);
    DDX_Text(pDX, IDC_CLIP_YMAX, m_ymax);
}

BEGIN_MESSAGE_MAP(ClipWindowDlg, CDialog)
END_MESSAGE_MAP()