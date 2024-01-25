
// PacmanV1.h : fichier d'en-tête principal de l'application PacmanV1
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'pch.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"       // symboles principaux


// CPacmanV1App :
// Consultez PacmanV1.cpp pour l'implémentation de cette classe
//

class CPacmanV1App : public CWinAppEx
{
public:
	CPacmanV1App() noexcept;


// Substitutions
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implémentation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPacmanV1App theApp;
