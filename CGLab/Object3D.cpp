/*
 * 文件: Models/Object3D.cpp
 * 作者: Ziyu ZHOU @ SDAU
 * 日期: 30/11/24
 *
 * 说明: 本文件实现了Object3D类的具体功能，包括三维几何变换、投影点生成及投影绘制。
 */

#include "pch.h"
#include "Object3D.hpp"
using namespace MyGraphics;

/**
 * 对三维对象的顶点应用指定的变换矩阵
 * @param matrix: 4x4变换矩阵
 */
void Object3D::Transform(const Matrix4x4& matrix) {
    // 遍历所有顶点并进行变换
    for (auto& vertex : m_vertices) {
        // 使用TransformPoint函数计算变换后的顶点坐标
        vertex = TransformPoint(vertex, matrix);
    }
}

/**
 * 获取三维对象的三视图投影点集
 * @param frontView: 主视图(前视图)点集,XOY平面投影
 * @param topView: 俯视图点集,XOZ平面投影
 * @param sideView: 左视图点集,YOZ平面投影
 */
void Object3D::GetProjections(
    std::vector<Point2D>& frontView,
    std::vector<Point2D>& topView,
    std::vector<Point2D>& sideView) const
{
    // 清空各视图点集，确保没有遗留数据
    frontView.clear();
    topView.clear();
    sideView.clear();

    // 遍历所有顶点，分别计算其在主视图、俯视图和左视图中的投影
    for (const auto& vertex : m_vertices) {
        // 主视图 (x-y平面投影)
        frontView.push_back(Point2D(vertex.x, vertex.y));
        // 俯视图 (x-z平面投影，z坐标取反以符合惯用绘制方向)
        topView.push_back(Point2D(vertex.x, -vertex.z));
        // 左视图 (z-y平面投影)
        sideView.push_back(Point2D(vertex.z, vertex.y));
    }
}

/**
 * 在指定的设备上下文中绘制二维投影
 * @param pDC: 绘图设备上下文指针
 * @param points: 投影点集
 * @param rect: 绘制区域矩形
 * @param color: 绘制颜色
 */
void Object3D::DrawProjection(CDC* pDC, const std::vector<Point2D>& points,
    CRect rect, COLORREF color) const
{
    // 计算缩放比例，使投影点适配到指定绘制区域
    double scaleX = rect.Width() / 200.0;  // 假设模型的坐标范围在±100
    double scaleY = rect.Height() / 200.0;

    // 计算偏移量，将模型中心对齐到绘制区域中心
    int offsetX = rect.left + rect.Width() / 2;
    int offsetY = rect.top + rect.Height() / 2;

    // 设置绘制所需的画笔
    CPen pen(PS_SOLID, 1, color);
    CPen* pOldPen = pDC->SelectObject(&pen);

    // 遍历每条边并绘制其连接的两个顶点
    for (const auto& edge : m_edges) {
        // 根据边的顶点索引获取对应的投影点
        const Point2D& p1 = points[edge.first];
        const Point2D& p2 = points[edge.second];

        // 将点坐标转换为屏幕坐标
        int x1 = offsetX + static_cast<int>(p1.x * scaleX);
        int y1 = offsetY - static_cast<int>(p1.y * scaleY);  // 注意Y轴向上为正
        int x2 = offsetX + static_cast<int>(p2.x * scaleX);
        int y2 = offsetY - static_cast<int>(p2.y * scaleY);

        // 使用设备上下文绘制线段
        pDC->MoveTo(x1, y1);
        pDC->LineTo(x2, y2);
    }

    // 恢复原来的画笔以防止影响后续绘制
    pDC->SelectObject(pOldPen);
}
