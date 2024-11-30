/*
 * 
 * Dialogs/EllipseInputDlg.hpp
 * Ziyu ZHOU @ SDAU
 * 27/11/24
 * 
*/

#pragma once
#include "resource.h"

class EllipseInputDlg : public CDialog {
    DECLARE_DYNAMIC(EllipseInputDlg)

public:
    EllipseInputDlg(CWnd* pParent = nullptr);
    virtual ~EllipseInputDlg();

    enum { IDD = IDD_ELLIPSE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()

public:
    int m_centreX;
    int m_centreY;
    int m_a;  // ³¤Öá
    int m_b;  // ¶ÌÖá
};

