/*
*
* �ļ�: Algorithms/WeilerAthertonAlgorithm.cpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�ʵ����Weiler-Atherton����βü��㷨
* ͨ���ݹ�ϸ�ֵķ�ʽ�Զ����ÿ���߽��вü�
* ��Ҫ����:
* 1. �������������
* 2. ����ü����ڵĽ������
* 3. �ߵĲü�����
* 4. ��������εĲü�����
*/

#include "pch.h"
#include "WeilerAthertonAlgorithm.hpp"
#include <algorithm>
#include <vector>

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* ���������ڲü����ڵ��������
* ʹ��9λ�����Ʊ����ʾ���λ��:
* ����(C):0000, ��(N):1000, ��(S):0100
* ��(E):0010, ��(W):0001
*
* @param point: ������ĵ�
* @param window: �ü�����
* @return: ���ص���������
*/
int WeilerAthertonAlgorithm::ComputeCode(
    const Point2D& point, const ClipWindow& window) {

    int code = CODE_C;

    // �жϵ��봰�����±߽�Ĺ�ϵ
    if (point.y < window.GetYmin())
        code |= CODE_N;
    else if (point.y > window.GetYmax())
        code |= CODE_S;

    // �жϵ��봰�����ұ߽�Ĺ�ϵ    
    if (point.x < window.GetXmin())
        code |= CODE_W;
    else if (point.x > window.GetXmax())
        code |= CODE_E;

    return code;
}

/**
* �����߶���ü����ڱ߽�Ľ���
* ʹ��ֱ�߷��̺Ͳ������̼��㽻������
*
* @param p1: �߶����
* @param p2: �߶��յ�
* @param edge_code: �߽����
* @param window: �ü�����
* @return: ���ؽ�������
*/
Point2D WeilerAthertonAlgorithm::ComputeIntersection(
    const Point2D& p1, const Point2D& p2,
    int edge_code, const ClipWindow& window) {

    Point2D intersection;
    double slope = 0;

    // ����б��(��ֱ�߶����⴦��)
    if (p2.x != p1.x)
        slope = static_cast<double>(p2.y - p1.y) / (p2.x - p1.x);

    // ���ݱ߽����ֱ���㽻��
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

/**
* ��һ���߽��вü�
* ʹ�õݹ�ϸ�ֵķ�ʽ����ߵĲü�
*
* @param start: �ߵ����
* @param end: �ߵ��յ�
* @param window: �ü�����
* @param result: �洢�ü�����ĵ㼯
*/
void WeilerAthertonAlgorithm::ClipEdge(
    const Point2D& start, const Point2D& end,
    const ClipWindow& window, std::vector<Point2D>& result) {

    // ����˵���������
    int start_code = ComputeCode(start, window);
    int end_code = ComputeCode(end, window);

    // ����ȫ�ڴ�����
    if (start_code & end_code)
        return;

    // ����ȫ�ڴ�����
    if (start_code == 0 && end_code == 0) {
        result.push_back(end);
        return;
    }

    // ȡ�ߵ��е���еݹ�ϸ��
    Point2D mid((start.x + end.x) / 2, (start.y + end.y) / 2);

    // ���ϸ�ִﵽ����Ҫ�󣬼��㽻��
    if (abs(start.x - mid.x) <= 1 && abs(start.y - mid.y) <= 1) {
        if (start_code == 0)  // ����ڴ�����
            result.push_back(start);

        // �����봰�ڱ߽�Ľ���
        int code = start_code ? start_code : end_code;
        Point2D intersection = ComputeIntersection(start, end, code, window);
        result.push_back(intersection);

        if (end_code == 0)  // �յ��ڴ�����
            result.push_back(end);

        return;
    }

    // �ݹ鴦�������Ӷ�
    ClipEdge(start, mid, window, result);
    ClipEdge(mid, end, window, result);
}

/**
* ����������ν��вü�
* ���δ������ε�ÿ����
*
* @param vertices: ����ζ�������
* @param window: �ü�����
* @return: ���زü���Ķ���ζ�������
*/
std::vector<Point2D> WeilerAthertonAlgorithm::ClipPolygon(
    const std::vector<Point2D>& vertices,
    const ClipWindow& window) {

    // ��������Ƿ���Ч
    if (vertices.size() < 3)
        return std::vector<Point2D>();

    std::vector<Point2D> result;

    // �Զ���ε�ÿ���߽��вü�
    for (size_t i = 0; i < vertices.size(); ++i) {
        const Point2D& start = vertices[i];
        const Point2D& end = vertices[(i + 1) % vertices.size()];

        ClipEdge(start, end, window, result);
    }

    return result;
}