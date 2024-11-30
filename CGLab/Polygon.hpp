/*
 * Models/Polygon.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */

#pragma once
#include "Point2D.hpp"
#include "GraphicsObject.hpp"
#include "IPolygonAlgorithm.hpp"
#include <memory>

namespace MyGraphics {
    class Polygon : public GraphicsObject {
    public:
        enum Algorithm {
            ALGO_SCANLINE,      // x-ɨ�������
            ALGO_SEEDFILL_4,    // �������������
            ALGO_SEEDFILL_8     // �������������
        };

        Polygon();
        ~Polygon() override = default;

        void SetAlgorithm(Algorithm algo);
        void AddVertex(const Point2D& point);  // ��Ӷ���
        void SetSeed(const Point2D& seed);     // �������ӵ�
        void Close();  // ��ն����
        bool IsClosed() const { return m_closed; }
        void GeneratePoints() override;
        void Draw(CDC* pDC) override;
        void DrawVertex(CDC* pDC, const Point2D& point);  // ���ƶ���
        const std::vector<Point2D>& GetVertices() const { return m_vertices; }  // ��ȡ��������
        void DrawSeed(CDC* pDC, const Point2D& point);  // �������ӵ�
        bool HasSeed() const { return m_hasSeed; }  // �Ƿ����������ӵ�

    private:
        Algorithm m_algorithm;
        std::vector<Point2D> m_vertices;
        static const int VERTEX_SIZE = 4;  // ������ʾ�Ĵ�С
        static const int SEED_SIZE = 6;  // ���ӵ���ʾ�Ĵ�С
        bool m_hasSeed = false;          // �Ƿ����������ӵ�
        Point2D m_seed;                // ���ӵ�
        bool m_closed;                 // ������Ƿ�պ�
        std::vector<Point2D> m_points; // �������ĵ㼯
        std::unique_ptr<Algorithms::IPolygonAlgorithm> m_polygonAlgorithm;
    };
}