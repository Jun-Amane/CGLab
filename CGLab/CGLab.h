
// CGLab.h : main header file for the CGLab application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCGLabApp:
// See CGLab.cpp for the implementation of this class
//

class CCGLabApp : public CWinApp
{
public:
	CCGLabApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCGLabApp theApp;
