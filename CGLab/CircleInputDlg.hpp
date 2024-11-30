/*
 * 
 * Dialogs/CircleInputDlg.hpp
 * Ziyu ZHOU @ SDAU
 * 27/11/24
 * 
*/

#pragma once

#include "resource.h"

class CircleInputDlg : public CDialog {
    DECLARE_DYNAMIC(CircleInputDlg)

public:
    CircleInputDlg(CWnd* pParent = nullptr);
    virtual ~CircleInputDlg();

    enum { IDD = IDD_CIRCLE };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()

public:
    int m_centreX;
    int m_centreY;
    int m_radius;
};

