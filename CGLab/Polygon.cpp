/*
 * Models/Polygon.cpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */

#include "pch.h"
#include "Polygon.hpp"
#include "PolygonAlgorithms.hpp"
#include "WeilerAthertonAlgorithm.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

Polygon::Polygon()
    : GraphicsObject(OT_POLYGON)
    , m_algorithm(ALGO_SCANLINE)
    , m_closed(false)
    , m_isClipped(false)
    , m_polygonAlgorithm(std::make_unique<ScanLineFillAlgorithm>())
{
}

void Polygon::SetAlgorithm(Algorithm algo) {
    m_algorithm = algo;
    switch (algo) {
    case ALGO_SCANLINE:
        m_polygonAlgorithm = std::make_unique<ScanLineFillAlgorithm>();
        break;
    case ALGO_SEEDFILL_4:
        m_polygonAlgorithm = std::make_unique<SeedFill4Algorithm>();
        break;
    case ALGO_SEEDFILL_8:
        m_polygonAlgorithm = std::make_unique<SeedFill8Algorithm>();
        break;
    case ALGO_WEILER_ATHERTON:
        m_polygonAlgorithm = std::make_unique<WeilerAthertonAlgorithm>();
        break;
    }
}

void Polygon::AddVertex(const Point2D& point) {
    if (!m_closed) {
        m_vertices.push_back(point);
    }
}

void Polygon::SetSeed(const Point2D& seed) {
    m_seed = seed;
    m_hasSeed = true;
}

void Polygon::Close() {
    if (m_vertices.size() >= 3) {
        m_closed = true;
    }
}

void Polygon::GeneratePoints() {
    if (m_closed && m_polygonAlgorithm) {
        if (m_algorithm == ALGO_WEILER_ATHERTON) {
            // 保存原始顶点
            m_originalVertices = m_vertices;
            // 执行裁剪
            m_vertices = m_polygonAlgorithm->ClipPolygon(m_originalVertices, m_clipWindow);
            m_isClipped = true;
        }
        else if (m_algorithm == ALGO_SCANLINE) {
            m_points = m_polygonAlgorithm->GeneratePoints(m_vertices);
        }
        else {
            m_points = m_polygonAlgorithm->GeneratePoints(m_vertices, m_seed);
        }
    }
}

void Polygon::DrawVertex(CDC* pDC, const Point2D& point) {
    // 绘制一个小方块表示顶点
    pDC->Rectangle(point.x - VERTEX_SIZE, point.y - VERTEX_SIZE,
                  point.x + VERTEX_SIZE, point.y + VERTEX_SIZE);
}

void Polygon::DrawSeed(CDC* pDC, const Point2D& point) {
    // 绘制一个红色十字表示种子点
    CPen seedPen(PS_SOLID, 2, RGB(255, 0, 0));
    CPen* pOldPen = pDC->SelectObject(&seedPen);

    pDC->MoveTo(point.x - SEED_SIZE, point.y);
    pDC->LineTo(point.x + SEED_SIZE, point.y);
    pDC->MoveTo(point.x, point.y - SEED_SIZE);
    pDC->LineTo(point.x, point.y + SEED_SIZE);

    pDC->SelectObject(pOldPen);
}

void Polygon::Draw(CDC* pDC) {
    // 1. 如果是裁剪算法，先绘制裁剪窗口
    if (m_algorithm == ALGO_WEILER_ATHERTON) {
        m_clipWindow.Draw(pDC);

        // 如果有原始顶点，用虚线绘制原始多边形
        if (!m_originalVertices.empty()) {
            CPen dashPen(PS_DASH, 1, RGB(255, 128, 128));
            CPen* pOldPen = pDC->SelectObject(&dashPen);

            pDC->MoveTo(m_originalVertices[0].x, m_originalVertices[0].y);
            for (size_t i = 1; i < m_originalVertices.size(); ++i) {
                pDC->LineTo(m_originalVertices[i].x, m_originalVertices[i].y);
            }
            // 如果多边形已闭合，连接首尾顶点
            if (m_closed && m_originalVertices.size() > 2) {
                pDC->LineTo(m_originalVertices[0].x, m_originalVertices[0].y);
            }

            pDC->SelectObject(pOldPen);
        }
    }

    // 2. 绘制顶点
    CPen vertexPen(PS_SOLID, 1, RGB(0, 0, 255));  // 蓝色
    CBrush vertexBrush(RGB(0, 0, 255));
    CPen* pOldPen = pDC->SelectObject(&vertexPen);
    CBrush* pOldBrush = pDC->SelectObject(&vertexBrush);

    for (const auto& vertex : m_vertices) {
        DrawVertex(pDC, vertex);
    }

    // 3. 绘制多边形边
    if (m_vertices.size() > 1) {
        CPen edgePen(PS_SOLID, 1, RGB(0, 0, 0));  // 黑色
        pDC->SelectObject(&edgePen);

        // 绘制已有的边
        pDC->MoveTo(m_vertices[0].x, m_vertices[0].y);
        for (size_t i = 1; i < m_vertices.size(); ++i) {
            pDC->LineTo(m_vertices[i].x, m_vertices[i].y);
        }

        // 如果多边形已闭合且顶点数大于2，连接首尾顶点
        if (m_closed && m_vertices.size() > 2) {
            pDC->LineTo(m_vertices[0].x, m_vertices[0].y);
        }
    }

    // 4. 绘制填充点
    for (const auto& point : m_points) {
        pDC->SetPixel(point.x, point.y, m_color);
    }

    // 5. 绘制种子点（如果有）
    if (m_hasSeed) {
        DrawSeed(pDC, m_seed);
    }

    // 恢复原始画笔和画刷
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}

void Polygon::Transform(const Matrix3x3& matrix) {
    TransformVertices(matrix);
    // 如果已经生成了填充点，需要重新生成
    if (m_closed) {
        GeneratePoints();
    }
}

void Polygon::TransformVertices(const Matrix3x3& matrix) {
    for (auto& vertex : m_vertices) {
        vertex = TransformPoint(vertex, matrix);
    }
}