
// PacmanV1View.h : interface de la classe CPacmanV1View
//

#pragma once
#include "Cpacman.h"
#include "GameManager.h"

class CPacmanV1View : public CView
{
protected: // création à partir de la sérialisation uniquement
	CPacmanV1View() noexcept;
	DECLARE_DYNCREATE(CPacmanV1View)

// Attributs
public:
	CPacmanV1Doc* GetDocument() const;
	GameManager game;
	int dir_pacman; 
	int square;
	//matrix previous_graph;

	void CPacmanV1View::afficher(int i, int j, CDC* pDC);

// Opérations
public:

// Substitutions
public:
	virtual void OnDraw(CDC* pDC);  // substitué pour dessiner cette vue
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implémentation
public:
	virtual ~CPacmanV1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // version Debug dans PacmanV1View.cpp
inline CPacmanV1Doc* CPacmanV1View::GetDocument() const
   { return reinterpret_cast<CPacmanV1Doc*>(m_pDocument); }
#endif

