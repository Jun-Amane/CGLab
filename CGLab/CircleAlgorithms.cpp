/*
 *
 * �ļ�: Algorithms/CircleAlgorithms.cpp
 * ����: Ziyu ZHOU @ SDAU
 * ����: 27/11/24
 *
 * ˵��: ���ļ�ʵ��������Բ�������㷨��
 * 1. �е�Բ�����㷨 (Midpoint Circle Algorithm)
 * 2. BresenhamԲ�����㷨
 * �������㷨��������Բ�İ˷ֶԳ����������Ч��
 */

#include "pch.h"
#include "CircleAlgorithms.hpp"
#include <cmath>

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/* �е�Բ�㷨ʵ�ֲ��� */

/**
 * ����Բ�İ˷ֶԳ����ʣ���һ�������������߸��ԳƵ�
 * @param points: �洢���ɵ������
 * @param centre: Բ������
 * @param x: ��ǰ���xƫ����
 * @param y: ��ǰ���yƫ����
 */
void MidpointCircleAlgorithm::AddCirclePoints(std::vector<Point2D>& points,
    const Point2D& centre,
    int x, int y) {
    // ����Բ�İ˷ֶԳ����ʣ�����һ����(x,y)����8���ԳƵ�
    points.push_back(Point2D(x + centre.x, y + centre.y));     // ��һ����
    points.push_back(Point2D(-x + centre.x, y + centre.y));    // �ڶ�����
    points.push_back(Point2D(-x + centre.x, -y + centre.y));   // ��������
    points.push_back(Point2D(x + centre.x, -y + centre.y));    // ��������
    points.push_back(Point2D(y + centre.x, x + centre.y));     // ��һ���޶ԳƵ�
    points.push_back(Point2D(-y + centre.x, x + centre.y));    // �ڶ����޶ԳƵ�
    points.push_back(Point2D(-y + centre.x, -x + centre.y));   // �������޶ԳƵ�
    points.push_back(Point2D(y + centre.x, -x + centre.y));    // �������޶ԳƵ�
}

/**
 * ʹ���е�Բ�㷨����Բ�����е�
 * @param centre: Բ������
 * @param radius: Բ�İ뾶
 * @return: ����Բ�����е�����꼯��
 */
std::vector<Point2D> MidpointCircleAlgorithm::GeneratePoints(const Point2D& centre, int radius) {
    std::vector<Point2D> points;
    int x = 0;
    int y = radius;
    // �е��б�ʽ�ĳ�ֵ d = 1 - R
    int d = 1 - radius;

    // �ȴ����һ���㣬���ɰ˸��ԳƵ�
    AddCirclePoints(points, centre, x, y);

    // ʹ���е��㷨����ѭ��
    // ��x < yʱ����ѭ����ȷ���ܴ���x=y���������Բ��45�Ƚ�λ�ã�
    while (x < y) {
        if (d < 0) {
            // ��ǰ����Բ�ڣ�ѡ��E��
            d += 2 * x + 3;  // �����б�ʽ��d += 2(x+1) + 1
        }
        else {
            // ��ǰ����Բ�⣬ѡ��SE��
            d += 2 * (x - y) + 5;  // �����б�ʽ��d += 2(x-y+1) + 3
            y--;  // y������Ҫ��1
        }
        x++;  // x�������Ǽ�1
        AddCirclePoints(points, centre, x, y);
    }

    return points;
}

/* BresenhamԲ�㷨ʵ�ֲ��� */

/**
 * BresenhamԲ�㷨�ĶԳƵ����ɺ���
 * ԭ�����е��㷨��ͬ����������Բ�İ˷ֶԳ���
 */
void BresenhamCircleAlgorithm::AddCirclePoints(std::vector<Point2D>& points,
    const Point2D& center,
    int x, int y) {
    // ʵ�ַ�ʽ���е��㷨��ͬ�����ɰ˸��ԳƵ�
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
 * ʹ��Bresenham�㷨����Բ�����е�
 * @param center: Բ������
 * @param radius: Բ�İ뾶
 * @return: ����Բ�����е�����꼯��
 */
std::vector<Point2D> BresenhamCircleAlgorithm::GeneratePoints(const Point2D& center, int radius) {
    std::vector<Point2D> points;

    // ������Ч�뾶�����
    if (radius <= 0) {
        return points;
    }

    int x = 0;
    int y = radius;
    // Bresenham�㷨���б�ʽ��ֵ
    int d = 1 - radius;

    // �����һ����
    AddCirclePoints(points, center, x, y);

    // Bresenham�㷨��ѭ��
    while (x <= y) {
        if (d < 0) {
            // ѡ��E��
            d += 2 * x + 3;
        }
        else {
            // ѡ��SE��
            d += 2 * (x - y) + 5;
            y--;  // ����d>=0ʱy�ż�1
        }
        x++;  // xʼ�յ���
        AddCirclePoints(points, center, x, y);
    }

    return points;
}