/*
 * Models/Polygon.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */

#pragma once
#include "Point2D.hpp"
#include "Matrix3x3.hpp"
#include "Transform2D.hpp"
#include "GraphicsObject.hpp"
#include "IPolygonAlgorithm.hpp"
#include <memory>

namespace MyGraphics {
    class Polygon : public GraphicsObject {
    public:
        enum Algorithm {
            ALGO_SCANLINE,      // x-扫描线填充
            ALGO_SEEDFILL_4,    // 四邻域种子填充
            ALGO_SEEDFILL_8,    // 八邻域种子填充
            ALGO_WEILER_ATHERTON // WEILER_ATHERTON
        };

        Polygon();
        ~Polygon() override = default;

        void SetAlgorithm(Algorithm algo);
        void AddVertex(const Point2D& point);  // 添加顶点
        void SetSeed(const Point2D& seed);     // 设置种子点
        void Close();  // 封闭多边形
        bool IsClosed() const { return m_closed; }
        void GeneratePoints() override;
        void Draw(CDC* pDC) override;
        void DrawVertex(CDC* pDC, const Point2D& point);  // 绘制顶点
        const std::vector<Point2D>& GetVertices() const { return m_vertices; }  // 获取顶点数组
        void DrawSeed(CDC* pDC, const Point2D& point);  // 绘制种子点
        bool HasSeed() const { return m_hasSeed; }  // 是否已设置种子点

        void Transform(const Matrix3x3& matrix);

        void SetClipWindow(const ClipWindow& window) { m_clipWindow = window; }
        ClipWindow& GetClipWindow() { return m_clipWindow; }

    private:
        Algorithm m_algorithm;
        std::vector<Point2D> m_vertices;
        static const int VERTEX_SIZE = 4;  // 顶点显示的大小
        static const int SEED_SIZE = 6;  // 种子点显示的大小
        bool m_hasSeed = false;          // 是否已设置种子点
        Point2D m_seed;                // 种子点
        bool m_closed;                 // 多边形是否闭合
        std::vector<Point2D> m_points; // 用于填充的点集
        std::unique_ptr<Algorithms::IPolygonAlgorithm> m_polygonAlgorithm;
        ClipWindow m_clipWindow;
        std::vector<Point2D> m_originalVertices;  // 保存原始顶点
        bool m_isClipped;

    protected:
        void TransformVertices(const Matrix3x3& matrix);
    };
}