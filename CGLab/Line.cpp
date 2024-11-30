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
	default:
		break;

	}
}

void Line::SetPoints(const Point2D& start, const Point2D& end) {
	m_startPoint = start;
	m_endPoint = end;
}

void Line::GeneratePoints() {
	if (m_lineAlgorithm) {
		m_points = m_lineAlgorithm->GeneratePoints(m_startPoint, m_endPoint);
	}
}

void Line::Draw(CDC* pDC) {
	for (const auto& point : m_points) {
		pDC->SetPixel(point.x, point.y, m_color);
	}
}
