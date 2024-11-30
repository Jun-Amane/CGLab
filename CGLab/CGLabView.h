
// CGLabView.h : interface of the CCGLabView class
//

#pragma once
#include "Point2D.hpp"
#include "GraphicsObject.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "Polygon.hpp"

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
	bool m_isDrawingPolygon;
	std::shared_ptr<MyGraphics::Polygon> m_currentPolygon;
	MyGraphics::Polygon::Algorithm m_currentPolygonAlgorithm;
	CPoint m_lastMousePos;  // 用于存储最后的鼠标位置
	void ClearScreen();
	void DrawPrompt(CDC* pDC);  // 绘制提示信息

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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPolygonX();
	afx_msg void OnSeedfilling4();
	afx_msg void OnSeedfilling8();
};

#ifndef _DEBUG  // debug version in CGLabView.cpp
inline CCGLabDoc* CCGLabView::GetDocument() const
   { return reinterpret_cast<CCGLabDoc*>(m_pDocument); }
#endif

