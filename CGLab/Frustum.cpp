/*
 *
 * Models/Frustum.cpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 * 
 */

#include "pch.h"
#include "Frustum.hpp"

using namespace MyGraphics;

Frustum::Frustum(double baseSize, double topSize, double height) {
    // �������Ͷ���İ�߳�
    double baseHalf = baseSize / 2.0;
    double topHalf = topSize / 2.0;
    double halfHeight = height / 2.0;

    // ����8������
    m_vertices = {
        // �����4������
        {-baseHalf, -halfHeight, -baseHalf},  // 0
        {baseHalf, -halfHeight, -baseHalf},   // 1
        {baseHalf, -halfHeight, baseHalf},    // 2
        {-baseHalf, -halfHeight, baseHalf},   // 3

        // �����4������
        {-topHalf, halfHeight, -topHalf},     // 4
        {topHalf, halfHeight, -topHalf},      // 5
        {topHalf, halfHeight, topHalf},       // 6
        {-topHalf, halfHeight, topHalf}       // 7
    };

    // �����
    m_edges = {
        // ����
        {0,1}, {1,2}, {2,3}, {3,0},
        // ����
        {4,5}, {5,6}, {6,7}, {7,4},
        // ���ӵ���Ͷ���ı�
        {0,4}, {1,5}, {2,6}, {3,7}
    };
}