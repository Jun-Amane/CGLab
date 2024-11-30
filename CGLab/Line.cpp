/*
 *
 * Models/Line.cpp
 * Ziyu ZHOU @ SDAU
 * 26/11/24
 *
*/

#include "pch.h"
#include "Line.hpp"
#include "LineAlgorithms.hpp"
#include "LineClipAlgorithms.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;


Line::Line()
	: GraphicsObject(OT_LINE)
	, m_algorithm(ALGO_DDA)
	, m_lineAlgorithm(std::make_unique<DDALineAlgorithm>())
{
}

void Line::SetAlgorithm(Algorithm algo) {
	m_algorithm = algo;
	switch (algo) {
	case ALGO_DDA:
		m_lineAlgorithm = std::make_unique<DDALineAlgorithm>();
		break;
	case ALGO_MIDPOINT:
		m_lineAlgorithm = std::make_unique<MidpointLineAlgorithm>();
		break;
	case ALGO_BRESENHAM:
		m_lineAlgorithm = std::make_unique<BresenhamLineAlgorithm>();
    case ALGO_COHEN_SUTHERLAND:
        m_lineAlgorithm = std::make_unique<DDALineAlgorithm>();  // ʹ��DDA�㷨����
        m_clipAlgorithm = std::make_unique<CohenSutherlandAlgorithm>();
        break;
	}
}

void Line::SetPoints(const Point2D& start, const Point2D& end) {
	m_startPoint = start;
	m_endPoint = end;
}

void Line::GeneratePoints() {
    if (m_algorithm == ALGO_COHEN_SUTHERLAND && m_clipAlgorithm) {
        // ����ü�ǰ�ĵ�
        m_clippedStart = m_startPoint;
        m_clippedEnd = m_endPoint;
        
        // ���вü�
        m_isClipped = m_clipAlgorithm->ClipLine(m_clippedStart, m_clippedEnd, m_clipWindow);
        
        if (m_isClipped) {
            // ʹ�òü���ĵ�����ֱ��
            m_points = m_lineAlgorithm->GeneratePoints(m_clippedStart, m_clippedEnd);
        }
        else {
            m_points.clear();
        }
    }
    else if (m_lineAlgorithm) {
        m_points = m_lineAlgorithm->GeneratePoints(m_startPoint, m_endPoint);
    }
}

void Line::Draw(CDC* pDC) {
    // �����Cohen-Sutherland�㷨���Ȼ��Ʋü�����
    if (m_algorithm == ALGO_COHEN_SUTHERLAND) {
        m_clipWindow.Draw(pDC);
        
        // ����ԭʼֱ�ߣ����ߣ�
        CPen dashPen(PS_DASH, 1, RGB(128, 128, 128));
        CPen* pOldPen = pDC->SelectObject(&dashPen);
        pDC->MoveTo(m_startPoint.x, m_startPoint.y);
        pDC->LineTo(m_endPoint.x, m_endPoint.y);
        pDC->SelectObject(pOldPen);
    }
    
    // ����ʵ�ʵĵ㣨ʵ�ߣ�
    for (const auto& point : m_points) {
        pDC->SetPixel(point.x, point.y, m_color);
    }
}