
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
#include "Matrix3x3.hpp"
#include "Line.hpp"
#include "LineInputDlg.hpp"
#include "ILineAlgorithm.hpp"
#include "Circle.hpp"
#include "CircleInputDlg.hpp"
#include "ICircleAlgorithm.hpp"
#include "Ellipse.hpp"
#include "EllipseInputDlg.hpp"
#include "IEllipseAlgorithm.hpp"
#include "Polygon.hpp"
#include "Transform2D.hpp"
#include "TransformDlg.hpp"
#include "IPolygonAlgorithm.hpp"
#include "ILineClipAlgorithm.hpp"
#include "LineClipAlgorithms.hpp"
#include "ClipWindow.hpp"
#include "ClipWindowDlg.hpp"

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
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_POLYGON_X, &CCGLabView::OnPolygonX)
	ON_COMMAND(ID_SEEDFILLING_4, &CCGLabView::OnSeedfilling4)
	ON_COMMAND(ID_SEEDFILLING_8, &CCGLabView::OnSeedfilling8)
	ON_COMMAND(ID_2DTRANSFORM_REFLECT, &CCGLabView::On2dtransformReflect)
	ON_COMMAND(ID_2DTRANSFORM_TRANSLATE, &CCGLabView::On2dtransformTranslate)
	ON_COMMAND(ID_2DTRANSFORM_ROTATE, &CCGLabView::On2dtransformRotate)
	ON_COMMAND(ID_2DTRANSFORM_SHEAR, &CCGLabView::On2dtransformShear)
	ON_COMMAND(ID_2DTRANSFORM_SCALE, &CCGLabView::On2dtransformScale)
	ON_COMMAND(ID_CLIPPING_COHENSUTHERLAND, &CCGLabView::OnClippingCohensutherland)
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

	if (m_isClipWindowSet && m_objects.empty()) {
		m_clipWindow.Draw(&memDC);
	}	

    // 绘制所有已完成的图形
    for (const auto& obj : m_objects) {
        obj->Draw(&memDC);
    }

    // 绘制正在构建的多边形
    if (m_isDrawingPolygon && m_currentPolygon) {
        m_currentPolygon->Draw(&memDC);

        // 绘制预览线（虚线效果）
        if (!m_currentPolygon->IsClosed() && !m_currentPolygon->GetVertices().empty()) {
            CPen dashPen(PS_DASH, 1, RGB(128, 128, 128));
            CPen* pOldPen = memDC.SelectObject(&dashPen);
            
            const auto& lastVertex = m_currentPolygon->GetVertices().back();
            memDC.MoveTo(lastVertex.x, lastVertex.y);
            memDC.LineTo(m_lastMousePos.x, m_lastMousePos.y);
            
            memDC.SelectObject(pOldPen);
        }
    }

    // 绘制提示信息
    DrawPrompt(&memDC);

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

void CCGLabView::ClearScreen() {
	m_objects.clear();  // 清除所有图形对象
	Invalidate();      // 强制重绘
}

void CCGLabView::DrawPrompt(CDC* pDC) {
	if (!m_isDrawingPolygon || !m_currentPolygon) return;

	CString prompt;
	if (!m_currentPolygon->IsClosed()) {
		prompt = _T("左键点击添加顶点，右键完成绘制");
	}
	else if (m_currentPolygonAlgorithm != MyGraphics::Polygon::ALGO_SCANLINE
		&& !m_currentPolygon->HasSeed()) {
		prompt = _T("请点击多边形内部选择种子点");
	}

	if (!prompt.IsEmpty()) {
		// 设置文本样式
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));

		// 在屏幕上方显示提示
		CRect rect;
		GetClientRect(&rect);
		pDC->TextOut(10, 10, prompt);
	}
}

void CCGLabView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_isDrawingPolygon && m_currentPolygon) {
        if (!m_currentPolygon->IsClosed()) {
            m_currentPolygon->AddVertex(MyGraphics::Point2D(point.x, point.y));
            m_lastMousePos = point;  // 更新最后的鼠标位置
            Invalidate();
        }
        else if (m_currentPolygonAlgorithm != MyGraphics::Polygon::ALGO_SCANLINE) {
            // 如果是种子填充算法且多边形已闭合，则设置种子点
            m_currentPolygon->SetSeed(MyGraphics::Point2D(point.x, point.y));
            m_currentPolygon->GeneratePoints();
            Invalidate();
        }
    }	CView::OnLButtonDown(nFlags, point);
}


void CCGLabView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_isDrawingPolygon && m_currentPolygon) {
		if (!m_currentPolygon->IsClosed()) {
			m_currentPolygon->Close();
			if (m_currentPolygonAlgorithm == MyGraphics::Polygon::ALGO_SCANLINE) {
				m_currentPolygon->GeneratePoints();
			}
			m_objects.push_back(m_currentPolygon);
			Invalidate();
		}
	}


	CView::OnRButtonDown(nFlags, point);
}


void CCGLabView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_isDrawingPolygon && m_currentPolygon && !m_currentPolygon->IsClosed()) {
		m_lastMousePos = point;
		Invalidate();  // 重绘以更新预览线
	}

	CView::OnMouseMove(nFlags, point);
}


void CCGLabView::OnPolygonX()
{
	ClearScreen();  // 清屏
	m_isDrawingPolygon = true;
	m_currentPolygon = std::make_shared<MyGraphics::Polygon>();
	m_currentPolygon->SetAlgorithm(MyGraphics::Polygon::ALGO_SCANLINE);
	m_currentPolygonAlgorithm = MyGraphics::Polygon::ALGO_SCANLINE;
}

void CCGLabView::OnSeedfilling4()
{
	ClearScreen();
	m_isDrawingPolygon = true;
	m_currentPolygon = std::make_shared<MyGraphics::Polygon>();
	m_currentPolygon->SetAlgorithm(MyGraphics::Polygon::ALGO_SEEDFILL_4);
	m_currentPolygonAlgorithm = MyGraphics::Polygon::ALGO_SEEDFILL_4;
}

void CCGLabView::OnSeedfilling8()
{
	ClearScreen();
	m_isDrawingPolygon = true;
	m_currentPolygon = std::make_shared<MyGraphics::Polygon>();
	m_currentPolygon->SetAlgorithm(MyGraphics::Polygon::ALGO_SEEDFILL_8);
	m_currentPolygonAlgorithm = MyGraphics::Polygon::ALGO_SEEDFILL_8;
}


void CCGLabView::On2dtransformReflect()
{
    if (m_objects.empty()) return;
    
    ReflectDlg dlg;
    if (dlg.DoModal() == IDOK) {
        auto polygon = std::dynamic_pointer_cast<MyGraphics::Polygon>(m_objects.back());
        if (polygon) {
            MyGraphics::Matrix3x3 matrix;
            switch (dlg.m_type) {
                case 0: // x轴对称
                    matrix = MyGraphics::Transform::ReflectX();
                    break;
                case 1: // y轴对称
                    matrix = MyGraphics::Transform::ReflectY();
                    break;
                case 2: // 直线对称
                    matrix = MyGraphics::Transform::Reflect(dlg.m_k, dlg.m_b);
                    break;
            }
            polygon->Transform(matrix);
            Invalidate();
        }
    }
}


void CCGLabView::On2dtransformTranslate()
{
	// 先绘制图形，再进行变换
	if (m_objects.empty()) return;
    
    TranslateDlg dlg;
    if (dlg.DoModal() == IDOK) {
        auto polygon = std::dynamic_pointer_cast<MyGraphics::Polygon>(m_objects.back());
        if (polygon) {
            auto matrix = MyGraphics::Transform::Translate(dlg.m_dx, dlg.m_dy);
            polygon->Transform(matrix);
            Invalidate();
        }
    }
}


void CCGLabView::On2dtransformRotate()
{
	if (m_objects.empty()) return;
    
    RotateDlg dlg;
    if (dlg.DoModal() == IDOK) {
        auto polygon = std::dynamic_pointer_cast<MyGraphics::Polygon>(m_objects.back());
        if (polygon) {
            auto matrix = MyGraphics::Transform::Rotate(
                dlg.m_angle, 
                MyGraphics::Point2D(dlg.m_cx, dlg.m_cy)
            );
            polygon->Transform(matrix);
            Invalidate();
        }
    }}


void CCGLabView::On2dtransformShear()
{
  if (m_objects.empty()) return;
    
    ShearDlg dlg;
    if (dlg.DoModal() == IDOK) {
        auto polygon = std::dynamic_pointer_cast<MyGraphics::Polygon>(m_objects.back());
        if (polygon) {
            auto matrix = MyGraphics::Transform::Shear(dlg.m_shx, dlg.m_shy);
            polygon->Transform(matrix);
            Invalidate();
        }
    }
}


void CCGLabView::On2dtransformScale()
{
	if (m_objects.empty()) return;

	ScaleDlg dlg;
	if (dlg.DoModal() == IDOK) {
		auto polygon = std::dynamic_pointer_cast<MyGraphics::Polygon>(m_objects.back());
		if (polygon) {
			auto matrix = MyGraphics::Transform::Scale(
				dlg.m_sx, dlg.m_sy,
				MyGraphics::Point2D(dlg.m_cx, dlg.m_cy)
			);
			polygon->Transform(matrix);
			Invalidate();
		}
	}
}


void CCGLabView::OnClippingCohensutherland()
{
	// 首先设置裁剪窗口
    ClipWindowDlg clipDlg;
    if (clipDlg.DoModal() == IDOK) {
        m_clipWindow.SetBounds(
            clipDlg.m_xmin, 
            clipDlg.m_ymin, 
            clipDlg.m_xmax, 
            clipDlg.m_ymax
        );
        m_isClipWindowSet = true;

        // 然后设置直线
        LineInputDlg lineDlg;
        if (lineDlg.DoModal() == IDOK) {
            auto line = std::make_shared<MyGraphics::Line>();
            line->SetAlgorithm(MyGraphics::Line::ALGO_COHEN_SUTHERLAND);
            line->SetPoints(
                MyGraphics::Point2D(lineDlg.m_x0, lineDlg.m_y0),
                MyGraphics::Point2D(lineDlg.m_x1, lineDlg.m_y1)
            );
            line->SetClipWindow(m_clipWindow);
            line->GeneratePoints();
            m_objects.push_back(line);
            Invalidate();
        }
    } 
}
