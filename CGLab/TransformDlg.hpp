/*
 * 
 * Dialogs/TransformDlg.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 * 
*/

#pragma once
#include "resource.h"

 // ƽ�ƶԻ���
class TranslateDlg : public CDialog {
    DECLARE_DYNAMIC(TranslateDlg)
public:
    TranslateDlg(CWnd* pParent = nullptr);
    virtual ~TranslateDlg() = default;
    enum { IDD = IDD_TRANSLATE };

    int m_dx;  // x����ƽ����
    int m_dy;  // y����ƽ����

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
};

// ��ת�Ի���
class RotateDlg : public CDialog {
    DECLARE_DYNAMIC(RotateDlg)
public:
    RotateDlg(CWnd* pParent = nullptr);
    virtual ~RotateDlg() = default;
    enum { IDD = IDD_ROTATE };

    double m_angle;  // ��ת�Ƕ�
    int m_cx;       // ��ת����x
    int m_cy;       // ��ת����y

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
};

// ���жԻ���
class ShearDlg : public CDialog {
    DECLARE_DYNAMIC(ShearDlg)
public:
    ShearDlg(CWnd* pParent = nullptr);
    virtual ~ShearDlg() = default;
    enum { IDD = IDD_SHEAR };

    double m_shx;  // x�����������
    double m_shy;  // y�����������

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
};

// ���ŶԻ���
class ScaleDlg : public CDialog {
    DECLARE_DYNAMIC(ScaleDlg)
public:
    ScaleDlg(CWnd* pParent = nullptr);
    virtual ~ScaleDlg() = default;
    enum { IDD = IDD_SCALE };

    double m_sx;  // x������������
    double m_sy;  // y������������
    int m_cx;     // ��������x
    int m_cy;     // ��������y

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
};

// �ԳƶԻ���
class ReflectDlg : public CDialog {
    DECLARE_DYNAMIC(ReflectDlg)
public:
    ReflectDlg(CWnd* pParent = nullptr);
    virtual ~ReflectDlg() = default;
    enum { IDD = IDD_REFLECT };

    int m_type;    // �Գ����ͣ�0-����x�ᣬ1-����y�ᣬ2-����ֱ��
    double m_k;    // ֱ��б��
    double m_b;    // ֱ�߽ؾ�

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
    afx_msg void OnBnClickedRadioType(UINT nID);
};

