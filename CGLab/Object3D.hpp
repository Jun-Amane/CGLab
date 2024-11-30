/*
 *
 * Models/Object3D.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 *
*/

#pragma once
#include "Point3D.hpp"
#include "Point2D.hpp"
#include "Matrix4x4.hpp"
#include "Transform3D.hpp"
#include <vector>
#include <utility>

namespace MyGraphics {
    class Object3D {
    public:
        Object3D() = default;
        virtual ~Object3D() = default;

        // 三维变换
        void Transform(const Matrix4x4& matrix);

        // 获取三视图投影点
        void GetProjections(
            std::vector<Point2D>& frontView,   // 主视图(前视图)
            std::vector<Point2D>& topView,     // 俯视图
            std::vector<Point2D>& sideView     // 左视图
        ) const;

        // 绘制投影图
        void DrawProjection(CDC* pDC, const std::vector<Point2D>& points,
            CRect rect, COLORREF color = RGB(0, 0, 0)) const;

        // 获取边的集合
        const std::vector<std::pair<int, int>>& GetEdges() const { return m_edges; }

        // 获取顶点集合
        const std::vector<Point3D>& GetVertices() const { return m_vertices; }

    protected:
        std::vector<Point3D> m_vertices;          // 顶点集合
        std::vector<std::pair<int, int>> m_edges;  // 边集合(顶点索引对)
    };
}