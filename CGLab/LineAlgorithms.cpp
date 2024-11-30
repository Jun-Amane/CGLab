/*
*
* 文件名: Algorithms/LineAlgorithms.cpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 26/11/24
*
* 说明: 本文件实现了三种经典的直线生成算法:
* 1. DDA算法 (数值微分法)
* 2. 中点直线算法
* 3. Bresenham直线算法
*/

#include "pch.h"
#include "LineAlgorithms.hpp"
#include <cmath>

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* DDA直线生成算法实现
* 基于数值微分的思想,通过浮点数运算实现直线的生成
*/
std::vector<Point2D> DDALineAlgorithm::GeneratePoints(const Point2D& start, const Point2D& end) {
    std::vector<Point2D> points;

    // 计算x和y方向的位移
    int dx = end.x - start.x;
    int dy = end.y - start.y;

    // 确定步进次数(取x、y方向位移的较大值)
    int steps = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);

    // 计算x和y方向的增量
    float xIncrement = static_cast<float>(dx) / steps;
    float yIncrement = static_cast<float>(dy) / steps;

    // 初始化起点坐标(转换为浮点数以提高精度)
    float x = static_cast<float>(start.x);
    float y = static_cast<float>(start.y);

    // 生成直线上的所有点
    for (int i = 0; i <= steps; i++) {
        points.push_back(Point2D(round(x), round(y)));
        x += xIncrement;
        y += yIncrement;
    }

    return points;
}

/**
* 中点直线算法实现
* 基于中点判别的思想,使用整数运算提高效率
*/
std::vector<Point2D> MidpointLineAlgorithm::GeneratePoints(const Point2D& start, const Point2D& end)
{
    std::vector<Point2D> points;
    int x1 = start.x, y1 = start.y;
    int x2 = end.x, y2 = end.y;

    // 处理垂直线的特殊情况
    if (x1 == x2) {
        int yStart = std::min<int>(y1, y2);
        int yEnd = std::max<int>(y1, y2);
        for (int y = yStart; y <= yEnd; y++) {
            points.push_back(Point2D(x1, y));
        }
        return points;
    }

    // 确保从左向右画线
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = abs(y2 - y1);
    int step_y = (y2 >= y1) ? 1 : -1;

    // 处理斜率大于1的情况
    bool steep = dy > dx;
    if (steep) {
        // 交换x,y坐标，使斜率小于1
        std::swap(x1, y1);
        std::swap(x2, y2);
        std::swap(dx, dy);
        step_y = (y2 >= y1) ? 1 : -1;
    }

    // 中点算法的主循环
    int x = x1, y = y1;
    int d = 2 * dy - dx;  // 初始判别式
    while (x <= x2) {
        points.push_back(steep ? Point2D(y, x) : Point2D(x, y));

        if (d < 0) {
            d += 2 * dy;
        }
        else {
            y += step_y;
            d += 2 * (dy - dx);
        }
        x++;
    }

    return points;
}

/**
* Bresenham直线算法实现
* 使用增量误差的思想,仅使用整数运算
*/
std::vector<Point2D> BresenhamLineAlgorithm::GeneratePoints(const Point2D& start, const Point2D& end) {
    std::vector<Point2D> points;

    // 获取起点和终点坐标
    int x0 = start.x;
    int y0 = start.y;
    int x1 = end.x;
    int y1 = end.y;

    // 计算x、y方向的位移和步进方向
    int dx = x1 - x0;
    int dy = y1 - y0;
    int ux = (dx > 0) ? 1 : -1;  // x方向步进
    int uy = (dy > 0) ? 1 : -1;  // y方向步进

    // 计算2倍的位移量(避免浮点运算)
    int dx2 = abs(dx * 2);
    int dy2 = abs(dy * 2);

    // 以x为主方向的情况
    if (abs(dx) > abs(dy)) {
        int e = -dx;  // 初始误差
        int x = x0;
        int y = y0;

        while (x != x1 + ux) {
            points.push_back(Point2D(x, y));
            e = e + dy2;  // 误差增量
            if (e > 0) {
                if (y != y1) {
                    y += uy;
                }
                e = e - dx2;
            }
            x += ux;
        }
    }
    // 以y为主方向的情况
    else {
        int e = -dy;  // 初始误差
        int x = x0;
        int y = y0;

        while (y != y1 + uy) {
            points.push_back(Point2D(x, y));
            e = e + dx2;  // 误差增量
            if (e > 0) {
                if (x != x1) {
                    x += ux;
                }
                e = e - dy2;
            }
            y += uy;
        }
    }

    return points;
}
