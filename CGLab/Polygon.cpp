/*
*
* 文件: Models/Polygon.cpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件实现了Polygon类,用于多边形的生成、填充、裁剪和变换
* 支持的算法:
* 1. 扫描线填充算法
* 2. 四邻域种子填充算法
* 3. 八邻域种子填充算法
* 4. Weiler-Atherton多边形裁剪算法
*/

#include "pch.h"
#include "Polygon.hpp"
#include "PolygonAlgorithms.hpp"
#include "WeilerAthertonAlgorithm.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* 多边形类构造函数
* 初始化:
* - 图形类型为多边形(OT_POLYGON)
* - 默认使用扫描线填充算法
* - 多边形未闭合
* - 未进行裁剪
*/
Polygon::Polygon()
    : GraphicsObject(OT_POLYGON)
    , m_algorithm(ALGO_SCANLINE)
    , m_closed(false)
    , m_isClipped(false)
    , m_polygonAlgorithm(std::make_unique<ScanLineFillAlgorithm>())
{
}

/**
* 设置多边形的处理算法
* @param algo: 算法类型
*/
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

/**
* 添加多边形顶点
* @param point: 新顶点的坐标
* 仅在多边形未闭合时可添加新顶点
*/
void Polygon::AddVertex(const Point2D& point) {
    if (!m_closed) {
        m_vertices.push_back(point);
    }
}

/**
* 设置种子点(用于种子填充算法)
* @param seed: 种子点坐标
*/
void Polygon::SetSeed(const Point2D& seed) {
    m_seed = seed;
    m_hasSeed = true;
}

/**
* 闭合多边形
* 当顶点数大于等于3时才能闭合
*/
void Polygon::Close() {
    if (m_vertices.size() >= 3) {
        m_closed = true;
    }
}

/**
* 根据选定的算法生成多边形的点集
* 包括:
* - Weiler-Atherton裁剪
* - 扫描线填充
* - 种子填充
*/
void Polygon::GeneratePoints() {
    if (m_closed && m_polygonAlgorithm) {
        if (m_algorithm == ALGO_WEILER_ATHERTON) {
            // Weiler-Atherton裁剪算法
            m_originalVertices = m_vertices;
            m_vertices = m_polygonAlgorithm->ClipPolygon(m_originalVertices, m_clipWindow);
            m_isClipped = true;
        }
        else if (m_algorithm == ALGO_SCANLINE) {
            // 扫描线填充算法
            m_points = m_polygonAlgorithm->GeneratePoints(m_vertices);
        }
        else {
            // 种子填充算法
            m_points = m_polygonAlgorithm->GeneratePoints(m_vertices, m_seed);
        }
    }
}

/**
* 绘制多边形顶点
* @param pDC: 设备上下文指针
* @param point: 顶点坐标
*/
void Polygon::DrawVertex(CDC* pDC, const Point2D& point) {
    pDC->Rectangle(point.x - VERTEX_SIZE, point.y - VERTEX_SIZE,
        point.x + VERTEX_SIZE, point.y + VERTEX_SIZE);
}

/**
* 绘制种子点
* @param pDC: 设备上下文指针
* @param point: 种子点坐标
*/
void Polygon::DrawSeed(CDC* pDC, const Point2D& point) {
    CPen seedPen(PS_SOLID, 2, RGB(255, 0, 0));
    CPen* pOldPen = pDC->SelectObject(&seedPen);

    pDC->MoveTo(point.x - SEED_SIZE, point.y);
    pDC->LineTo(point.x + SEED_SIZE, point.y);
    pDC->MoveTo(point.x, point.y - SEED_SIZE);
    pDC->LineTo(point.x, point.y + SEED_SIZE);

    pDC->SelectObject(pOldPen);
}

/**
* 绘制完整的多边形
* @param pDC: 设备上下文指针
* 绘制顺序:
* 1. 裁剪窗口(如果使用裁剪算法)
* 2. 顶点
* 3. 边
* 4. 填充点
* 5. 种子点(如果有)
*/
void Polygon::Draw(CDC* pDC) {
    // 1. 绘制裁剪窗口和原始多边形(如果使用裁剪算法)
    if (m_algorithm == ALGO_WEILER_ATHERTON) {
        m_clipWindow.Draw(pDC);
        if (!m_originalVertices.empty()) {
            CPen dashPen(PS_DASH, 1, RGB(255, 128, 128));
            CPen* pOldPen = pDC->SelectObject(&dashPen);
            // 绘制原始多边形
            pDC->MoveTo(m_originalVertices[0].x, m_originalVertices[0].y);
            for (size_t i = 1; i < m_originalVertices.size(); ++i) {
                pDC->LineTo(m_originalVertices[i].x, m_originalVertices[i].y);
            }
            if (m_closed && m_originalVertices.size() > 2) {
                pDC->LineTo(m_originalVertices[0].x, m_originalVertices[0].y);
            }
            pDC->SelectObject(pOldPen);
        }
    }

    // 2. 绘制顶点
    CPen vertexPen(PS_SOLID, 1, RGB(0, 0, 255));
    CBrush vertexBrush(RGB(0, 0, 255));
    CPen* pOldPen = pDC->SelectObject(&vertexPen);
    CBrush* pOldBrush = pDC->SelectObject(&vertexBrush);
    for (const auto& vertex : m_vertices) {
        DrawVertex(pDC, vertex);
    }

    // 3. 绘制多边形边
    if (m_vertices.size() > 1) {
        CPen edgePen(PS_SOLID, 1, RGB(0, 0, 0));
        pDC->SelectObject(&edgePen);
        pDC->MoveTo(m_vertices[0].x, m_vertices[0].y);
        for (size_t i = 1; i < m_vertices.size(); ++i) {
            pDC->LineTo(m_vertices[i].x, m_vertices[i].y);
        }
        if (m_closed && m_vertices.size() > 2) {
            pDC->LineTo(m_vertices[0].x, m_vertices[0].y);
        }
    }

    // 4. 绘制填充点
    for (const auto& point : m_points) {
        pDC->SetPixel(point.x, point.y, m_color);
    }

    // 5. 绘制种子点
    if (m_hasSeed) {
        DrawSeed(pDC, m_seed);
    }

    // 恢复设备上下文状态
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}

/**
* 对多边形进行变换
* @param matrix: 变换矩阵
*/
void Polygon::Transform(const Matrix3x3& matrix) {
    TransformVertices(matrix);
    if (m_closed) {
        GeneratePoints();  // 重新生成填充点
    }
}

/**
* 对多边形顶点应用变换
* @param matrix: 变换矩阵
*/
void Polygon::TransformVertices(const Matrix3x3& matrix) {
    for (auto& vertex : m_vertices) {
        vertex = TransformPoint(vertex, matrix);
    }
}
