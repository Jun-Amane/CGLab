/*
 *
 * Algorithms/EllipseAlgorithms.cpp
 * Ziyu ZHOU @ SDAU
 * 28/11/24
 *
*/

#include "pch.h"
#include "EllipseAlgorithms.hpp"
#include <cmath>

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

void BresenhamEllipseAlgorithm::AddPoints(std::vector<Point2D>& points,
                                         const Point2D& center, 
                                         int x, int y) {
    // 利用椭圆的对称性，一次生成四个点
    points.push_back(Point2D(center.x + x, center.y + y));
    points.push_back(Point2D(center.x - x, center.y - y));
    points.push_back(Point2D(center.x - x, center.y + y));
    points.push_back(Point2D(center.x + x, center.y - y));
}

std::vector<Point2D> BresenhamEllipseAlgorithm::GeneratePoints(
    const Point2D& center, int a, int b) {
    std::vector<Point2D> points;
    
    int x = 0;
    int y = b;
    
    // Region 1
    double d1 = b * b + a * a * (-b + 0.25);
    AddPoints(points, center, x, y);
    
    // 第一区域：当b^2(x+1) < a^2(y-0.5)时
    while (b * b * (x + 1) < a * a * (y - 0.5)) {
        if (d1 <= 0) {
            d1 += b * b * (2 * x + 3);
            x++;
        }
        else {
            d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            x++;
            y--;
        }
        AddPoints(points, center, x, y);
    }
    
    // Region 2
    // 第二区域的判别式初值
    double d2 = b * b * (x + 0.5) * (x + 0.5) + 
                a * a * (y - 1) * (y - 1) - 
                a * a * b * b;
                
    // 第二区域：当y > 0时
    while (y > 0) {
        if (d2 <= 0) {
            d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x++;
            y--;
        }
        else {
            d2 += a * a * (-2 * y + 3);
            y--;
        }
        AddPoints(points, center, x, y);
    }
    
    return points;
}

