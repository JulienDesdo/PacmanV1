
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

#include "matrix.h"
// CPacmanV1View

IMPLEMENT_DYNCREATE(CPacmanV1View, CView)

BEGIN_MESSAGE_MAP(CPacmanV1View, CView)
	// Commandes d'impression standard
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPacmanV1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// construction/destruction de CPacmanV1View

CPacmanV1View::CPacmanV1View() noexcept
{
	// TODO: ajoutez ici du code de construction

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

// dessin de CPacmanV1View

void CPacmanV1View::OnDraw(CDC* pDC)
{
	CPacmanV1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;



	
	matrix graph; 
	graph.initializeGraph(); 

	int square = 35;
	

	for (int i = 0; i <= 20; i++) {
		for (int j = 0; j <= 18; j++) {
			int value = graph.get_value(i,j);

			CRect rect(j * square, i * square, (j + 1) * square, (i + 1) * square);

			switch (value)
			{
			case 0 : // vide (rectangle noir) 
				pDC->FillSolidRect(&rect, RGB(0, 0, 0));
				break;

			case 1 : // block (rectangle bleu) 
				pDC->FillSolidRect(&rect, RGB(0, 0, 255));
				break;
			default:
				break;
			}
		}
	}
	
	

	// TODO: ajoutez ici le code de dessin pour les données natives
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
