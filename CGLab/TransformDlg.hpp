/*
 * 
 * Dialogs/TransformDlg.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 * 
*/

#pragma once
#include "resource.h"

 // 平移对话框
class TranslateDlg : public CDialog {
    DECLARE_DYNAMIC(TranslateDlg)
public:
    TranslateDlg(CWnd* pParent = nullptr);
    virtual ~TranslateDlg() = default;
    enum { IDD = IDD_TRANSLATE };

    int m_dx;  // x方向平移量
    int m_dy;  // y方向平移量

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
};

// 旋转对话框
class RotateDlg : public CDialog {
    DECLARE_DYNAMIC(RotateDlg)
public:
    RotateDlg(CWnd* pParent = nullptr);
    virtual ~RotateDlg() = default;
    enum { IDD = IDD_ROTATE };

    double m_angle;  // 旋转角度
    int m_cx;       // 旋转中心x
    int m_cy;       // 旋转中心y

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
};

// 错切对话框
class ShearDlg : public CDialog {
    DECLARE_DYNAMIC(ShearDlg)
public:
    ShearDlg(CWnd* pParent = nullptr);
    virtual ~ShearDlg() = default;
    enum { IDD = IDD_SHEAR };

    double m_shx;  // x方向错切因子
    double m_shy;  // y方向错切因子

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
};

// 缩放对话框
class ScaleDlg : public CDialog {
    DECLARE_DYNAMIC(ScaleDlg)
public:
    ScaleDlg(CWnd* pParent = nullptr);
    virtual ~ScaleDlg() = default;
    enum { IDD = IDD_SCALE };

    double m_sx;  // x方向缩放因子
    double m_sy;  // y方向缩放因子
    int m_cx;     // 缩放中心x
    int m_cy;     // 缩放中心y

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
};

// 对称对话框
class ReflectDlg : public CDialog {
    DECLARE_DYNAMIC(ReflectDlg)
public:
    ReflectDlg(CWnd* pParent = nullptr);
    virtual ~ReflectDlg() = default;
    enum { IDD = IDD_REFLECT };

    int m_type;    // 对称类型：0-关于x轴，1-关于y轴，2-关于直线
    double m_k;    // 直线斜率
    double m_b;    // 直线截距

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedRadioType(UINT nID);
};

