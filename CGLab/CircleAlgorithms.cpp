/*
 *
 * Algorithms/CircleAlgorithms.cpp
 * Ziyu ZHOU @ SDAU
 * 27/11/24
 *
*/

#include "pch.h"
#include "CircleAlgorithms.hpp"
#include <cmath>

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

void MidpointCircleAlgorithm::AddCirclePoints(std::vector<Point2D>& points,
	const Point2D& centre,
	int x, int y) {
	// ����Բ�İ˷ֶԳ��ԣ�һ�ο�������8����
	points.push_back(Point2D(x + centre.x, y + centre.y));
	points.push_back(Point2D(-x + centre.x, y + centre.y));
	points.push_back(Point2D(-x + centre.x, -y + centre.y));
	points.push_back(Point2D(x + centre.x, -y + centre.y));
	points.push_back(Point2D(y + centre.x, x + centre.y));
	points.push_back(Point2D(-y + centre.x, x + centre.y));
	points.push_back(Point2D(-y + centre.x, -x + centre.y));
	points.push_back(Point2D(y + centre.x, -x + centre.y));
}

std::vector<Point2D> MidpointCircleAlgorithm::GeneratePoints(const Point2D& centre, int radius) {
	std::vector<Point2D> points;

	int x = 0;
	int y = radius;
	int d = 1 - radius;  // �б�ʽ��ֵ

	// �����һ����(��Ϊ�˸��ԳƵ㶼��ͬ������ֻ�����һ��)
	AddCirclePoints(points, centre, x, y);

	// ʹ�� x <= y ��Ϊѭ��������ȷ���ܴ��� x = y �����
	while (x < y) {
		if (d < 0) {
			d += 2 * x + 3;  // d += 2(x+1) + 1
		}
		else {
			d += 2 * (x - y) + 5;  // d += 2(x-y+1) + 3
			y--;
		}
		x++;
		AddCirclePoints(points, centre, x, y);
	}

	return points;
}

void BresenhamCircleAlgorithm::AddCirclePoints(std::vector<Point2D>& points,
	const Point2D& center,
	int x, int y) {
	// ����Բ�İ˷ֶԳ���
	points.push_back(Point2D(x + center.x, y + center.y));
	points.push_back(Point2D(-x + center.x, y + center.y));
	points.push_back(Point2D(-x + center.x, -y + center.y));
	points.push_back(Point2D(x + center.x, -y + center.y));
	points.push_back(Point2D(y + center.x, x + center.y));
	points.push_back(Point2D(-y + center.x, x + center.y));
	points.push_back(Point2D(-y + center.x, -x + center.y));
	points.push_back(Point2D(y + center.x, -x + center.y));
}

std::vector<Point2D> BresenhamCircleAlgorithm::GeneratePoints(const Point2D& center, int radius) {
	std::vector<Point2D> points;

	// ������Ч�뾶
	if (radius <= 0) {
		return points;
	}

	int x = 0;
	int y = radius;
	int d = 1 - radius;  // Bresenham�б�ʽ��ֵ

	// ��ӵ�һ����
	AddCirclePoints(points, center, x, y);

	// Bresenham�㷨��ѭ����ʹ�� x <= y ��Ϊ����
	while (x <= y) {
		if (d < 0) {
			d += 2 * x + 3;  // d = d + 2x + 3
		}
		else {
			d += 2 * (x - y) + 5;  // d = d + 2(x-y) + 5
			y--;  // yֻ��d>=0ʱ�ݼ�
		}
		x++;  // x���ǵ���
		AddCirclePoints(points, center, x, y);
	}

	return points;
}
