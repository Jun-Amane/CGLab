
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
	ON_COMMAND(ID_CLIPPING_WEILERATHERTON, &CCGLabView::OnClippingWeileratherton)
	ON_COMMAND(ID_3DTRANSFORM_ORIGINAL, &CCGLabView::On3dtransformOriginal)
	ON_COMMAND(ID_3DTRANSFORM_TRANSLATE, &CCGLabView::On3dtransformTranslate)
	ON_COMMAND(ID_3DTRANSFORM_ROTATE, &CCGLabView::On3dtransformRotate)
	ON_COMMAND(ID_3DTRANSFORM_SHEAR, &CCGLabView::On3dtransformShear)
	ON_COMMAND(ID_3DTRANSFORM_SCALE, &CCGLabView::On3dtransformScale)
	ON_COMMAND(ID_3DTRANSFORM_REFLECT, &CCGLabView::On3dtransformReflect)
	ON_COMMAND(ID_3DTRANSFORM_3, &CCGLabView::On3dtransformView)
	ON_COMMAND(ID_FILE_CLEAR, &CCGLabView::OnFileClear)
END_MESSAGE_MAP()

// CCGLabView construction/destruction

CCGLabView::CCGLabView() noexcept
    : m_isDrawingPolygon(false)
    , m_isClipWindowSet(false)
    , m_is3DMode(false)
    , m_isOrthographic(false)  // Ĭ��Ϊб����ͶӰ
{
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
	if (m_is3DMode) {
		// 3Dģʽ
		if (m_isOrthographic) {
			Draw3ViewsObject(&memDC);	// ��������ͼ
		}
		else {
			Draw3DObject(&memDC);  // ����б����ͶӰ
		}
	}
	else
	{	// 2Dģʽ
		if (m_isClipWindowSet && m_objects.empty()) {
			m_clipWindow.Draw(&memDC);
		}

		// ������������ɵ�ͼ��
		for (const auto& obj : m_objects) {
			obj->Draw(&memDC);
		}

		// �������ڹ����Ķ����
		if (m_isDrawingPolygon && m_currentPolygon) {
			m_currentPolygon->Draw(&memDC);

			// ����Ԥ���ߣ�����Ч����
			if (!m_currentPolygon->IsClosed() && !m_currentPolygon->GetVertices().empty()) {
				CPen dashPen(PS_DASH, 1, RGB(128, 128, 128));
				CPen* pOldPen = memDC.SelectObject(&dashPen);

				const auto& lastVertex = m_currentPolygon->GetVertices().back();
				memDC.MoveTo(lastVertex.x, lastVertex.y);
				memDC.LineTo(m_lastMousePos.x, m_lastMousePos.y);

				memDC.SelectObject(pOldPen);
			}
		}

		// ������ʾ��Ϣ
		DrawPrompt(&memDC);
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	memBitmap.DeleteObject();
}

void CCGLabView::ClearAll()
{
	m_objects.clear();
	m_isDrawingPolygon = false;
	m_currentPolygon = nullptr;
	m_isClipWindowSet = false;
	m_frustum = nullptr;
	m_projectedPoints.clear();
	m_is3DMode = false;
}

Matrix4x4 CCGLabView::GetObliqueProjMatrix(double alpha, double beta)
{
	Matrix4x4 matrix;
	double rad_alpha = alpha * M_PI / 180.0;
	double rad_beta = beta * M_PI / 180.0;

	matrix.Set(0, 0, 1.0);
	matrix.Set(1, 1, 1.0);
	matrix.Set(0, 2, cos(rad_alpha));
	matrix.Set(1, 2, sin(rad_beta));
	matrix.Set(2, 2, 0.0);

	return matrix;
}

std::vector<MyGraphics::Point2D> CCGLabView::ProjectPoints(
	const std::vector<MyGraphics::Point3D>& points3d,
	const Matrix4x4& projMatrix)
{
	std::vector<MyGraphics::Point2D> points2d;
	for (const auto& p : points3d) {
		Point3D projected = TransformPoint(p, projMatrix);
		points2d.push_back(MyGraphics::Point2D(projected.x, projected.y));
	}
	return points2d;
}

void CCGLabView::Draw3DObject(CDC* pDC)
{
	if (!m_frustum || m_projectedPoints.empty()) return;

	CRect rect;
	GetClientRect(&rect);

	// �������ź�ƫ������Ӧ����
	double scaleX = rect.Width() / 300.0;
	double scaleY = rect.Height() / 300.0;
	double scale = min(scaleX, scaleY);

	int offsetX = rect.Width() / 2;
	int offsetY = rect.Height() / 2;

	// ���Ʊ�
	const auto& edges = m_frustum->GetEdges();
	for (const auto& edge : edges) {
		const auto& p1 = m_projectedPoints[edge.first];
		const auto& p2 = m_projectedPoints[edge.second];

		int x1 = offsetX + static_cast<int>(p1.x * scale);
		int y1 = offsetY - static_cast<int>(p1.y * scale);
		int x2 = offsetX + static_cast<int>(p2.x * scale);
		int y2 = offsetY - static_cast<int>(p2.y * scale);

		pDC->MoveTo(x1, y1);
		pDC->LineTo(x2, y2);
	}
}

void CCGLabView::ClearScreen() {
	this->ClearAll();
	Invalidate();      // ǿ���ػ�
}

void CCGLabView::DrawPrompt(CDC* pDC) {
	if (!m_isDrawingPolygon || !m_currentPolygon) return;

	CString prompt;
	if (!m_currentPolygon->IsClosed()) {
		prompt = _T("��������Ӷ��㣬�Ҽ���ɻ���");
	}
	else if (m_currentPolygonAlgorithm != MyGraphics::Polygon::ALGO_SCANLINE
		&& !m_currentPolygon->HasSeed()) {
		prompt = _T("����������ڲ�ѡ�����ӵ�");
	}

	if (!prompt.IsEmpty()) {
		// �����ı���ʽ
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));

		// ����Ļ�Ϸ���ʾ��ʾ
		CRect rect;
		GetClientRect(&rect);
		pDC->TextOut(10, 10, prompt);
	}
}

void CCGLabView::Draw3ViewsObject(CDC* pDC) {
    if (!m_frustum) return;

    CRect clientRect;
    GetClientRect(&clientRect);

    // ����������ͼ����
    int padding = 20;  // ��ͼ��ļ�϶
    int areaWidth = (clientRect.Width() - 3 * padding) / 2;
    int areaHeight = (clientRect.Height() - 3 * padding) / 2;

    CRect frontRect(padding, padding, padding + areaWidth, padding + areaHeight);  // ����ͼ
    CRect topRect(padding * 2 + areaWidth, padding, padding * 2 + areaWidth * 2, padding + areaHeight);  // ����ͼ
    CRect sideRect(padding, padding * 2 + areaHeight, padding + areaWidth, padding * 2 + areaHeight * 2);  // ����ͼ

    // ��ȡ����ͼͶӰ��
    std::vector<Point2D> frontView, topView, sideView;
    m_frustum->GetProjections(frontView, topView, sideView);

    // ����������ͼ
    DrawSingleView(pDC, frontView, frontRect, _T("����ͼ"));
    DrawSingleView(pDC, topView, topRect, _T("����ͼ"));
    DrawSingleView(pDC, sideView, sideRect, _T("����ͼ"));
}

void CCGLabView::DrawSingleView(CDC* pDC, const std::vector<Point2D>& points, CRect rect, const CString& title) {
    // ������ͼ�߿�
    pDC->Rectangle(rect);

    // ���Ʊ���
    CRect titleRect = rect;
    titleRect.bottom = titleRect.top + 20;
    pDC->DrawText(title, titleRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // ������ͼ����
    rect.top += 20;

    // �������ű���
    double scaleX = (rect.Width() - 40) / 200.0;  // Ԥ���߾�
    double scaleY = (rect.Height() - 40) / 200.0;
    double scale = min(scaleX, scaleY);

    // �������ĵ�
    int centerX = rect.left + rect.Width() / 2;
    int centerY = rect.top + rect.Height() / 2;

    // ����������
    CPen axisPen(PS_DOT, 1, RGB(128, 128, 128));
    CPen* pOldPen = pDC->SelectObject(&axisPen);
    pDC->MoveTo(rect.left + 10, centerY);
    pDC->LineTo(rect.right - 10, centerY);
    pDC->MoveTo(centerX, rect.top + 10);
    pDC->LineTo(centerX, rect.bottom - 10);

    // ����ͼ�α�
    CPen objectPen(PS_SOLID, 2, RGB(0, 0, 0));
    pDC->SelectObject(&objectPen);

    const auto& edges = m_frustum->GetEdges();
    for (const auto& edge : edges) {
        const Point2D& p1 = points[edge.first];
        const Point2D& p2 = points[edge.second];

        int x1 = centerX + static_cast<int>(p1.x * scale);
        int y1 = centerY - static_cast<int>(p1.y * scale);
        int x2 = centerX + static_cast<int>(p2.x * scale);
        int y2 = centerY - static_cast<int>(p2.y * scale);

        pDC->MoveTo(x1, y1);
        pDC->LineTo(x2, y2);
    }

    pDC->SelectObject(pOldPen);
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

void CCGLabView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_isDrawingPolygon && m_currentPolygon) {
		if (!m_currentPolygon->IsClosed()) {
			m_currentPolygon->AddVertex(MyGraphics::Point2D(point.x, point.y));
			m_lastMousePos = point;  // �����������λ��
			Invalidate();
		}
		else if (m_currentPolygonAlgorithm != MyGraphics::Polygon::ALGO_SCANLINE) {
			// �������������㷨�Ҷ�����ѱպϣ����������ӵ�
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

			if (m_currentPolygonAlgorithm == MyGraphics::Polygon::ALGO_WEILER_ATHERTON ||
				m_currentPolygonAlgorithm == MyGraphics::Polygon::ALGO_SCANLINE) {
				m_currentPolygon->GeneratePoints();
			}

			m_objects.push_back(m_currentPolygon);
			m_isDrawingPolygon = false;
			Invalidate();
		}
	}

	CView::OnRButtonDown(nFlags, point);
}


void CCGLabView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_isDrawingPolygon && m_currentPolygon && !m_currentPolygon->IsClosed()) {
		m_lastMousePos = point;
		Invalidate();  // �ػ��Ը���Ԥ����
	}

	CView::OnMouseMove(nFlags, point);
}


void CCGLabView::OnPolygonX()
{
	ClearScreen();  // ����
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
			case 0: // x��Գ�
				matrix = MyGraphics::Transform::ReflectX();
				break;
			case 1: // y��Գ�
				matrix = MyGraphics::Transform::ReflectY();
				break;
			case 2: // ֱ�߶Գ�
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
	// �Ȼ���ͼ�Σ��ٽ��б任
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
	}
}


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
	// �������òü�����
	ClipWindowDlg clipDlg;
	if (clipDlg.DoModal() == IDOK) {
		m_clipWindow.SetBounds(
			clipDlg.m_xmin,
			clipDlg.m_ymin,
			clipDlg.m_xmax,
			clipDlg.m_ymax
		);
		m_isClipWindowSet = true;

		// Ȼ������ֱ��
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


void CCGLabView::OnClippingWeileratherton()
{
	// �������òü�����
	ClipWindowDlg clipDlg;
	if (clipDlg.DoModal() == IDOK) {
		ClearScreen();  // �����ǰ��Ļ

		// �����µĶ���ζ���
		m_isDrawingPolygon = true;
		m_currentPolygon = std::make_shared<MyGraphics::Polygon>();
		m_currentPolygon->SetAlgorithm(MyGraphics::Polygon::ALGO_WEILER_ATHERTON);

		// ���òü�����
		MyGraphics::ClipWindow clipWindow(
			clipDlg.m_xmin,
			clipDlg.m_ymin,
			clipDlg.m_xmax,
			clipDlg.m_ymax
		);
		m_currentPolygon->SetClipWindow(clipWindow);
		m_currentPolygonAlgorithm = MyGraphics::Polygon::ALGO_WEILER_ATHERTON;

		// ��ʾ��ʾ��Ϣ
		MessageBox(_T("������������Ӷ���ζ��㣬�Ҽ�����������ơ�"),
			_T("������ʾ"), MB_ICONINFORMATION);
	}
}


void CCGLabView::On3dtransformOriginal()
{
	ClearAll();
	m_is3DMode = true;
	m_isOrthographic = false;  // ʹ��б����ͶӰ
	m_frustum = std::make_shared<MyGraphics::Frustum>(100, 60, 120);
	m_projectedPoints = ProjectPoints(m_frustum->GetVertices(), GetObliqueProjMatrix());
	Invalidate();
}


void CCGLabView::On3dtransformTranslate()
{
	if (!m_frustum || !m_is3DMode) {
        MessageBox(_T("���ȵ��Original��ť��ʾԭʼͼ��"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
        return;
    }
    
    Matrix4x4 trans = Transform3D::Translate(30, -20, 0);
    m_frustum->Transform(trans);
    m_projectedPoints = ProjectPoints(m_frustum->GetVertices(), GetObliqueProjMatrix());
    Invalidate();
}


void CCGLabView::On3dtransformRotate()
{
	if (!m_frustum || !m_is3DMode) {
        MessageBox(_T("���ȵ��Original��ť��ʾԭʼͼ��"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
        return;
    }
    
    Matrix4x4 rot = Transform3D::RotateY(45.0);
    m_frustum->Transform(rot);
    m_projectedPoints = ProjectPoints(m_frustum->GetVertices(), GetObliqueProjMatrix());
    Invalidate();
}


void CCGLabView::On3dtransformShear()
{
	if (!m_frustum || !m_is3DMode) {
		MessageBox(_T("���ȵ��Original��ť��ʾԭʼͼ��"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	Matrix4x4 shear;
	shear.Set(0, 1, 0.3);
	m_frustum->Transform(shear);
	m_projectedPoints = ProjectPoints(m_frustum->GetVertices(), GetObliqueProjMatrix());
	Invalidate();
}


void CCGLabView::On3dtransformScale()
{
	if (!m_frustum || !m_is3DMode) {
        MessageBox(_T("���ȵ��Original��ť��ʾԭʼͼ��"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
        return;
    }
    
    Matrix4x4 scale = Transform3D::Scale(1.5, 1.5, 1.5);
    m_frustum->Transform(scale);
    m_projectedPoints = ProjectPoints(m_frustum->GetVertices(), GetObliqueProjMatrix());
    Invalidate();
}


void CCGLabView::On3dtransformReflect()
{
	if (!m_frustum || !m_is3DMode) {
		MessageBox(_T("���ȵ��Original��ť��ʾԭʼͼ��"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return;
	}

	Matrix4x4 reflect;
	reflect.Set(2, 2, -1);
	m_frustum->Transform(reflect);
	m_projectedPoints = ProjectPoints(m_frustum->GetVertices(), GetObliqueProjMatrix());
	Invalidate();
}


void CCGLabView::On3dtransformView()
{
	if (!m_frustum || !m_is3DMode) {
		MessageBox(_T("���ȵ��Original��ť��ʾԭʼͼ��"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return;
	}
	m_isOrthographic = true;
	Invalidate();
}

void CCGLabView::OnFileClear()
{
	ClearScreen();
}
