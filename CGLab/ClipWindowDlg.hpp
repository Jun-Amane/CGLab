/*
 *
 * Dialogs/ClipWindowDlg.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 *
*/


#pragma once

#include "resource.h"

class ClipWindowDlg : public CDialog {
    DECLARE_DYNAMIC(ClipWindowDlg)

public:
    ClipWindowDlg(CWnd* pParent = nullptr);
    virtual ~ClipWindowDlg() = default;

    enum { IDD = IDD_CLIP_WINDOW };

    int m_xmin;
    int m_ymin;
    int m_xmax;
    int m_ymax;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
};