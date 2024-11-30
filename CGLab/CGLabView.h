
// CGLabView.h : interface of the CCGLabView class
//

#pragma once
#include "Point2D.hpp"
#include "Point3D.hpp"
#include "Matrix3x3.hpp"
#include "Matrix4x4.hpp"
#include "GraphicsObject.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "Polygon.hpp"
#include "Frustum.hpp"
#include "ClipWindow.hpp"

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
	MyGraphics::ClipWindow m_clipWindow;
	bool m_isClipWindowSet;

	// 3D相关
    std::shared_ptr<MyGraphics::Frustum> m_frustum;  // 四棱台对象
    std::vector<MyGraphics::Point2D> m_projectedPoints;  // 投影点
    bool m_is3DMode;  // 是否在3D模式
	bool m_isOrthographic;  // true为三视图，false为斜二侧投影
    
    // 3D辅助函数
    MyGraphics::Matrix4x4 GetObliqueProjMatrix(double alpha = 45.0, double beta = 45.0);
    std::vector<MyGraphics::Point2D> ProjectPoints(
        const std::vector<MyGraphics::Point3D>& points3d, 
        const MyGraphics::Matrix4x4& projMatrix);
    void Draw3DObject(CDC* pDC);
	void Draw3ViewsObject(CDC* pDC);
    void DrawSingleView(CDC* pDC, const std::vector<MyGraphics::Point2D>& points, CRect rect, const CString& title);
    void ClearAll();  // 清除所有对象


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
	afx_msg void On2dtransformReflect();
	afx_msg void On2dtransformTranslate();
	afx_msg void On2dtransformRotate();
	afx_msg void On2dtransformShear();
	afx_msg void On2dtransformScale();
	afx_msg void OnClippingCohensutherland();
	afx_msg void OnClippingWeileratherton();
	afx_msg void On3dtransformOriginal();
	afx_msg void On3dtransformTranslate();
	afx_msg void On3dtransformRotate();
	afx_msg void On3dtransformShear();
	afx_msg void On3dtransformScale();
	afx_msg void On3dtransformReflect();
	afx_msg void On3dtransformView();
	afx_msg void OnFileClear();
};

#ifndef _DEBUG  // debug version in CGLabView.cpp
inline CCGLabDoc* CCGLabView::GetDocument() const
   { return reinterpret_cast<CCGLabDoc*>(m_pDocument); }
#endif

