/*
*
* �ļ�: Models/Ellipse.cpp
* ����: Ziyu ZHOU @ SDAU
* ����: 28/11/24
*
* ˵��: ���ļ�ʵ����Ellipse��,������Բ�����ɺͻ���
* ��ǰ֧��:
* - Bresenham��Բ�����㷨
*/

#include "pch.h"
#include "Ellipse.hpp"
#include "EllipseAlgorithms.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* Ellipse�๹�캯��
* ��ʼ��:
* - ͼ������Ϊ��Բ(OT_ELLIPSE)
* - Ĭ��ʹ��Bresenham�㷨
* - ����Ͷ����ʼ��Ϊ0
* - ����Bresenham�㷨����
*/
Ellipse::Ellipse()
    : GraphicsObject(OT_ELLIPSE)
    , m_algorithm(ALGO_BRESENHAM)
    , m_a(0)  // �����ʼ��Ϊ0
    , m_b(0)  // �����ʼ��Ϊ0
    , m_ellipseAlgorithm(std::make_unique<BresenhamEllipseAlgorithm>())
{
}

/**
* ������Բ�������㷨
* @param algo: �㷨����(��ǰ��֧��ALGO_BRESENHAM)
*/
void Ellipse::SetAlgorithm(Algorithm algo) {
    m_algorithm = algo;
    switch (algo) {
    case ALGO_BRESENHAM:
        m_ellipseAlgorithm = std::make_unique<BresenhamEllipseAlgorithm>();
        break;
    }
}

/**
* ������Բ�Ļ�������
* @param center: ��Բ���ĵ�����
* @param a: ��Բ���᳤��
* @param b: ��Բ���᳤��
*/
void Ellipse::SetParameters(const Point2D& center, int a, int b) {
    m_center = center;
    m_a = a;
    m_b = b;
}

/**
* ������Բ�ϵ����е�
* ����ѡ���㷨��GeneratePoints����
*/
void Ellipse::GeneratePoints() {
    if (m_ellipseAlgorithm) {
        m_points = m_ellipseAlgorithm->GeneratePoints(m_center, m_a, m_b);
    }
}

/**
* ��ָ���豸�������л�����Բ
* @param pDC: �豸������ָ��
* ͨ�������������ɵĵ�,������SetPixel����
*/
void Ellipse::Draw(CDC* pDC) {
    for (const auto& point : m_points) {
        pDC->SetPixel(point.x, point.y, m_color);
    }
}