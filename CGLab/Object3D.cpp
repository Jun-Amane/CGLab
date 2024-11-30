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

    // 对每个顶点进行投影
    for (const auto& vertex : m_vertices) {
        // 主视图 (x-y平面)
        frontView.push_back(Point2D(vertex.x, vertex.y));
        // 俯视图 (x-z平面)
        topView.push_back(Point2D(vertex.x, -vertex.z));  // 注意z坐标取反
        // 左视图 (z-y平面)
        sideView.push_back(Point2D(vertex.z, vertex.y));
    }
}

void Object3D::DrawProjection(CDC* pDC, const std::vector<Point2D>& points,
    CRect rect, COLORREF color) const
{
    // 计算缩放比例和偏移量以适应绘制区域
    double scaleX = rect.Width() / 200.0;  // 假设模型在±100范围内
    double scaleY = rect.Height() / 200.0;
    int offsetX = rect.left + rect.Width() / 2;
    int offsetY = rect.top + rect.Height() / 2;

    // 设置画笔
    CPen pen(PS_SOLID, 1, color);
    CPen* pOldPen = pDC->SelectObject(&pen);

    // 绘制边
    for (const auto& edge : m_edges) {
        const Point2D& p1 = points[edge.first];
        const Point2D& p2 = points[edge.second];

        // 转换到屏幕坐标
        int x1 = offsetX + static_cast<int>(p1.x * scaleX);
        int y1 = offsetY - static_cast<int>(p1.y * scaleY);  // Y轴向上为正
        int x2 = offsetX + static_cast<int>(p2.x * scaleX);
        int y2 = offsetY - static_cast<int>(p2.y * scaleY);

        pDC->MoveTo(x1, y1);
        pDC->LineTo(x2, y2);
    }

    // 恢复原来的画笔
    pDC->SelectObject(pOldPen);
}