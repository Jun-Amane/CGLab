/*
*
* �ļ�: Models/Circle.cpp
* ����: Ziyu ZHOU @ SDAU
* ����: 27/11/24
*
* ˵��: ���ļ�ʵ����Circle��,����Բ�����ɺͻ���
* ֧�����������㷨:
* 1. �е�Բ�����㷨
* 2. BresenhamԲ�����㷨
*/

#include "pch.h"
#include "Circle.hpp"
#include "CircleAlgorithms.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* Circle�๹�캯��
* ��ʼ��:
* - ͼ������ΪԲ��(OT_CIRCLE)
* - Ĭ��ʹ���е������㷨
* - �뾶��ʼ��Ϊ0
* - �����е��㷨����
*/
Circle::Circle()
    : GraphicsObject(OT_CIRCLE)
    , m_algorithm(ALGO_MIDPOINT)
    , m_radius(0)
    , m_circleAlgorithm(std::make_unique<MidpointCircleAlgorithm>())
{
}

/**
* ����Բ�������㷨
* @param algo: �㷨����(ALGO_MIDPOINT��ALGO_BRESENHAM)
*/
void Circle::SetAlgorithm(Algorithm algo) {
    m_algorithm = algo;
    switch (algo) {
    case ALGO_MIDPOINT:
        m_circleAlgorithm = std::make_unique<MidpointCircleAlgorithm>();
        break;
    case ALGO_BRESENHAM:
        m_circleAlgorithm = std::make_unique<BresenhamCircleAlgorithm>();
        break;
    }
}

/**
* ����Բ�Ĳ���
* @param centre: Բ������
* @param radius: Բ�İ뾶
*/
void Circle::SetParameters(const Point2D& centre, int radius) {
    m_centre = centre;
    m_radius = radius;
}

/**
* ʹ��ѡ�����㷨����Բ�ϵĵ�
* ����㷨�������,�������GeneratePoints�������ɵ㼯
*/
void Circle::GeneratePoints() {
    if (m_circleAlgorithm) {
        m_points = m_circleAlgorithm->GeneratePoints(m_centre, m_radius);
    }
}

/**
* ��ָ���豸�������л���Բ
* @param pDC: �豸������ָ��
* ͨ�������������ɵĵ�,������SetPixel����
*/
void Circle::Draw(CDC* pDC) {
    for (const auto& point : m_points) {
        pDC->SetPixel(point.x, point.y, m_color);
    }
}