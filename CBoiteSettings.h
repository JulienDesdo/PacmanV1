#pragma once

// boîte de dialogue de CBoiteSettings

class CBoiteSettings : public CDialog
{
	DECLARE_DYNAMIC(CBoiteSettings)

public:
	CBoiteSettings(CWnd* pParent = nullptr);   // constructeur standard
	virtual ~CBoiteSettings();

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif
	bool m_isActive = false; 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//bool m_bAdminMode;
	afx_msg void OnCheckAdminMode();
	virtual BOOL OnInitDialog();
	BOOL BDD_admin = false;
	BOOL BDD_affch = true;
	BOOL BDD_interpolation = false;
	afx_msg void OnBnAffich_Jeu();
	afx_msg void OnBnInterpolation();
	int BDD_speed_selected;
	afx_msg void OnSpeed();
	int BDD_life_pacman;
	afx_msg void OnLifePacman();
	int BDD_lvl;
	afx_msg void OnLvlGame();
};
