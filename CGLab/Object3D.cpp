/*
 *
 * Models/Object3D.cpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 * 
 */

#include "pch.h"
#include "Object3D.hpp"

using namespace MyGraphics;

void Object3D::Transform(const Matrix4x4& matrix) {
    for (auto& vertex : m_vertices) {
        vertex = TransformPoint(vertex, matrix);
    }
}

void Object3D::GetProjections(
    std::vector<Point2D>& frontView,
    std::vector<Point2D>& topView,
    std::vector<Point2D>& sideView) const
{
    frontView.clear();
    topView.clear();
    sideView.clear();

    // ��ÿ���������ͶӰ
    for (const auto& vertex : m_vertices) {
        // ����ͼ (x-yƽ��)
        frontView.push_back(Point2D(vertex.x, vertex.y));
        // ����ͼ (x-zƽ��)
        topView.push_back(Point2D(vertex.x, -vertex.z));  // ע��z����ȡ��
        // ����ͼ (z-yƽ��)
        sideView.push_back(Point2D(vertex.z, vertex.y));
    }
}

void Object3D::DrawProjection(CDC* pDC, const std::vector<Point2D>& points,
    CRect rect, COLORREF color) const
{
    // �������ű�����ƫ��������Ӧ��������
    double scaleX = rect.Width() / 200.0;  // ����ģ���ڡ�100��Χ��
    double scaleY = rect.Height() / 200.0;
    int offsetX = rect.left + rect.Width() / 2;
    int offsetY = rect.top + rect.Height() / 2;

    // ���û���
    CPen pen(PS_SOLID, 1, color);
    CPen* pOldPen = pDC->SelectObject(&pen);

    // ���Ʊ�
    for (const auto& edge : m_edges) {
        const Point2D& p1 = points[edge.first];
        const Point2D& p2 = points[edge.second];

        // ת������Ļ����
        int x1 = offsetX + static_cast<int>(p1.x * scaleX);
        int y1 = offsetY - static_cast<int>(p1.y * scaleY);  // Y������Ϊ��
        int x2 = offsetX + static_cast<int>(p2.x * scaleX);
        int y2 = offsetY - static_cast<int>(p2.y * scaleY);

        pDC->MoveTo(x1, y1);
        pDC->LineTo(x2, y2);
    }

    // �ָ�ԭ���Ļ���
    pDC->SelectObject(pOldPen);
}