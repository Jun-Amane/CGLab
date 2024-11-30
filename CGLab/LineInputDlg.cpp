/*
 * 
 * Dialogs/LineInputDlg.cpp
 * Ziyu ZHOU @ SDAU
 * 26/11/24
 * 
*/

#include "pch.h"
#include "LineInputDlg.hpp"

IMPLEMENT_DYNAMIC(LineInputDlg, CDialog)

LineInputDlg::LineInputDlg(CWnd* pParent)
    : CDialog(IDD_LINE, pParent)
    , m_x0(0)
    , m_y0(0)
    , m_x1(0)
    , m_y1(0)
{
}

LineInputDlg::~LineInputDlg()
{
}

void LineInputDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_LINE_DDA_X0, m_x0);
    DDX_Text(pDX, IDC_LINE_DDA_Y0, m_y0);
    DDX_Text(pDX, IDC_LINE_DDA_X1, m_x1);
    DDX_Text(pDX, IDC_LINE_DDA_Y1, m_y1);
}

BEGIN_MESSAGE_MAP(LineInputDlg, CDialog)
END_MESSAGE_MAP()

