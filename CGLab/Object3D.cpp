/*
 * �ļ�: Models/Object3D.cpp
 * ����: Ziyu ZHOU @ SDAU
 * ����: 30/11/24
 *
 * ˵��: ���ļ�ʵ����Object3D��ľ��幦�ܣ�������ά���α任��ͶӰ�����ɼ�ͶӰ���ơ�
 */

#include "pch.h"
#include "Object3D.hpp"
using namespace MyGraphics;

/**
 * ����ά����Ķ���Ӧ��ָ���ı任����
 * @param matrix: 4x4�任����
 */
void Object3D::Transform(const Matrix4x4& matrix) {
    // �������ж��㲢���б任
    for (auto& vertex : m_vertices) {
        // ʹ��TransformPoint��������任��Ķ�������
        vertex = TransformPoint(vertex, matrix);
    }
}

/**
 * ��ȡ��ά���������ͼͶӰ�㼯
 * @param frontView: ����ͼ(ǰ��ͼ)�㼯,XOYƽ��ͶӰ
 * @param topView: ����ͼ�㼯,XOZƽ��ͶӰ
 * @param sideView: ����ͼ�㼯,YOZƽ��ͶӰ
 */
void Object3D::GetProjections(
    std::vector<Point2D>& frontView,
    std::vector<Point2D>& topView,
    std::vector<Point2D>& sideView) const
{
    // ��ո���ͼ�㼯��ȷ��û����������
    frontView.clear();
    topView.clear();
    sideView.clear();

    // �������ж��㣬�ֱ������������ͼ������ͼ������ͼ�е�ͶӰ
    for (const auto& vertex : m_vertices) {
        // ����ͼ (x-yƽ��ͶӰ)
        frontView.push_back(Point2D(vertex.x, vertex.y));
        // ����ͼ (x-zƽ��ͶӰ��z����ȡ���Է��Ϲ��û��Ʒ���)
        topView.push_back(Point2D(vertex.x, -vertex.z));
        // ����ͼ (z-yƽ��ͶӰ)
        sideView.push_back(Point2D(vertex.z, vertex.y));
    }
}

/**
 * ��ָ�����豸�������л��ƶ�άͶӰ
 * @param pDC: ��ͼ�豸������ָ��
 * @param points: ͶӰ�㼯
 * @param rect: �����������
 * @param color: ������ɫ
 */
void Object3D::DrawProjection(CDC* pDC, const std::vector<Point2D>& points,
    CRect rect, COLORREF color) const
{
    // �������ű�����ʹͶӰ�����䵽ָ����������
    double scaleX = rect.Width() / 200.0;  // ����ģ�͵����귶Χ�ڡ�100
    double scaleY = rect.Height() / 200.0;

    // ����ƫ��������ģ�����Ķ��뵽������������
    int offsetX = rect.left + rect.Width() / 2;
    int offsetY = rect.top + rect.Height() / 2;

    // ���û�������Ļ���
    CPen pen(PS_SOLID, 1, color);
    CPen* pOldPen = pDC->SelectObject(&pen);

    // ����ÿ���߲����������ӵ���������
    for (const auto& edge : m_edges) {
        // ���ݱߵĶ���������ȡ��Ӧ��ͶӰ��
        const Point2D& p1 = points[edge.first];
        const Point2D& p2 = points[edge.second];

        // ��������ת��Ϊ��Ļ����
        int x1 = offsetX + static_cast<int>(p1.x * scaleX);
        int y1 = offsetY - static_cast<int>(p1.y * scaleY);  // ע��Y������Ϊ��
        int x2 = offsetX + static_cast<int>(p2.x * scaleX);
        int y2 = offsetY - static_cast<int>(p2.y * scaleY);

        // ʹ���豸�����Ļ����߶�
        pDC->MoveTo(x1, y1);
        pDC->LineTo(x2, y2);
    }

    // �ָ�ԭ���Ļ����Է�ֹӰ���������
    pDC->SelectObject(pOldPen);
}
