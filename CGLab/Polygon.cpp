/*
*
* �ļ�: Models/Polygon.cpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�ʵ����Polygon��,���ڶ���ε����ɡ���䡢�ü��ͱ任
* ֧�ֵ��㷨:
* 1. ɨ��������㷨
* 2. ��������������㷨
* 3. ��������������㷨
* 4. Weiler-Atherton����βü��㷨
*/

#include "pch.h"
#include "Polygon.hpp"
#include "PolygonAlgorithms.hpp"
#include "WeilerAthertonAlgorithm.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* ������๹�캯��
* ��ʼ��:
* - ͼ������Ϊ�����(OT_POLYGON)
* - Ĭ��ʹ��ɨ��������㷨
* - �����δ�պ�
* - δ���вü�
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
* ���ö���εĴ����㷨
* @param algo: �㷨����
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
* ��Ӷ���ζ���
* @param point: �¶��������
* ���ڶ����δ�պ�ʱ������¶���
*/
void Polygon::AddVertex(const Point2D& point) {
    if (!m_closed) {
        m_vertices.push_back(point);
    }
}

/**
* �������ӵ�(������������㷨)
* @param seed: ���ӵ�����
*/
void Polygon::SetSeed(const Point2D& seed) {
    m_seed = seed;
    m_hasSeed = true;
}

/**
* �պ϶����
* �����������ڵ���3ʱ���ܱպ�
*/
void Polygon::Close() {
    if (m_vertices.size() >= 3) {
        m_closed = true;
    }
}

/**
* ����ѡ�����㷨���ɶ���εĵ㼯
* ����:
* - Weiler-Atherton�ü�
* - ɨ�������
* - �������
*/
void Polygon::GeneratePoints() {
    if (m_closed && m_polygonAlgorithm) {
        if (m_algorithm == ALGO_WEILER_ATHERTON) {
            // Weiler-Atherton�ü��㷨
            m_originalVertices = m_vertices;
            m_vertices = m_polygonAlgorithm->ClipPolygon(m_originalVertices, m_clipWindow);
            m_isClipped = true;
        }
        else if (m_algorithm == ALGO_SCANLINE) {
            // ɨ��������㷨
            m_points = m_polygonAlgorithm->GeneratePoints(m_vertices);
        }
        else {
            // ��������㷨
            m_points = m_polygonAlgorithm->GeneratePoints(m_vertices, m_seed);
        }
    }
}

/**
* ���ƶ���ζ���
* @param pDC: �豸������ָ��
* @param point: ��������
*/
void Polygon::DrawVertex(CDC* pDC, const Point2D& point) {
    pDC->Rectangle(point.x - VERTEX_SIZE, point.y - VERTEX_SIZE,
        point.x + VERTEX_SIZE, point.y + VERTEX_SIZE);
}

/**
* �������ӵ�
* @param pDC: �豸������ָ��
* @param point: ���ӵ�����
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
* ���������Ķ����
* @param pDC: �豸������ָ��
* ����˳��:
* 1. �ü�����(���ʹ�òü��㷨)
* 2. ����
* 3. ��
* 4. ����
* 5. ���ӵ�(�����)
*/
void Polygon::Draw(CDC* pDC) {
    // 1. ���Ʋü����ں�ԭʼ�����(���ʹ�òü��㷨)
    if (m_algorithm == ALGO_WEILER_ATHERTON) {
        m_clipWindow.Draw(pDC);
        if (!m_originalVertices.empty()) {
            CPen dashPen(PS_DASH, 1, RGB(255, 128, 128));
            CPen* pOldPen = pDC->SelectObject(&dashPen);
            // ����ԭʼ�����
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

    // 2. ���ƶ���
    CPen vertexPen(PS_SOLID, 1, RGB(0, 0, 255));
    CBrush vertexBrush(RGB(0, 0, 255));
    CPen* pOldPen = pDC->SelectObject(&vertexPen);
    CBrush* pOldBrush = pDC->SelectObject(&vertexBrush);
    for (const auto& vertex : m_vertices) {
        DrawVertex(pDC, vertex);
    }

    // 3. ���ƶ���α�
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

    // 4. ��������
    for (const auto& point : m_points) {
        pDC->SetPixel(point.x, point.y, m_color);
    }

    // 5. �������ӵ�
    if (m_hasSeed) {
        DrawSeed(pDC, m_seed);
    }

    // �ָ��豸������״̬
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOldBrush);
}

/**
* �Զ���ν��б任
* @param matrix: �任����
*/
void Polygon::Transform(const Matrix3x3& matrix) {
    TransformVertices(matrix);
    if (m_closed) {
        GeneratePoints();  // ������������
    }
}

/**
* �Զ���ζ���Ӧ�ñ任
* @param matrix: �任����
*/
void Polygon::TransformVertices(const Matrix3x3& matrix) {
    for (auto& vertex : m_vertices) {
        vertex = TransformPoint(vertex, matrix);
    }
}
