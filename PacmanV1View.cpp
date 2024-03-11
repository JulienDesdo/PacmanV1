
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
	ON_COMMAND(ID_SETTINGSGAME, &CPacmanV1View::OnSettingsgame)
END_MESSAGE_MAP()

// construction/destruction de CPacmanV1View

CPacmanV1View::CPacmanV1View() noexcept
{
	// TODO: ajoutez ici du code de construction
	GameManager game;
	//dir_pacman = 0; // 0 = left, 1=right, 2=down, 3=up 
	square = 35;
	timer2_active = 0;
	nb_seg = 16;
	fps = 60;  // Nombre d'images par secondes. Utile à faire varier pour augmenter l'interpolation. 
	fps_timer = int(1000 / 60);
	Xcharg1 = 0; 
	Ycharg1 = 0;
	Xcharg2 = 0;
	Ycharg2 = 0;
	interpolation_active = false; 
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

/*
void CPacmanV1View::permuter_int(int &a, int &b) { int c; c = a; a = b; b = c;}
void CPacmanV1View::permuter_double(double &a, double &b) { double c; c = a; a = b; b = c; }
*/

void CPacmanV1View::interpolation(int i, int j) {
	int X1 = j * square;
	int Y1 = i * square;
	int X2 = (j + 1) * square;
	int Y2 = (i + 1) * square;

	int X1_previous = X1;
	int Y1_previous = Y1;
	int X2_previous = X2;
	int Y2_previous = Y2;

	switch (game.graph.get_value(i, j)) {
	case 2: // pacman 
		switch (game.pacman.dir) {
		case 0: // direction = left
			X1_previous = (j + 1) * square; // modif
			Y1_previous = i * square;
			X2_previous = (j + 2) * square; // modif
			Y2_previous = (i + 1) * square;
			break;
		case 1: // direction = right
			X1_previous = (j - 1) * square; // modif
			Y1_previous = i * square;
			X2_previous = (j)*square; // modif
			Y2_previous = (i + 1) * square;
			break;
		case 2: // direction = down
			X1_previous = j * square;
			Y1_previous = (i - 1) * square; // modif
			X2_previous = (j + 1) * square;
			Y2_previous = (i)*square; // modif 
			break;
		case 3: // direction = up
			X1_previous = j * square;
			Y1_previous = (i + 1) * square; // modif 
			X2_previous = (j + 1) * square;
			Y2_previous = (i + 2) * square; // modif
			break;
		}
		if (game.horloge == 1) { // si X1 > X2 inverser car MFC ne comprend pas... 
			game.pacman.interpolation_value_X1 = (X1 - X1_previous) / nb_seg;
			Xcharg1 = game.pacman.interpolation_value_X1;
			game.pacman.interpolation_value_Y1 = (Y1 - Y1_previous) / nb_seg;
			Ycharg1 = game.pacman.interpolation_value_Y1;
			game.pacman.interpolation_value_X2 = (X2 - X2_previous) / nb_seg;
			Xcharg2 = game.pacman.interpolation_value_X2;
			game.pacman.interpolation_value_Y2 = (Y2 - Y2_previous) / nb_seg;
			Ycharg2 = game.pacman.interpolation_value_Y2;
		}
		break;
		// FIN CASE 2 = pacman. 


	default:
		break;
	}

	// Reintialisation des Xcharg et Ycharg à chaque passage dans la grande horloge. 

	if (game.graph.get_value(i, j) == 2) {
		Xcharg1 = game.pacman.interpolation_value_X1;
		Ycharg1 = game.pacman.interpolation_value_Y1;
		Xcharg2 = game.pacman.interpolation_value_X2;
		Ycharg2 = game.pacman.interpolation_value_Y2;

		game.pacman.rectangle_edge_X1 = X1 + int(Xcharg1 * game.horloge);
		game.pacman.rectangle_edge_Y1 = Y1 + int(Ycharg1 * game.horloge);
		game.pacman.rectangle_edge_X2 = X2 + int(Xcharg2 * game.horloge); // bug pas pris en compte
		game.pacman.rectangle_edge_Y2 = Y2 + int(Ycharg2 * game.horloge); // bug pas pris en compte -> car il faut afficher les edges "dans l'ordre"

		// D'où les permutations. 
		if (game.pacman.rectangle_edge_X1 < game.pacman.rectangle_edge_X2) { // int c; c = a; a = b; b = c; 
			int c;
			c = game.pacman.rectangle_edge_X1;
			game.pacman.rectangle_edge_X1 = game.pacman.rectangle_edge_X2;
			game.pacman.rectangle_edge_X2 = c;

		}
		if (game.pacman.rectangle_edge_Y1 < game.pacman.rectangle_edge_Y2) {
			int c;
			c = game.pacman.rectangle_edge_Y1;
			game.pacman.rectangle_edge_Y1 = game.pacman.rectangle_edge_Y2;
			game.pacman.rectangle_edge_Y2 = c;
		}
	}

}

void CPacmanV1View::afficher(int i, int j, CDC* pDC){
	int X1 = j * square;
	int Y1 = i * square;
	int X2 = (j + 1) * square;
	int Y2 = (i + 1) * square;


	if (interpolation_active) {
		interpolation(i, j); // valable uniquement pour pacman en guise d'essai. 
	}
	else {
		game.pacman.rectangle_edge_X1 = X1;
		game.pacman.rectangle_edge_Y1 = Y1;
		game.pacman.rectangle_edge_X2 = X2;
		game.pacman.rectangle_edge_Y2 = Y2;
	}

	CRect rect_move_pacman(game.pacman.rectangle_edge_X1, game.pacman.rectangle_edge_Y1, game.pacman.rectangle_edge_X2, game.pacman.rectangle_edge_Y2); // car (x,y) inversé par rapport à la matrice. Matrix: x lignes matrices; y colonnes matrices.

	
	CRect rect(X1, Y1, X2, Y2); // car (x,y) inversé par rapport à la matrice. Matrix: x lignes matrices; y colonnes matrices.
	CRect smallFoodRect(rect.left + square / 4, rect.top + square / 4, rect.left + square / 2.3, rect.top + square / 2.3);
	CRect bigFoodRect(rect.left + square / 4, rect.top + square / 4, rect.left + square / 1.4, rect.top + square / 1.4);
	

	switch (game.graph.get_value(i, j)) {
		// Cas des entités mouvantes : présence d'interpolation. 

	case 2: // pacman (rectangle jaune)
		pDC->FillSolidRect(&rect_move_pacman, RGB(255, 255, 0));
		break;
	case 4:
	case 14:
	case 24:
		if (!game.state_fantome) {
			pDC->FillSolidRect(&rect, RGB(255, 0, 0)); // phantom Blinky (rectangle rouge)
		}
		else {
			pDC->FillSolidRect(&rect, RGB(0, 255, 0));
		}
		break;
	case 5:
	case 15:
	case 25:
		if (!game.state_fantome) {
			pDC->FillSolidRect(&rect, RGB(0, 255, 255)); // phantom Inky (rectangle cyan)
		}
		else {
			pDC->FillSolidRect(&rect, RGB(0, 255, 0));
		}
		break;
	case 6:
	case 16:
	case 26:
		if (!game.state_fantome) {
			pDC->FillSolidRect(&rect, RGB(253, 108, 158)); // phantom Pinky (rectangle rose) 
		}
		else {
			pDC->FillSolidRect(&rect, RGB(0, 255, 0));
		}
		break;
	case 7:
	case 17:
	case 27:
		if (!game.state_fantome) {
			pDC->FillSolidRect(&rect, RGB(255, 69, 0)); // phantom Clyde (rectangle orange)
		}
		else {
			pDC->FillSolidRect(&rect, RGB(0, 255, 0));
		}
		break;

	// Cas des entités statiques. (Pas d'interpolation). 

	case 0: // vide (rectangle noir) 
		pDC->FillSolidRect(&rect, RGB(0, 0, 0));
		break;

	case 1: // block (rectangle bleu) 
		pDC->FillSolidRect(&rect, RGB(0, 0, 255));

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
	/*
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
		case 4:
		case 14 : 
		case 24 : 
			if (!game.state_fantome) {
				pDC->FillSolidRect(&rect, RGB(255, 0, 0)); // phantom Blinky (rectangle rouge)
			}
			else {
				pDC->FillSolidRect(&rect, RGB(0, 255, 0));
			}
			break;
		case 5:
		case 15 : 
		case 25 : 
			if (!game.state_fantome) {
				pDC->FillSolidRect(&rect, RGB(0, 255, 255)); // phantom Inky (rectangle cyan)
			}
			else {
				pDC->FillSolidRect(&rect, RGB(0, 255, 0));
			}
			break;
		case 6:
		case 16 : 
		case 26 : 
			if (!game.state_fantome) {
				pDC->FillSolidRect(&rect, RGB(253, 108, 158)); // phantom Pinky (rectangle rose) 
			}
			else {
				pDC->FillSolidRect(&rect, RGB(0, 255, 0));
			}
			break;
		case 7:
		case 17 : 
		case 27 : 
			if (!game.state_fantome) {
				pDC->FillSolidRect(&rect, RGB(255, 69, 0)); // phantom Clyde (rectangle orange)
			}
			else {
				pDC->FillSolidRect(&rect, RGB(0, 255, 0));
			}
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
		*/
}

void CPacmanV1View::OnDraw(CDC* pDC)
{
	CPacmanV1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// OnDraw n'est pas une boucle, ce sont les Timers qui sont des boucles.
	// OnDraw est une boucle d'affichage si jamais il n'y aucun timer. 
	// TODO: ajoutez ici le code de dessin pour les données natives

	//SetTimer(3, 400, NULL); // timer fantomes -> NON car sinon probleme decompte nourriture... si on met MoveFantom dedans.  
	//SetTimer(1, 250, NULL); // 375 timer pacman
	SetTimer(1, fps_timer, NULL); // 60 FPS rafraichissement. = int(1000/60) = 16 = fps_timer
	//CBoiteSettings dlg; 
	//dlg.DoModal(); 
	//SetFocus();
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
	// dlg.OnActivate(); Non! : OnActivate automatiquement appelée à chaque changement dans la fenetre.

	if (nIDEvent == 1) {
		
		if (!dlg.m_isActive) { // Si boite de dialogue fermée. 
			if (game.horloge > int(game.vitesse / fps_timer)) { // 250/16 = 15.6 => on affiche 15.6 fois par nIDEvent avant de rentrer dans le if. 

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
				game.horloge = 0;
				// Collision pacman avec un phantome.
				// re-initialisation s'il n'y plus de nourriture. sous certaines conditions 
				game.reset_food();


			}

		game.horloge += 1; // incrémentation de l'horloge du jeu à chaque passage dans timer tous les 16. (= 60 FPS)

		// Pacman mange nourriture qui lui donne des pouvoirs
		if (game.nb_high_food_ingere >= 1) {
			game.horloge_ghost += 1;
		}

		if (game.horloge_ghost > int(game.temps_vulnerable / fps_timer)) { // 8000 / 16 = 8 secondes / 16 = 500. 
			game.horloge_ghost = 0;
			game.cumul_gain = 0; // pour reinitialiser cumul_gain. (pacman mange fantomes) 
			if (game.nb_high_food_ingere == 1) {
				game.state_fantome = 0;
			}
			game.nb_high_food_ingere -= 1;
		}

		// Prison fantome 

		// Cas Blinky 
		if (game.Blinky.dead) { // if blinky mangé == dead = true 
			game.clock_prison_Blinky += 1;
		}

		if (game.clock_prison_Blinky > int(game.temps_prison / fps_timer)) {
			game.clock_prison_Blinky = 0; 
			game.Blinky.dead = false;
			// respawn en dehors de la prison. 
			game.Respawn_Entity(game.Blinky);
		}

		// Cas Inky 
		if (game.Inky.dead) {
			game.clock_prison_Inky += 1; 
		}

		if (game.clock_prison_Inky > int(game.temps_prison / fps_timer)) {
			game.clock_prison_Inky = 0; 
			game.Inky.dead = false; 
			game.Respawn_Entity(game.Inky);
		}

		// Cas Pinky
		if (game.Pinky.dead) {
			game.clock_prison_Pinky += 1; 
		}

		if (game.clock_prison_Pinky > int(game.temps_prison / fps_timer)) {
			game.clock_prison_Pinky = 0; 
			game.Pinky.dead = false; 
			game.Respawn_Entity(game.Pinky);
		}

		// Cas Clyde 
		if (game.Clyde.dead) {
			game.clock_prison_Clyde += 1; 
		}

		if (game.clock_prison_Clyde > int(game.temps_prison / fps_timer)) {
			game.clock_prison_Clyde = 0; 
			game.Clyde.dead = false; 
			game.Respawn_Entity(game.Clyde);
		}

		// Affichage de la grille 

		if (game.affich_tot) {
			for (int i = 0; i <= 20; i++) {
				for (int j = 0; j <= 18; j++) {
					afficher(i, j, pDC);
				}
			}
		}

		// Affichage du score obtenu pour l'ingestion d'un fantome (ou cumul). 

		if (game.affich_gain) { // montre le score gagné lorsque pacman mange un fantome. + ajouter ensuite cumul fantome. 
				// affich gain : score, position du texte à afficher... 

			CString gainText;
			gainText.Format(_T("%d"), game.cumul_gain);
			CFont font;
			font.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")); // Créer une fonte plus grande, en gras
			CFont* oldFont = pDC->SelectObject(&font);
			pDC->SetTextColor(RGB(255, 255, 255)); // Mettre la couleur en blanc
			pDC->TextOutW(game.pos_collision_fantome.y * square, game.pos_collision_fantome.x * square, gainText); // Attention ! Inversé dû à ma structure de donné et à l'orientation des axes MFC 
			pDC->SelectObject(oldFont); // Restaurer la fonte par défaut
			game.horloge_score_ghost += 1;
		}

		if (game.horloge_score_ghost > int(600 / fps_timer)) {
			game.horloge_score_ghost = 0;
			game.affich_gain = false;
		}

		// Affichage du score global

		CString scoreText;
		scoreText.Format(_T("SCORE   %d"), game.pacman.score); // game.pacman.score
		CFont font;
		font.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")); // Créer une fonte plus grande, en gras
		CFont* oldFont = pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(255, 255, 255)); // Mettre la couleur en blanc
		pDC->TextOutW(120, square * 21, scoreText); // pDC->TextOutW(120, square*21, scoreText); 
		pDC->SelectObject(oldFont); // Restaurer la fonte par défaut

		// Affichage des vies de pacman 

		CString livesText;
		livesText.Format(_T("LIVES   %d"), game.pacman.life_nbr); // game.pacman.life_nbr
		font.DeleteObject(); // Supprimer l'ancienne fonte
		font.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")); // Créer une fonte plus grande, en gras
		oldFont = pDC->SelectObject(&font);
		pDC->SetTextColor(RGB(255, 255, 255)); // Mettre la couleur en blanc
		pDC->TextOutW(30, square * 21, livesText);
		pDC->SelectObject(oldFont); // Restaurer la fonte par défaut



		// Cas interface admin activée. 

		if (game.admin) {
			// Affichage variable1 
			CString scoreText;
			scoreText.Format(_T("ADMIN, nb_basic_food_restantes   %d"), game.nb_basic_food_restantes); // game.pacman.score
			CFont font;
			font.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")); // Créer une fonte plus grande, en gras
			CFont* oldFont = pDC->SelectObject(&font);
			pDC->SetTextColor(RGB(255, 255, 255)); // Mettre la couleur en blanc
			pDC->TextOutW(330, square * 22, scoreText); // pDC->TextOutW(120, square*21, scoreText); 
			pDC->SelectObject(oldFont); // Restaurer la fonte par défaut

			// Affichage variable2
			CString livesText;
			livesText.Format(_T("ADMIN, nb_high_food_restantes  %d"), game.nb_high_food_restantes); // game.pacman.life_nbr
			font.DeleteObject(); // Supprimer l'ancienne fonte
			font.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")); // Créer une fonte plus grande, en gras
			oldFont = pDC->SelectObject(&font);
			pDC->SetTextColor(RGB(255, 255, 255)); // Mettre la couleur en blanc
			pDC->TextOutW(30, square * 22, livesText);
			pDC->SelectObject(oldFont); // Restaurer la fonte par défaut

			// Affichage variable 3 
			CString var3Text;
			var3Text.Format(_T("ADMIN, game.cumul_gain  %d, game.pos_collision_fantome.x  %d, game.pos_collision_fantome.y  %d, pacman pos x,y : %d %d"), game.cumul_gain, game.pos_collision_fantome.x, game.pos_collision_fantome.y, game.pacman.position.x, game.pacman.position.y); // game.pacman.life_nbr
			font.DeleteObject(); // Supprimer l'ancienne fonte
			font.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")); // Créer une fonte plus grande, en gras
			oldFont = pDC->SelectObject(&font);
			pDC->SetTextColor(RGB(255, 255, 255)); // Mettre la couleur en blanc
			pDC->TextOutW(600, square * 22, var3Text);
			pDC->SelectObject(oldFont); // Restaurer la fonte par défaut


			// Affichage de la matrice brute. METTRE COULEUR POUR LISIBILITE DE L ADMIN 

			if (game.affich_tot) {
				for (int i = 0; i <= 20; i++) {
					for (int j = 0; j <= 18; j++) {

						CString val_matrice;
						val_matrice.Format(_T(" %d"), game.graph.get_value(i, j)); // game.pacman.life_nbr
						font.DeleteObject(); // Supprimer l'ancienne fonte
						font.CreateFontW(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial")); // Créer une fonte plus grande, en gras
						oldFont = pDC->SelectObject(&font);

						if (game.graph.get_value(i, j) == 2) {
							pDC->SetTextColor(RGB(255, 255, 0));
						}
						else if (game.graph.get_value(i, j) == 4 || game.graph.get_value(i, j) == 14 || game.graph.get_value(i, j) == 24) {
							pDC->SetTextColor(RGB(255, 0, 0));
						}
						else if (game.graph.get_value(i, j) == 5 || game.graph.get_value(i, j) == 15 || game.graph.get_value(i, j) == 25) {
							pDC->SetTextColor(RGB(0, 255, 255));
						}
						else if (game.graph.get_value(i, j) == 6 || game.graph.get_value(i, j) == 16 || game.graph.get_value(i, j) == 26) {
							pDC->SetTextColor(RGB(253, 108, 153));
						}
						else if (game.graph.get_value(i, j) == 7 || game.graph.get_value(i, j) == 17 || game.graph.get_value(i, j) == 27) {
							pDC->SetTextColor(RGB(255, 69, 0));
						}
						else if (game.graph.get_value(i, j) == 1) {
							pDC->SetTextColor(RGB(0, 0, 0));
						}
						else {
							pDC->SetTextColor(RGB(255, 255, 255));
						}

						pDC->TextOutW(700 + square * j, 20 + square * i, val_matrice);
						pDC->SelectObject(oldFont); // Restaurer la fonte par défaut


					}
				}
			}
		}

	} 
	else { // Boite de dialogue active. Attendre sa fermeture. 
	
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
	
}


void CPacmanV1View::OnSettingsgame() // Boite de dialogue Settings Game 
{
	dlg.DoModal(); 
	
	game.admin = dlg.BDD_admin; // ok mais problème d'effacement... à voir. 
	interpolation_active = dlg.BDD_interpolation;
	game.affich_tot = dlg.BDD_affch;
	game.vitesse = dlg.BDD_speed_selected;
	game.pacman.life_nbr = dlg.BDD_life_pacman;
	if (game.lvl != dlg.BDD_lvl) game.check_level(); // à corriger pour le rendre effectif sur le programme. + decrease level effect. 
	game.lvl = dlg.BDD_lvl;
	
}

void CPacmanV1View::EffacerContenuALL()
{
	// Obtenez le contexte de périphérique de la vue
	CDC* pDC = GetDC();

	// Récupérer la taille de la vue
	CRect rectClient;
	GetClientRect(&rectClient);

	// Remplir la vue avec une couleur unie (par exemple, blanc)
	pDC->FillSolidRect(rectClient, RGB(255, 255, 255)); // Remplacez RGB(255, 255, 255) par la couleur de votre choix

	// Libérer le contexte de périphérique
	ReleaseDC(pDC);
}

/* 
void CVotreVue::EffacerContenuPartiel(int x, int y, int width, int height)
{
	// Obtenez le contexte de périphérique de la vue
	CDC* pDC = GetDC();

	// Remplir la zone spécifiée avec une couleur unie (par exemple, blanc)
	pDC->FillSolidRect(x, y, width, height, RGB(255, 255, 255)); // Remplacez RGB(255, 255, 255) par la couleur de votre choix

	// Libérer le contexte de périphérique
	ReleaseDC(pDC);
}
*/
void CPacmanV1View::EffacerContenuAdmin() {

}
void CPacmanV1View::EffacerContenuAffichtot() {

}