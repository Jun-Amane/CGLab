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
	// 由于圆的八分对称性，一次可以生成8个点
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
	int d = 1 - radius;  // 判别式初值

	// 处理第一个点(因为八个对称点都相同，所以只需添加一次)
	AddCirclePoints(points, centre, x, y);

	// 使用 x <= y 作为循环条件，确保能处理 x = y 的情况
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
	// 利用圆的八分对称性
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

	// 处理无效半径
	if (radius <= 0) {
		return points;
	}

	int x = 0;
	int y = radius;
	int d = 1 - radius;  // Bresenham判别式初值

	// 添加第一个点
	AddCirclePoints(points, center, x, y);

	// Bresenham算法主循环，使用 x <= y 作为条件
	while (x <= y) {
		if (d < 0) {
			d += 2 * x + 3;  // d = d + 2x + 3
		}
		else {
			d += 2 * (x - y) + 5;  // d = d + 2(x-y) + 5
			y--;  // y只在d>=0时递减
		}
		x++;  // x总是递增
		AddCirclePoints(points, center, x, y);
	}

	return points;
}
