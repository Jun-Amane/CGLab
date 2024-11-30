/*
 *
 * Models/Ellipse.cpp
 * Ziyu ZHOU @ SDAU
 * 28/11/24
 *
*/

#include "pch.h"
#include "Ellipse.hpp"
#include "EllipseAlgorithms.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;


Ellipse::Ellipse()
	: GraphicsObject(OT_ELLIPSE)
	, m_algorithm(ALGO_BRESENHAM)
	, m_a(0)
	, m_b(0)
	, m_ellipseAlgorithm(std::make_unique<BresenhamEllipseAlgorithm>())
{
}

void Ellipse::SetAlgorithm(Algorithm algo) {
	m_algorithm = algo;
	switch (algo) {
	case ALGO_BRESENHAM:
		m_ellipseAlgorithm = std::make_unique<BresenhamEllipseAlgorithm>();
		break;
	}
}

void Ellipse::SetParameters(const Point2D& center, int a, int b) {
	m_center = center;
	m_a = a;
	m_b = b;
}

void Ellipse::GeneratePoints() {
	if (m_ellipseAlgorithm) {
		m_points = m_ellipseAlgorithm->GeneratePoints(m_center, m_a, m_b);
	}
}

void Ellipse::Draw(CDC* pDC) {
	for (const auto& point : m_points) {
		pDC->SetPixel(point.x, point.y, m_color);
	}
}
