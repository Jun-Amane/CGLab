/*
 * 
 * Dialogs/TransformDlg.cpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 * 
*/

#include "pch.h"
#include "TransformDlg.hpp"

 // 平移对话框实现
IMPLEMENT_DYNAMIC(TranslateDlg, CDialog)

TranslateDlg::TranslateDlg(CWnd* pParent)
    : CDialog(IDD_TRANSLATE, pParent)
    , m_dx(0)
    , m_dy(0)
{
}

void TranslateDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TRANSLATE_DX, m_dx);
    DDX_Text(pDX, IDC_TRANSLATE_DY, m_dy);
}

BEGIN_MESSAGE_MAP(TranslateDlg, CDialog)
END_MESSAGE_MAP()

// 旋转对话框实现
IMPLEMENT_DYNAMIC(RotateDlg, CDialog)

RotateDlg::RotateDlg(CWnd* pParent)
    : CDialog(IDD_ROTATE, pParent)
    , m_angle(0)
    , m_cx(0)
    , m_cy(0)
{
}

void RotateDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ROTATE_ANGLE, m_angle);
    DDX_Text(pDX, IDC_ROTATE_CX, m_cx);
    DDX_Text(pDX, IDC_ROTATE_CY, m_cy);
}

BEGIN_MESSAGE_MAP(RotateDlg, CDialog)
END_MESSAGE_MAP()

// 错切对话框实现
IMPLEMENT_DYNAMIC(ShearDlg, CDialog)

ShearDlg::ShearDlg(CWnd* pParent)
    : CDialog(IDD_SHEAR, pParent)
    , m_shx(0)
    , m_shy(0)
{
}

void ShearDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_SHEAR_SHX, m_shx);
    DDX_Text(pDX, IDC_SHEAR_SHY, m_shy);
}

BEGIN_MESSAGE_MAP(ShearDlg, CDialog)
END_MESSAGE_MAP()

// 缩放对话框实现
IMPLEMENT_DYNAMIC(ScaleDlg, CDialog)

ScaleDlg::ScaleDlg(CWnd* pParent)
    : CDialog(IDD_SCALE, pParent)
    , m_sx(1.0)
    , m_sy(1.0)
    , m_cx(0)
    , m_cy(0)
{
}

void ScaleDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_SACLE_SX, m_sx);
    DDX_Text(pDX, IDC_SACLE_SY, m_sy);
    DDX_Text(pDX, IDC_SACLE_CX, m_cx);
    DDX_Text(pDX, IDC_SACLE_CY, m_cy);
}

BEGIN_MESSAGE_MAP(ScaleDlg, CDialog)
END_MESSAGE_MAP()

// 对称对话框实现
IMPLEMENT_DYNAMIC(ReflectDlg, CDialog)

ReflectDlg::ReflectDlg(CWnd* pParent)
    : CDialog(IDD_REFLECT, pParent)
    , m_type(0)
    , m_k(0)
    , m_b(0)
{
}

void ReflectDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_RADIO_X, m_type);
    DDX_Text(pDX, IDC_REFLECT_K, m_k);
    DDX_Text(pDX, IDC_REFLECT_B, m_b);
}

BEGIN_MESSAGE_MAP(ReflectDlg, CDialog)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_X, IDC_RADIO_LINE, &ReflectDlg::OnBnClickedRadioType)
END_MESSAGE_MAP()

void ReflectDlg::OnBnClickedRadioType(UINT nID)
{
    m_type = nID - IDC_RADIO_X;
    
    GetDlgItem(IDC_REFLECT_K)->EnableWindow(m_type == 2);
    GetDlgItem(IDC_REFLECT_B)->EnableWindow(m_type == 2);
}