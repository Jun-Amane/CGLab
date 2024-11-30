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

        // ��ά�任
        void Transform(const Matrix4x4& matrix);

        // ��ȡ����ͼͶӰ��
        void GetProjections(
            std::vector<Point2D>& frontView,   // ����ͼ(ǰ��ͼ)
            std::vector<Point2D>& topView,     // ����ͼ
            std::vector<Point2D>& sideView     // ����ͼ
        ) const;

        // ����ͶӰͼ
        void DrawProjection(CDC* pDC, const std::vector<Point2D>& points,
            CRect rect, COLORREF color = RGB(0, 0, 0)) const;

        // ��ȡ�ߵļ���
        const std::vector<std::pair<int, int>>& GetEdges() const { return m_edges; }

        // ��ȡ���㼯��
        const std::vector<Point3D>& GetVertices() const { return m_vertices; }

    protected:
        std::vector<Point3D> m_vertices;          // ���㼯��
        std::vector<std::pair<int, int>> m_edges;  // �߼���(����������)
    };
}