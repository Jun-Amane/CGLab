/*
 * Algorithms/WeilerAthertonAlgorithm.cpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */


#include "pch.h"
#include "WeilerAthertonAlgorithm.hpp"
#include <algorithm>
#include <vector>

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

int WeilerAthertonAlgorithm::ComputeCode(
    const Point2D& point, const ClipWindow& window) {
    
    int code = CODE_C;
    
    if (point.y < window.GetYmin())
        code |= CODE_N;
    else if (point.y > window.GetYmax())
        code |= CODE_S;
        
    if (point.x < window.GetXmin())
        code |= CODE_W;
    else if (point.x > window.GetXmax())
        code |= CODE_E;
        
    return code;
}

Point2D WeilerAthertonAlgorithm::ComputeIntersection(
    const Point2D& p1, const Point2D& p2,
    int edge_code, const ClipWindow& window) {
    
    Point2D intersection;
    double slope = 0;
    
    if (p2.x != p1.x)
        slope = static_cast<double>(p2.y - p1.y) / (p2.x - p1.x);

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

void WeilerAthertonAlgorithm::ClipEdge(
    const Point2D& start, const Point2D& end,
    const ClipWindow& window, std::vector<Point2D>& result) {
    
    int start_code = ComputeCode(start, window);
    int end_code = ComputeCode(end, window);
    
    // 如果两端点编码相与不为0，说明在同侧外部，完全舍弃
    if (start_code & end_code)
        return;
        
    // 如果两端点都在内部，直接添加
    if (start_code == 0 && end_code == 0) {
        result.push_back(end);
        return;
    }
    
    // 对边进行细分
    Point2D mid((start.x + end.x) / 2, (start.y + end.y) / 2);
    
    // 如果两点足够接近，计算交点
    if (abs(start.x - mid.x) <= 1 && abs(start.y - mid.y) <= 1) {
        if (start_code == 0)  // 起点在内部
            result.push_back(start);
            
        int code = start_code ? start_code : end_code;
        Point2D intersection = ComputeIntersection(start, end, code, window);
        result.push_back(intersection);
        
        if (end_code == 0)  // 终点在内部
            result.push_back(end);
            
        return;
    }
    
    // 递归处理两段
    ClipEdge(start, mid, window, result);
    ClipEdge(mid, end, window, result);
}

std::vector<Point2D> WeilerAthertonAlgorithm::ClipPolygon(
    const std::vector<Point2D>& vertices,
    const ClipWindow& window) {
    
    if (vertices.size() < 3)
        return std::vector<Point2D>();
        
    std::vector<Point2D> result;
    
    // 对每条边进行裁剪
    for (size_t i = 0; i < vertices.size(); ++i) {
        const Point2D& start = vertices[i];
        const Point2D& end = vertices[(i + 1) % vertices.size()];
        
        ClipEdge(start, end, window, result);
    }
    
    return result;
}