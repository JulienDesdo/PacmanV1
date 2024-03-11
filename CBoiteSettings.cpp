// CBoiteSettings.cpp : fichier d'implémentation
//

#include "pch.h"
#include "PacmanV1.h"
#include "CBoiteSettings.h"
#include "afxdialogex.h"


// boîte de dialogue de CBoiteSettings

IMPLEMENT_DYNAMIC(CBoiteSettings, CDialog)

CBoiteSettings::CBoiteSettings(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, BDD_admin(TRUE)
	, BDD_affch(TRUE)
	, BDD_interpolation(FALSE)
	, BDD_speed_selected(200)
	, BDD_life_pacman(3)
	, BDD_lvl(0)
{

}

CBoiteSettings::~CBoiteSettings()
{
}

void CBoiteSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK2, BDD_admin);
	DDX_Check(pDX, IDC_CHECK1, BDD_affch);
	DDX_Check(pDX, IDC_CHECK3, BDD_interpolation);
	DDX_Text(pDX, IDC_EDIT1, BDD_speed_selected);
	DDX_Text(pDX, IDC_EDIT2, BDD_life_pacman);
	DDV_MinMaxInt(pDX, BDD_life_pacman, 1, INT_MAX);
	DDX_Text(pDX, IDC_EDIT3, BDD_lvl);
	DDV_MinMaxInt(pDX, BDD_lvl, 0, 100);
}


BEGIN_MESSAGE_MAP(CBoiteSettings, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDC_CHECK2, &CBoiteSettings::OnCheckAdminMode)
	ON_BN_CLICKED(IDC_CHECK1, &CBoiteSettings::OnBnAffich_Jeu)
	ON_BN_CLICKED(IDC_CHECK3, &CBoiteSettings::OnBnInterpolation)
	ON_EN_CHANGE(IDC_EDIT1, &CBoiteSettings::OnSpeed)
	ON_EN_CHANGE(IDC_EDIT2, &CBoiteSettings::OnLifePacman)
	ON_EN_CHANGE(IDC_EDIT3, &CBoiteSettings::OnLvlGame)
END_MESSAGE_MAP()


// gestionnaires de messages de CBoiteSettings


void CBoiteSettings::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
}


void CBoiteSettings::OnClose()
{
	CDialog::OnClose();

	/*
	// Obtenir l'état actuel de la case à cocher "Admin"
	BOOL bChecked = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();

	// Sauvegarder l'état actuel de la case à cocher "Admin" dans les paramètres de l'application
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("AdminMode"), bChecked);
	*/
}

void CBoiteSettings::OnCheckAdminMode() // case admin 
{
	/*
	// Obtenir l'état actuel de la case à cocher
	BOOL bChecked = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();

	// Mettre à jour la variable membre pour refléter l'état actuel de la case à cocher
	 m_bAdminMode = bChecked;
	 */
	if (BDD_admin) BDD_admin = false;
	else BDD_admin = true; 
	 
}


BOOL CBoiteSettings::OnInitDialog()
{
	CDialog::OnInitDialog();

	/*
	// Charger l'état précédent de la case à cocher "Admin" depuis les paramètres de l'application
	BOOL bChecked = AfxGetApp()->GetProfileInt(_T("Settings"), _T("AdminMode"), FALSE);
	((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(bChecked);
	m_bAdminMode = bChecked; // Assurez-vous de mettre à jour votre variable membre également
	*/

	if (BDD_affch) ((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(BST_CHECKED);
	if (BDD_admin) ((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(BST_CHECKED);
	return TRUE; 
}


void CBoiteSettings::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) // Pour arrêter le jeu quand on ouvre le bdd
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	if (nState == WA_ACTIVE || nState == WA_CLICKACTIVE)
	{
		// La boîte de dialogue a été activée
		// Faites quelque chose ici en réponse à l'activation
		m_isActive = true;
	}
	else if (nState == WA_INACTIVE)
	{
		// La boîte de dialogue a été désactivée
		// Faites quelque chose ici en réponse à la désactivation
		m_isActive = false;
	}
}

void CBoiteSettings::OnBnAffich_Jeu() // case "afficher le jeu"
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	if (BDD_affch) BDD_affch = false;
	else BDD_affch = true; 
}


void CBoiteSettings::OnBnInterpolation()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	if (BDD_interpolation) BDD_interpolation = false;
	else BDD_interpolation = true;
}


void CBoiteSettings::OnSpeed()
{
	// TODO:  S'il s'agit d'un contrôle RICHEDIT, le contrôle ne
	// envoyez cette notification sauf si vous substituez CDialog::OnInitDialog()
	// fonction et appelle CRichEditCtrl().SetEventMask()
	// avec l'indicateur ENM_CHANGE ajouté au masque grâce à l'opérateur OR.

	// TODO:  Ajoutez ici le code de votre gestionnaire de notification de contrôle
	CString strSpeedValue;
	GetDlgItemText(IDC_EDIT1, strSpeedValue); // Récupérer le texte de la zone de texte

	// Convertir le texte en entier et le stocker dans m_SpeedValue
	BDD_speed_selected = _ttoi(strSpeedValue);
}


void CBoiteSettings::OnLifePacman()
{
	// TODO:  S'il s'agit d'un contrôle RICHEDIT, le contrôle ne
	// envoyez cette notification sauf si vous substituez CDialog::OnInitDialog()
	// fonction et appelle CRichEditCtrl().SetEventMask()
	// avec l'indicateur ENM_CHANGE ajouté au masque grâce à l'opérateur OR.

	// TODO:  Ajoutez ici le code de votre gestionnaire de notification de contrôle
	CString strLifeValue;
	GetDlgItemText(IDC_EDIT1, strLifeValue); // Récupérer le texte de la zone de texte

	// Convertir le texte en entier et le stocker dans m_SpeedValue
	BDD_life_pacman = _ttoi(strLifeValue);
}


void CBoiteSettings::OnLvlGame()
{
	// TODO:  S'il s'agit d'un contrôle RICHEDIT, le contrôle ne
	// envoyez cette notification sauf si vous substituez CDialog::OnInitDialog()
	// fonction et appelle CRichEditCtrl().SetEventMask()
	// avec l'indicateur ENM_CHANGE ajouté au masque grâce à l'opérateur OR.

	// TODO:  Ajoutez ici le code de votre gestionnaire de notification de contrôle
	CString strLvLValue;
	GetDlgItemText(IDC_EDIT1, strLvLValue); // Récupérer le texte de la zone de texte

	// Convertir le texte en entier et le stocker dans m_SpeedValue
	BDD_lvl = _ttoi(strLvLValue);
}
