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
    // 计算底面和顶面的半边长
    double baseHalf = baseSize / 2.0;
    double topHalf = topSize / 2.0;
    double halfHeight = height / 2.0;

    // 定义8个顶点
    m_vertices = {
        // 底面的4个顶点
        {-baseHalf, -halfHeight, -baseHalf},  // 0
        {baseHalf, -halfHeight, -baseHalf},   // 1
        {baseHalf, -halfHeight, baseHalf},    // 2
        {-baseHalf, -halfHeight, baseHalf},   // 3

        // 顶面的4个顶点
        {-topHalf, halfHeight, -topHalf},     // 4
        {topHalf, halfHeight, -topHalf},      // 5
        {topHalf, halfHeight, topHalf},       // 6
        {-topHalf, halfHeight, topHalf}       // 7
    };

    // 定义边
    m_edges = {
        // 底面
        {0,1}, {1,2}, {2,3}, {3,0},
        // 顶面
        {4,5}, {5,6}, {6,7}, {7,4},
        // 连接底面和顶面的边
        {0,4}, {1,5}, {2,6}, {3,7}
    };
}