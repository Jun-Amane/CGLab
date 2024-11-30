
// CGLabView.cpp : implementation of the CCGLabView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CGLab.h"
#endif

#include "CGLabDoc.h"
#include "CGLabView.h"

#include "Point2D.hpp"
#include "Line.hpp"
#include "LineInputDlg.hpp"
#include "ILineAlgorithm.hpp"
#include "Circle.hpp"
#include "CircleInputDlg.hpp"
#include "ICircleAlgorithm.hpp"
#include "Ellipse.hpp"
#include "EllipseInputDlg.hpp"
#include "IEllipseAlgorithm.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGLabView

IMPLEMENT_DYNCREATE(CCGLabView, CView)

BEGIN_MESSAGE_MAP(CCGLabView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_LINE_DDA, &CCGLabView::OnLineDda)
	ON_COMMAND(ID_LINE_MIDPOINT, &CCGLabView::OnLineMidpoint)
	ON_COMMAND(ID_LINE_BRESENHAM, &CCGLabView::OnLineBresenham)
	ON_COMMAND(ID_CIRCLE_MIDPOINT, &CCGLabView::OnCircleMidpoint)
	ON_COMMAND(ID_CIRCLE_BRESENHAM, &CCGLabView::OnCircleBresenham)
	ON_COMMAND(ID_ELLIPSE_BRESENHAM, &CCGLabView::OnEllipseBresenham)
END_MESSAGE_MAP()

// CCGLabView construction/destruction

CCGLabView::CCGLabView() noexcept
{
	// TODO: add construction code here

}

CCGLabView::~CCGLabView()
{
}

BOOL CCGLabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCGLabView drawing

void CCGLabView::OnDraw(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap memBitmap;
	memDC.CreateCompatibleDC(pDC);
	memBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);

	memDC.FillSolidRect(rect, RGB(255, 255, 255));

	for (const auto& obj : m_objects) {
		obj->Draw(&memDC);
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memBitmap.DeleteObject();
}

// CCGLabView printing

BOOL CCGLabView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGLabView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGLabView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCGLabView diagnostics

#ifdef _DEBUG
void CCGLabView::AssertValid() const
{
	CView::AssertValid();
}

void CCGLabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGLabDoc* CCGLabView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGLabDoc)));
	return (CCGLabDoc*)m_pDocument;
}
#endif //_DEBUG


// CCGLabView message handlers


void CCGLabView::HandleLineAlgorithm(MyGraphics::Line::Algorithm algo)
{
	LineInputDlg dlg;
	if (dlg.DoModal() == IDOK) {
		auto line = std::make_shared<MyGraphics::Line>();
		line->SetAlgorithm(algo);
		line->SetPoints(
			MyGraphics::Point2D(dlg.m_x0, dlg.m_y0),
			MyGraphics::Point2D(dlg.m_x1, dlg.m_y1)
		);
		line->GeneratePoints();
		m_objects.push_back(line);
		Invalidate();
	}
}

void CCGLabView::HandleCircleAlgorithm(MyGraphics::Circle::Algorithm algo)
{
	CircleInputDlg dlg;
	if (dlg.DoModal() == IDOK) {
		auto circle = std::make_shared<MyGraphics::Circle>();
		circle->SetAlgorithm(algo);
		circle->SetParameters(
			MyGraphics::Point2D(dlg.m_centreX, dlg.m_centreY),
			dlg.m_radius
		);
		circle->GeneratePoints();
		m_objects.push_back(circle);
		Invalidate();
	}
}

void CCGLabView::OnLineDda()
{
	HandleLineAlgorithm(MyGraphics::Line::ALGO_DDA);
}

void CCGLabView::OnLineMidpoint()
{
	HandleLineAlgorithm(MyGraphics::Line::ALGO_MIDPOINT);
}

void CCGLabView::OnLineBresenham()
{
	HandleLineAlgorithm(MyGraphics::Line::ALGO_BRESENHAM);
}

void CCGLabView::OnCircleMidpoint()
{
	HandleCircleAlgorithm(MyGraphics::Circle::ALGO_MIDPOINT);
}


void CCGLabView::OnCircleBresenham()
{
	HandleCircleAlgorithm(MyGraphics::Circle::ALGO_BRESENHAM);
}


void CCGLabView::OnEllipseBresenham()
{
	EllipseInputDlg dlg;
	if (dlg.DoModal() == IDOK) {
		auto ellipse = std::make_shared<MyGraphics::Ellipse>();
		// auto ellipse = new MyGraphics::Ellipse();
		ellipse->SetAlgorithm(MyGraphics::Ellipse::ALGO_BRESENHAM);
		ellipse->SetParameters(
			MyGraphics::Point2D(dlg.m_centreX, dlg.m_centreY),
			dlg.m_a,
			dlg.m_b
		);
		ellipse->GeneratePoints();
		m_objects.push_back(ellipse);
		Invalidate();
	}
}
