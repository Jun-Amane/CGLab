/*
*
* 文件: Algorithms/WeilerAthertonAlgorithm.cpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件实现了Weiler-Atherton多边形裁剪算法
* 通过递归细分的方式对多边形每条边进行裁剪
* 主要包含:
* 1. 点的区域编码计算
* 2. 边与裁剪窗口的交点计算
* 3. 边的裁剪处理
* 4. 整个多边形的裁剪流程
*/

#include "pch.h"
#include "WeilerAthertonAlgorithm.hpp"
#include <algorithm>
#include <vector>

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* 计算点相对于裁剪窗口的区域编码
* 使用9位二进制编码表示点的位置:
* 中心(C):0000, 北(N):1000, 南(S):0100
* 东(E):0010, 西(W):0001
*
* @param point: 待编码的点
* @param window: 裁剪窗口
* @return: 返回点的区域编码
*/
int WeilerAthertonAlgorithm::ComputeCode(
    const Point2D& point, const ClipWindow& window) {

    int code = CODE_C;

    // 判断点与窗口上下边界的关系
    if (point.y < window.GetYmin())
        code |= CODE_N;
    else if (point.y > window.GetYmax())
        code |= CODE_S;

    // 判断点与窗口左右边界的关系    
    if (point.x < window.GetXmin())
        code |= CODE_W;
    else if (point.x > window.GetXmax())
        code |= CODE_E;

    return code;
}

/**
* 计算线段与裁剪窗口边界的交点
* 使用直线方程和参数方程计算交点坐标
*
* @param p1: 线段起点
* @param p2: 线段终点
* @param edge_code: 边界编码
* @param window: 裁剪窗口
* @return: 返回交点坐标
*/
Point2D WeilerAthertonAlgorithm::ComputeIntersection(
    const Point2D& p1, const Point2D& p2,
    int edge_code, const ClipWindow& window) {

    Point2D intersection;
    double slope = 0;

    // 计算斜率(垂直线段特殊处理)
    if (p2.x != p1.x)
        slope = static_cast<double>(p2.y - p1.y) / (p2.x - p1.x);

    // 根据边界编码分别计算交点
    if (edge_code & CODE_N) {  // 与上边界相交
        intersection.y = window.GetYmin();
        intersection.x = p1.x + (window.GetYmin() - p1.y) / slope;
    }
    else if (edge_code & CODE_S) {  // 与下边界相交 
        intersection.y = window.GetYmax();
        intersection.x = p1.x + (window.GetYmax() - p1.y) / slope;
    }
    else if (edge_code & CODE_W) {  // 与左边界相交
        intersection.x = window.GetXmin();
        intersection.y = p1.y + slope * (window.GetXmin() - p1.x);
    }
    else if (edge_code & CODE_E) {  // 与右边界相交
        intersection.x = window.GetXmax();
        intersection.y = p1.y + slope * (window.GetXmax() - p1.x);
    }

    return intersection;
}

/**
* 对一条边进行裁剪
* 使用递归细分的方式处理边的裁剪
*
* @param start: 边的起点
* @param end: 边的终点
* @param window: 裁剪窗口
* @param result: 存储裁剪结果的点集
*/
void WeilerAthertonAlgorithm::ClipEdge(
    const Point2D& start, const Point2D& end,
    const ClipWindow& window, std::vector<Point2D>& result) {

    // 计算端点的区域编码
    int start_code = ComputeCode(start, window);
    int end_code = ComputeCode(end, window);

    // 边完全在窗口外
    if (start_code & end_code)
        return;

    // 边完全在窗口内
    if (start_code == 0 && end_code == 0) {
        result.push_back(end);
        return;
    }

    // 取边的中点进行递归细分
    Point2D mid((start.x + end.x) / 2, (start.y + end.y) / 2);

    // 如果细分达到精度要求，计算交点
    if (abs(start.x - mid.x) <= 1 && abs(start.y - mid.y) <= 1) {
        if (start_code == 0)  // 起点在窗口内
            result.push_back(start);

        // 计算与窗口边界的交点
        int code = start_code ? start_code : end_code;
        Point2D intersection = ComputeIntersection(start, end, code, window);
        result.push_back(intersection);

        if (end_code == 0)  // 终点在窗口内
            result.push_back(end);

        return;
    }

    // 递归处理两个子段
    ClipEdge(start, mid, window, result);
    ClipEdge(mid, end, window, result);
}

/**
* 对整个多边形进行裁剪
* 依次处理多边形的每条边
*
* @param vertices: 多边形顶点数组
* @param window: 裁剪窗口
* @return: 返回裁剪后的多边形顶点数组
*/
std::vector<Point2D> WeilerAthertonAlgorithm::ClipPolygon(
    const std::vector<Point2D>& vertices,
    const ClipWindow& window) {

    // 检查多边形是否有效
    if (vertices.size() < 3)
        return std::vector<Point2D>();

    std::vector<Point2D> result;

    // 对多边形的每条边进行裁剪
    for (size_t i = 0; i < vertices.size(); ++i) {
        const Point2D& start = vertices[i];
        const Point2D& end = vertices[(i + 1) % vertices.size()];

        ClipEdge(start, end, window, result);
    }

    return result;
}