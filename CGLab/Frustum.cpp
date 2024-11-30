/*
 * �ļ�: Models/Frustum.cpp
 * ����: Ziyu ZHOU @ SDAU
 * ����: 30/11/24
 *
 * ˵��: ���ļ�ʵ����Frustum��Ĺ��캯�������ڱ�ʾһ������̨����ά����ģ�͡�
 * ����:
 * 1. ��������̨���󣬲���ʼ���䶥��ͱ����ݡ�
 * 2. ����̨�ĵ���Ͷ����Ϊƽ����X-Yƽ��������Ρ�
 */

#include "pch.h"
#include "Frustum.hpp"

using namespace MyGraphics;

/**
 * Frustum�๹�캯��
 * @param baseSize: ���������εı߳�
 * @param topSize: ���������εı߳�
 * @param height: ����̨�ĸ߶�
 *
 * ����:
 * - ������������������Ͷ���İ�߳��Լ��߶ȵ��е㡣
 * - ��ʼ������̨�Ķ�������ͱߵ����ӹ�ϵ��
 */
Frustum::Frustum(double baseSize, double topSize, double height) {
    // �������Ͷ���İ�߳�
    double baseHalf = baseSize / 2.0; // ����߳���һ��
    double topHalf = topSize / 2.0;  // ����߳���һ��
    double halfHeight = height / 2.0; // �߶ȵ�һ�룬���ڼ��㶥���Y����

    // ����8������
    m_vertices = {
        // �����4������ (����ƽ���� X-Y ƽ��, Y = -halfHeight)
        {-baseHalf, -halfHeight, -baseHalf},  // ����0
        {baseHalf, -halfHeight, -baseHalf},   // ����1
        {baseHalf, -halfHeight, baseHalf},    // ����2
        {-baseHalf, -halfHeight, baseHalf},   // ����3

        // �����4������ (����ƽ���� X-Y ƽ��, Y = halfHeight)
        {-topHalf, halfHeight, -topHalf},     // ����4
        {topHalf, halfHeight, -topHalf},      // ����5
        {topHalf, halfHeight, topHalf},       // ����6
        {-topHalf, halfHeight, topHalf}       // ����7
    };

    // ��������̨�ı� (ͨ������������������)
    m_edges = {
        // �����
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        // �����
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        // �����붥������ӱ�
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };
}
