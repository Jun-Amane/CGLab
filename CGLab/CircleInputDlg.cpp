/*
 * 
 * Dialogs/CircleInputDlg.cpp
 * Ziyu ZHOU @ SDAU
 * 27/11/24
 * 
*/

#include "pch.h"
#include "CircleInputDlg.hpp"

IMPLEMENT_DYNAMIC(CircleInputDlg, CDialog)

CircleInputDlg::CircleInputDlg(CWnd* pParent)
    : CDialog(IDD_CIRCLE, pParent)
    , m_centreX(0)
    , m_centreY(0)
    , m_radius(0)
{
}

CircleInputDlg::~CircleInputDlg()
{
}

void CircleInputDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_CIRCLE_CENTRE_X, m_centreX);
    DDX_Text(pDX, IDC_CIRCLE_CENTRE_Y, m_centreY);
    DDX_Text(pDX, IDC_CIRCLE_RADIUS, m_radius);
}

BEGIN_MESSAGE_MAP(CircleInputDlg, CDialog)
END_MESSAGE_MAP()