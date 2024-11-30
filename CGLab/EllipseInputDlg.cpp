/*
 *
 * Dialogs/EllipseInputDlg.cpp
 * Ziyu ZHOU @ SDAU
 * 27/11/24
 *
*/

#include "pch.h"
#include "EllipseInputDlg.hpp"

IMPLEMENT_DYNAMIC(EllipseInputDlg, CDialog)

EllipseInputDlg::EllipseInputDlg(CWnd* pParent)
    : CDialog(IDD_ELLIPSE, pParent)
    , m_centreX(0)
    , m_centreY(0)
    , m_a(0)
    , m_b(0)
{
}

EllipseInputDlg::~EllipseInputDlg()
{
}

void EllipseInputDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ELLIPSE_CENTRE_X, m_centreX);
    DDX_Text(pDX, IDC_ELLIPSE_CENTRE_Y, m_centreY);
    DDX_Text(pDX, IDC_ELLIPSE_A, m_a);
    DDX_Text(pDX, IDC_ELLIPSE_B, m_b);
}

BEGIN_MESSAGE_MAP(EllipseInputDlg, CDialog)
END_MESSAGE_MAP()