/*
*
* �ļ���: Algorithms/LineAlgorithms.cpp
* ����: Ziyu ZHOU @ SDAU
* ����: 26/11/24
*
* ˵��: ���ļ�ʵ�������־����ֱ�������㷨:
* 1. DDA�㷨 (��ֵ΢�ַ�)
* 2. �е�ֱ���㷨
* 3. Bresenhamֱ���㷨
*/

#include "pch.h"
#include "LineAlgorithms.hpp"
#include <cmath>

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* DDAֱ�������㷨ʵ��
* ������ֵ΢�ֵ�˼��,ͨ������������ʵ��ֱ�ߵ�����
*/
std::vector<Point2D> DDALineAlgorithm::GeneratePoints(const Point2D& start, const Point2D& end) {
    std::vector<Point2D> points;

    // ����x��y�����λ��
    int dx = end.x - start.x;
    int dy = end.y - start.y;

    // ȷ����������(ȡx��y����λ�ƵĽϴ�ֵ)
    int steps = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);

    // ����x��y���������
    float xIncrement = static_cast<float>(dx) / steps;
    float yIncrement = static_cast<float>(dy) / steps;

    // ��ʼ���������(ת��Ϊ����������߾���)
    float x = static_cast<float>(start.x);
    float y = static_cast<float>(start.y);

    // ����ֱ���ϵ����е�
    for (int i = 0; i <= steps; i++) {
        points.push_back(Point2D(round(x), round(y)));
        x += xIncrement;
        y += yIncrement;
    }

    return points;
}

/**
* �е�ֱ���㷨ʵ��
* �����е��б��˼��,ʹ�������������Ч��
*/
std::vector<Point2D> MidpointLineAlgorithm::GeneratePoints(const Point2D& start, const Point2D& end)
{
    std::vector<Point2D> points;
    int x1 = start.x, y1 = start.y;
    int x2 = end.x, y2 = end.y;

    // ����ֱ�ߵ��������
    if (x1 == x2) {
        int yStart = std::min<int>(y1, y2);
        int yEnd = std::max<int>(y1, y2);
        for (int y = yStart; y <= yEnd; y++) {
            points.push_back(Point2D(x1, y));
        }
        return points;
    }

    // ȷ���������һ���
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = abs(y2 - y1);
    int step_y = (y2 >= y1) ? 1 : -1;

    // ����б�ʴ���1�����
    bool steep = dy > dx;
    if (steep) {
        // ����x,y���꣬ʹб��С��1
        std::swap(x1, y1);
        std::swap(x2, y2);
        std::swap(dx, dy);
        step_y = (y2 >= y1) ? 1 : -1;
    }

    // �е��㷨����ѭ��
    int x = x1, y = y1;
    int d = 2 * dy - dx;  // ��ʼ�б�ʽ
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
* Bresenhamֱ���㷨ʵ��
* ʹ����������˼��,��ʹ����������
*/
std::vector<Point2D> BresenhamLineAlgorithm::GeneratePoints(const Point2D& start, const Point2D& end) {
    std::vector<Point2D> points;

    // ��ȡ�����յ�����
    int x0 = start.x;
    int y0 = start.y;
    int x1 = end.x;
    int y1 = end.y;

    // ����x��y�����λ�ƺͲ�������
    int dx = x1 - x0;
    int dy = y1 - y0;
    int ux = (dx > 0) ? 1 : -1;  // x���򲽽�
    int uy = (dy > 0) ? 1 : -1;  // y���򲽽�

    // ����2����λ����(���⸡������)
    int dx2 = abs(dx * 2);
    int dy2 = abs(dy * 2);

    // ��xΪ����������
    if (abs(dx) > abs(dy)) {
        int e = -dx;  // ��ʼ���
        int x = x0;
        int y = y0;

        while (x != x1 + ux) {
            points.push_back(Point2D(x, y));
            e = e + dy2;  // �������
            if (e > 0) {
                if (y != y1) {
                    y += uy;
                }
                e = e - dx2;
            }
            x += ux;
        }
    }
    // ��yΪ����������
    else {
        int e = -dy;  // ��ʼ���
        int x = x0;
        int y = y0;

        while (y != y1 + uy) {
            points.push_back(Point2D(x, y));
            e = e + dx2;  // �������
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
