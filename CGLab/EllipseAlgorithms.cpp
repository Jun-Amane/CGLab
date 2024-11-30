/*
*
* 文件名: Algorithms/EllipseAlgorithms.cpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 28/11/24
*
* 说明: 本文件实现了 Bresenham 椭圆生成算法
* 该算法将椭圆分为两个区域进行绘制,利用椭圆的四分对称性质
*/

#include "pch.h"
#include "EllipseAlgorithms.hpp"
#include <cmath>

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* 利用椭圆的四分对称性质生成四个对称点
* @param points: 存储所有椭圆点的向量
* @param center: 椭圆中心坐标
* @param x: 当前点的x偏移量
* @param y: 当前点的y偏移量
*/
void BresenhamEllipseAlgorithm::AddPoints(std::vector<Point2D>& points,
    const Point2D& center,
    int x, int y) {
    // 利用椭圆的四分对称性,一次生成四个对称点
    points.push_back(Point2D(center.x + x, center.y + y));  // 第一象限
    points.push_back(Point2D(center.x - x, center.y - y));  // 第三象限
    points.push_back(Point2D(center.x - x, center.y + y));  // 第二象限
    points.push_back(Point2D(center.x + x, center.y - y));  // 第四象限
}

/**
* 使用Bresenham算法生成椭圆的所有点
* @param center: 椭圆中心坐标
* @param a: 椭圆长轴长度
* @param b: 椭圆短轴长度
* @return: 返回椭圆上所有点的坐标集合
*/
std::vector<Point2D> BresenhamEllipseAlgorithm::GeneratePoints(
    const Point2D& center, int a, int b) {
    std::vector<Point2D> points;

    int x = 0;
    int y = b;

    // 区域1 - 从y轴开始绘制到斜率为-1的点
    // 判别式初值
    double d1 = b * b + a * a * (-b + 0.25);
    AddPoints(points, center, x, y);

    // 第一区域的处理
    // 当b^2(x+1) < a^2(y-0.5)时,在第一区域
    while (b * b * (x + 1) < a * a * (y - 0.5)) {
        if (d1 <= 0) {
            // 选择E点
            d1 += b * b * (2 * x + 3);
            x++;
        }
        else {
            // 选择SE点
            d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
            x++;
            y--;
        }
        AddPoints(points, center, x, y);
    }

    // 区域2 - 从斜率为-1的点绘制到x轴
    // 第二区域判别式初值
    double d2 = b * b * (x + 0.5) * (x + 0.5) +
        a * a * (y - 1) * (y - 1) -
        a * a * b * b;

    // 第二区域的处理：当y > 0时继续
    while (y > 0) {
        if (d2 <= 0) {
            // 选择SE点
            d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
            x++;
            y--;
        }
        else {
            // 选择S点
            d2 += a * a * (-2 * y + 3);
            y--;
        }
        AddPoints(points, center, x, y);
    }

    return points;
}
