/*
*
* �ļ�: Models/Line.cpp
* ����: Ziyu ZHOU @ SDAU
* ����: 26/11/24
*
* ˵��: ���ļ�ʵ����Line��,����ֱ�ߵ����ɺͻ���
* ֧�������㷨:
* 1. DDAֱ�������㷨(Ĭ��)
* 2. �е�ֱ�������㷨
* 3. Bresenhamֱ�������㷨
* 4. Cohen-Sutherlandֱ�߲ü��㷨
*/

#include "pch.h"
#include "Line.hpp"
#include "LineAlgorithms.hpp"
#include "LineClipAlgorithms.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* Line�๹�캯��
* ��ʼ��:
* - ͼ������Ϊֱ��(OT_LINE)
* - Ĭ��ʹ��DDA�㷨
* - ����DDA�㷨����
*/
Line::Line()
    : GraphicsObject(OT_LINE)
    , m_algorithm(ALGO_DDA)
    , m_lineAlgorithm(std::make_unique<DDALineAlgorithm>())
{
}

/**
* ����ֱ�ߵ�����/�ü��㷨
* @param algo: �㷨����
*/
void Line::SetAlgorithm(Algorithm algo) {
    m_algorithm = algo;
    switch (algo) {
    case ALGO_DDA:
        m_lineAlgorithm = std::make_unique<DDALineAlgorithm>();
        break;
    case ALGO_MIDPOINT:
        m_lineAlgorithm = std::make_unique<MidpointLineAlgorithm>();
        break;
    case ALGO_BRESENHAM:
        m_lineAlgorithm = std::make_unique<BresenhamLineAlgorithm>();
    case ALGO_COHEN_SUTHERLAND:
        // Cohen-Sutherland�㷨��Ҫ�������:
        m_lineAlgorithm = std::make_unique<DDALineAlgorithm>();  // ���ڻ��Ʋü�����߶�
        m_clipAlgorithm = std::make_unique<CohenSutherlandAlgorithm>();  // ���ڲü�����
        break;
    }
}

/**
* ����ֱ�ߵ������յ�
* @param start: �������
* @param end: �յ�����
*/
void Line::SetPoints(const Point2D& start, const Point2D& end) {
    m_startPoint = start;
    m_endPoint = end;
}

/**
* ���ɹ���ֱ�ߵ����е�
* ���ڲü��㷨,�Ƚ��вü������ɵ�
*/
void Line::GeneratePoints() {
    if (m_algorithm == ALGO_COHEN_SUTHERLAND && m_clipAlgorithm) {
        // ����ԭʼ�˵����ڻ�������
        m_clippedStart = m_startPoint;
        m_clippedEnd = m_endPoint;

        // ���вü�����
        m_isClipped = m_clipAlgorithm->ClipLine(m_clippedStart, m_clippedEnd, m_clipWindow);

        if (m_isClipped) {
            // ʹ�òü���Ķ˵�����ֱ�ߵ㼯
            m_points = m_lineAlgorithm->GeneratePoints(m_clippedStart, m_clippedEnd);
        }
        else {
            // �߶���ȫ�ڴ�����,��յ㼯
            m_points.clear();
        }
    }
    else if (m_lineAlgorithm) {
        // ��ֱͨ�������㷨
        m_points = m_lineAlgorithm->GeneratePoints(m_startPoint, m_endPoint);
    }
}

/**
* ��ָ���豸�������л���ֱ��
* @param pDC: �豸������ָ��
*/
void Line::Draw(CDC* pDC) {
    // Cohen-Sutherland�㷨��Ҫ������Ʋü����ں�ԭʼ�߶�
    if (m_algorithm == ALGO_COHEN_SUTHERLAND) {
        // ���Ʋü�����
        m_clipWindow.Draw(pDC);

        // ��糺�ɫ���߻���ԭʼ�߶�
        CPen dashPen(PS_DASH, 1, RGB(255, 128, 128));
        CPen* pOldPen = pDC->SelectObject(&dashPen);
        pDC->MoveTo(m_startPoint.x, m_startPoint.y);
        pDC->LineTo(m_endPoint.x, m_endPoint.y);
        pDC->SelectObject(pOldPen);
    }

    // ����ʵ�ʵ��߶ε㼯
    for (const auto& point : m_points) {
        pDC->SetPixel(point.x, point.y, m_color);
    }
}