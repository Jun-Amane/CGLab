/*
 *
 * Models/Circle.cpp
 * Ziyu ZHOU @ SDAU
 * 27/11/24
 *
*/

#include "pch.h"
#include "Circle.hpp"
#include "CircleAlgorithms.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;


Circle::Circle()
	: GraphicsObject(OT_CIRCLE)
	, m_algorithm(ALGO_MIDPOINT)
	, m_radius(0)
	, m_circleAlgorithm(std::make_unique<MidpointCircleAlgorithm>())
{
}

void Circle::SetAlgorithm(Algorithm algo) {
	m_algorithm = algo;
	switch (algo) {
	case ALGO_MIDPOINT:
		m_circleAlgorithm = std::make_unique<MidpointCircleAlgorithm>();
		break;
	case ALGO_BRESENHAM:
		m_circleAlgorithm = std::make_unique<BresenhamCircleAlgorithm>();
		break;
	}
}

void Circle::SetParameters(const Point2D& centre, int radius) {
	m_centre = centre;
	m_radius = radius;
}

void Circle::GeneratePoints() {
	if (m_circleAlgorithm) {
		m_points = m_circleAlgorithm->GeneratePoints(m_centre, m_radius);
	}
}

void Circle::Draw(CDC* pDC) {
	for (const auto& point : m_points) {
		pDC->SetPixel(point.x, point.y, m_color);
	}
}
