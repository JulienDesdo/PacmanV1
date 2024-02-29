
// PacmanV1View.cpp : implémentation de la classe CPacmanV1View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS peuvent être définis dans les gestionnaires d'aperçu, de miniature
// et de recherche d'implémentation de projet ATL, et permettent le partage de code de document avec ce projet.
#ifndef SHARED_HANDLERS
#include "PacmanV1.h"
#endif

#include "PacmanV1Doc.h"
#include "PacmanV1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#include "matrix.h"
//#include "Cpacman.h"
//#include "pos.h"
// CPacmanV1View

IMPLEMENT_DYNCREATE(CPacmanV1View, CView)

BEGIN_MESSAGE_MAP(CPacmanV1View, CView)
	// Commandes d'impression standard
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPacmanV1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// construction/destruction de CPacmanV1View

CPacmanV1View::CPacmanV1View() noexcept
{
	// TODO: ajoutez ici du code de construction
	GameManager game;
	//dir_pacman = 0; // 0 = left, 1=right, 2=down, 3=up 
	square = 35;
	timer2_active = 0;

}

CPacmanV1View::~CPacmanV1View()
{
}

BOOL CPacmanV1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CPacmanV1View::afficher(int i, int j, CDC* pDC){
	CRect rect(j * square, i * square, (j + 1) * square, (i + 1) * square); // car (x,y) inversé par rapport à la matrice. Matrix: x lignes matrices; y colonnes matrices.
	CRect smallFoodRect(rect.left + square / 4, rect.top + square / 4, rect.left + square / 2.3, rect.top + square / 2.3);
	CRect bigFoodRect(rect.left + square / 4, rect.top + square / 4, rect.left + square / 1.4, rect.top + square / 1.4);

	switch (game.graph.get_value(i, j))
	{
	case 0: // vide (rectangle noir) 
		pDC->FillSolidRect(&rect, RGB(0, 0, 0));
		break;

	case 1: // block (rectangle bleu) 
		pDC->FillSolidRect(&rect, RGB(0, 0, 255));
		break;
	case 2: // pacman (rectangle jaune)
		pDC->FillSolidRect(&rect, RGB(255, 255, 0));
		break;
	case 3:
		pDC->FillSolidRect(&rect, RGB(158, 158, 158)); // phantom par défaut, gris
		break;
	case 4:
		pDC->FillSolidRect(&rect, RGB(255, 0, 0)); // phantom Blinky (rectangle rouge)
		break;
	case 14:
		pDC->FillSolidRect(&rect, RGB(255, 0, 0)); // phantom Blinky (rectangle rouge)
		break;
	case 24:
		pDC->FillSolidRect(&rect, RGB(255, 0, 0)); // phantom Blinky (rectangle rouge)
		break;
	case 5:
		pDC->FillSolidRect(&rect, RGB(0, 255, 255)); // phantom Inky (rectangle cyan)
		break;
	case 6:
		pDC->FillSolidRect(&rect, RGB(253, 108, 158)); // phantom Pinky (rectangle rose) 
		break;
	case 7:
		pDC->FillSolidRect(&rect, RGB(255, 69, 0)); // phantom Clyde (rectangle orange)
		break;
	case 10: // case de la nourriture petite 
		pDC->FillSolidRect(&rect, RGB(0, 0, 0));
		pDC->FillSolidRect(&smallFoodRect, RGB(255, 255, 255)); // Rectangle blanc
		break;

	case 20: // case de la grosse nourriture
		pDC->FillSolidRect(&rect, RGB(0, 0, 0));
		pDC->FillSolidRect(&bigFoodRect, RGB(255, 255, 255)); // Rectangle blanc
		break;

	default:
		break;
	}


}

void CPacmanV1View::OnDraw(CDC* pDC)
{
	CPacmanV1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ajoutez ici le code de dessin pour les données natives
	SetTimer(1, 375, NULL);
	
	//SetFocus();
	

	
	// Affichage du score
	CString scoreText;
	scoreText.Format(_T("SCORE   %d"), game.pacman.score);
	CFont font;
	font.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")); // Créer une fonte plus grande, en gras
	CFont* oldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(255, 255, 255)); // Mettre la couleur en blanc
	pDC->TextOutW(120, square*21, scoreText); // pDC->TextOutW(120, square*21, scoreText); 
	pDC->SelectObject(oldFont); // Restaurer la fonte par défaut

	// Affichage des vies
	CString livesText;
	livesText.Format(_T("LIVES   %d"), game.pacman.life_nbr);
	font.DeleteObject(); // Supprimer l'ancienne fonte
	font.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")); // Créer une fonte plus grande, en gras
	oldFont = pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(255, 255, 255)); // Mettre la couleur en blanc
	pDC->TextOutW(30, square*21, livesText);
	pDC->SelectObject(oldFont); // Restaurer la fonte par défaut


}


// impression de CPacmanV1View


void CPacmanV1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPacmanV1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// préparation par défaut
	return DoPreparePrinting(pInfo);
}

void CPacmanV1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ajoutez une initialisation supplémentaire avant l'impression
}

void CPacmanV1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ajoutez un nettoyage après l'impression
}

void CPacmanV1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPacmanV1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// diagnostics de CPacmanV1View

#ifdef _DEBUG
void CPacmanV1View::AssertValid() const
{
	CView::AssertValid();
}

void CPacmanV1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPacmanV1Doc* CPacmanV1View::GetDocument() const // la version non Debug est inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPacmanV1Doc)));
	return (CPacmanV1Doc*)m_pDocument;
}
#endif //_DEBUG


// gestionnaires de messages de CPacmanV1View


void CPacmanV1View::OnTimer(UINT_PTR nIDEvent)
{
	CDC* pDC = GetDC();

	if (nIDEvent == 1) {
		// Mouvement de Pacman
		switch (game.pacman.dir) {
		case 0:
			game.left(game.pacman);
			break;
		case 1:
			game.right(game.pacman);
			break;
		case 2:
			game.down(game.pacman);
			break;
		case 3:
			game.up(game.pacman);
			break;
		default:
			break;
		}

		game.Move_fantome();
		

		if (game.affich_tot) { // affichage toutes les 375. 
			for (int i = 0; i <= 20; i++) {
				for (int j = 0; j <= 18; j++) {
					afficher(i, j, pDC);
				}
			}
		}
		
	}

	CView::OnTimer(nIDEvent);
}


//void CPacmanV1View::OnKey Down(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: ajoutez ici le code de votre gestionnaire de messages et/ou les paramètres par défaut des appels
//	switch (nChar) {
//	case 'z':
//		pacman.up();
//		break; 
//
//	case 'q':
//		pacman.left();
//		break;
//
//	case 's':
//		pacman.down();
//		//AfxMessageBox(L"Key down!");
//		break;
//
//	case 'd':
//		pacman.right();
//		break; 
//	default : 
//		break;
//	}
//
//	
//	CView::OnKeyDown(nChar, nRepCnt, nFlags);
//}


BOOL CPacmanV1View::PreTranslateMessage(MSG* pMsg)
{
	
	// TODO: ajoutez ici votre code spécialisé et/ou l'appel de la classe de base
	int X = (int)pMsg->wParam;

	// 0 = left, 1=right, 2=down, 3=up
	if (pMsg->message == WM_KEYDOWN) {
		if (X == VK_UP) {
			//game.up();
			if (!game.check_up(game.pacman)) game.pacman.dir = 3;
			//AfxMessageBox(L"UP !");
			
		}
		else if (X == VK_DOWN) {
			//game.down();
			if (!game.check_down(game.pacman)) game.pacman.dir = 2;
			//AfxMessageBox(L"DOWN!");
		}
		else if (X == VK_LEFT) {
			//game.left();
			if (!game.check_left(game.pacman)) game.pacman.dir = 0;
			//AfxMessageBox(L"LEFT!");
		}
		else if (X == VK_RIGHT) {
			//game.right();
			if (!game.check_right(game.pacman)) game.pacman.dir = 1;
			//AfxMessageBox(L"RIGHT");
		}
	}

	return CView::PreTranslateMessage(pMsg);
	
}


void CPacmanV1View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	/*
	CDC* pDC = GetDC();
	// TODO: ajoutez ici votre code spécialisé et/ou l'appel de la classe de base
	for (int i = 0; i <= 20; i++) {
		for (int j = 0; j <= 18; j++) {
			afficher(i, j, pDC);
			game.affich_tot = false;
		}
	}
	Invalidate(); // Force le redessin de la vue
	*/
}
