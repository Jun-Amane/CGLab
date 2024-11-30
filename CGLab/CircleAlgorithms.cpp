/*
 *
 * 文件: Algorithms/CircleAlgorithms.cpp
 * 作者: Ziyu ZHOU @ SDAU
 * 日期: 27/11/24
 *
 * 说明: 本文件实现了两种圆的生成算法：
 * 1. 中点圆生成算法 (Midpoint Circle Algorithm)
 * 2. Bresenham圆生成算法
 * 这两种算法都利用了圆的八分对称性质来提高效率
 */

#include "pch.h"
#include "CircleAlgorithms.hpp"
#include <cmath>

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/* 中点圆算法实现部分 */

/**
 * 根据圆的八分对称性质，由一个点生成其他七个对称点
 * @param points: 存储生成点的向量
 * @param centre: 圆心坐标
 * @param x: 当前点的x偏移量
 * @param y: 当前点的y偏移量
 */
void MidpointCircleAlgorithm::AddCirclePoints(std::vector<Point2D>& points,
    const Point2D& centre,
    int x, int y) {
    // 利用圆的八分对称性质，根据一个点(x,y)生成8个对称点
    points.push_back(Point2D(x + centre.x, y + centre.y));     // 第一象限
    points.push_back(Point2D(-x + centre.x, y + centre.y));    // 第二象限
    points.push_back(Point2D(-x + centre.x, -y + centre.y));   // 第三象限
    points.push_back(Point2D(x + centre.x, -y + centre.y));    // 第四象限
    points.push_back(Point2D(y + centre.x, x + centre.y));     // 第一象限对称点
    points.push_back(Point2D(-y + centre.x, x + centre.y));    // 第二象限对称点
    points.push_back(Point2D(-y + centre.x, -x + centre.y));   // 第三象限对称点
    points.push_back(Point2D(y + centre.x, -x + centre.y));    // 第四象限对称点
}

/**
 * 使用中点圆算法生成圆的所有点
 * @param centre: 圆心坐标
 * @param radius: 圆的半径
 * @return: 返回圆上所有点的坐标集合
 */
std::vector<Point2D> MidpointCircleAlgorithm::GeneratePoints(const Point2D& centre, int radius) {
    std::vector<Point2D> points;
    int x = 0;
    int y = radius;
    // 中点判别式的初值 d = 1 - R
    int d = 1 - radius;

    // 先处理第一个点，生成八个对称点
    AddCirclePoints(points, centre, x, y);

    // 使用中点算法的主循环
    // 当x < y时继续循环，确保能处理到x=y的情况（即圆的45度角位置）
    while (x < y) {
        if (d < 0) {
            // 当前点在圆内，选择E点
            d += 2 * x + 3;  // 更新判别式：d += 2(x+1) + 1
        }
        else {
            // 当前点在圆外，选择SE点
            d += 2 * (x - y) + 5;  // 更新判别式：d += 2(x-y+1) + 3
            y--;  // y坐标需要减1
        }
        x++;  // x坐标总是加1
        AddCirclePoints(points, centre, x, y);
    }

    return points;
}

/* Bresenham圆算法实现部分 */

/**
 * Bresenham圆算法的对称点生成函数
 * 原理与中点算法相同，都是利用圆的八分对称性
 */
void BresenhamCircleAlgorithm::AddCirclePoints(std::vector<Point2D>& points,
    const Point2D& center,
    int x, int y) {
    // 实现方式与中点算法相同，生成八个对称点
    points.push_back(Point2D(x + center.x, y + center.y));
    points.push_back(Point2D(-x + center.x, y + center.y));
    points.push_back(Point2D(-x + center.x, -y + center.y));
    points.push_back(Point2D(x + center.x, -y + center.y));
    points.push_back(Point2D(y + center.x, x + center.y));
    points.push_back(Point2D(-y + center.x, x + center.y));
    points.push_back(Point2D(-y + center.x, -x + center.y));
    points.push_back(Point2D(y + center.x, -x + center.y));
}

/**
 * 使用Bresenham算法生成圆的所有点
 * @param center: 圆心坐标
 * @param radius: 圆的半径
 * @return: 返回圆上所有点的坐标集合
 */
std::vector<Point2D> BresenhamCircleAlgorithm::GeneratePoints(const Point2D& center, int radius) {
    std::vector<Point2D> points;

    // 处理无效半径的情况
    if (radius <= 0) {
        return points;
    }

    int x = 0;
    int y = radius;
    // Bresenham算法的判别式初值
    int d = 1 - radius;

    // 处理第一个点
    AddCirclePoints(points, center, x, y);

    // Bresenham算法主循环
    while (x <= y) {
        if (d < 0) {
            // 选择E点
            d += 2 * x + 3;
        }
        else {
            // 选择SE点
            d += 2 * (x - y) + 5;
            y--;  // 仅在d>=0时y才减1
        }
        x++;  // x始终递增
        AddCirclePoints(points, center, x, y);
    }

    return points;
}