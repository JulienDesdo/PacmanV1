
// PacmanV1View.h : interface de la classe CPacmanV1View
//

#pragma once


class CPacmanV1View : public CView
{
protected: // création à partir de la sérialisation uniquement
	CPacmanV1View() noexcept;
	DECLARE_DYNCREATE(CPacmanV1View)

// Attributs
public:
	CPacmanV1Doc* GetDocument() const;

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
};

#ifndef _DEBUG  // version Debug dans PacmanV1View.cpp
inline CPacmanV1Doc* CPacmanV1View::GetDocument() const
   { return reinterpret_cast<CPacmanV1Doc*>(m_pDocument); }
#endif

