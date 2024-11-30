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

    if (edge_code & CODE_N) {  // ���ϱ߽��ཻ
        intersection.y = window.GetYmin();
        intersection.x = p1.x + (window.GetYmin() - p1.y) / slope;
    }
    else if (edge_code & CODE_S) {  // ���±߽��ཻ
        intersection.y = window.GetYmax();
        intersection.x = p1.x + (window.GetYmax() - p1.y) / slope;
    }
    else if (edge_code & CODE_W) {  // ����߽��ཻ
        intersection.x = window.GetXmin();
        intersection.y = p1.y + slope * (window.GetXmin() - p1.x);
    }
    else if (edge_code & CODE_E) {  // ���ұ߽��ཻ
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
    
    // ������˵�������벻Ϊ0��˵����ͬ���ⲿ����ȫ����
    if (start_code & end_code)
        return;
        
    // ������˵㶼���ڲ���ֱ�����
    if (start_code == 0 && end_code == 0) {
        result.push_back(end);
        return;
    }
    
    // �Ա߽���ϸ��
    Point2D mid((start.x + end.x) / 2, (start.y + end.y) / 2);
    
    // ��������㹻�ӽ������㽻��
    if (abs(start.x - mid.x) <= 1 && abs(start.y - mid.y) <= 1) {
        if (start_code == 0)  // ������ڲ�
            result.push_back(start);
            
        int code = start_code ? start_code : end_code;
        Point2D intersection = ComputeIntersection(start, end, code, window);
        result.push_back(intersection);
        
        if (end_code == 0)  // �յ����ڲ�
            result.push_back(end);
            
        return;
    }
    
    // �ݹ鴦������
    ClipEdge(start, mid, window, result);
    ClipEdge(mid, end, window, result);
}

std::vector<Point2D> WeilerAthertonAlgorithm::ClipPolygon(
    const std::vector<Point2D>& vertices,
    const ClipWindow& window) {
    
    if (vertices.size() < 3)
        return std::vector<Point2D>();
        
    std::vector<Point2D> result;
    
    // ��ÿ���߽��вü�
    for (size_t i = 0; i < vertices.size(); ++i) {
        const Point2D& start = vertices[i];
        const Point2D& end = vertices[(i + 1) % vertices.size()];
        
        ClipEdge(start, end, window, result);
    }
    
    return result;
}