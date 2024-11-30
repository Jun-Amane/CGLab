
// CGLabView.h : interface of the CCGLabView class
//

#pragma once
#include "Point2D.hpp"
#include "GraphicsObject.hpp"
#include "Line.hpp"
#include "Circle.hpp"

class CCGLabView : public CView
{
protected: // create from serialization only
	CCGLabView() noexcept;
	DECLARE_DYNCREATE(CCGLabView)

// Attributes
public:
	CCGLabDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCGLabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


// My code
protected:
	std::vector<std::shared_ptr<MyGraphics::GraphicsObject>> m_objects;
	void HandleLineAlgorithm(MyGraphics::Line::Algorithm algo);
	void HandleCircleAlgorithm(MyGraphics::Circle::Algorithm algoh);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLineDda();
	afx_msg void OnLineMidpoint();
	afx_msg void OnLineBresenham();
	afx_msg void OnCircleMidpoint();
	afx_msg void OnCircleBresenham();
	afx_msg void OnEllipseBresenham();
};

#ifndef _DEBUG  // debug version in CGLabView.cpp
inline CCGLabDoc* CCGLabView::GetDocument() const
   { return reinterpret_cast<CCGLabDoc*>(m_pDocument); }
#endif

