/*
 * 文件: Models/Frustum.cpp
 * 作者: Ziyu ZHOU @ SDAU
 * 日期: 30/11/24
 *
 * 说明: 本文件实现了Frustum类的构造函数，用于表示一个四棱台的三维几何模型。
 * 功能:
 * 1. 构造四棱台对象，并初始化其顶点和边数据。
 * 2. 四棱台的底面和顶面均为平行于X-Y平面的正方形。
 */

#include "pch.h"
#include "Frustum.hpp"

using namespace MyGraphics;

/**
 * Frustum类构造函数
 * @param baseSize: 底面正方形的边长
 * @param topSize: 顶面正方形的边长
 * @param height: 四棱台的高度
 *
 * 功能:
 * - 根据输入参数计算底面和顶面的半边长以及高度的中点。
 * - 初始化四棱台的顶点坐标和边的连接关系。
 */
Frustum::Frustum(double baseSize, double topSize, double height) {
    // 计算底面和顶面的半边长
    double baseHalf = baseSize / 2.0; // 底面边长的一半
    double topHalf = topSize / 2.0;  // 顶面边长的一半
    double halfHeight = height / 2.0; // 高度的一半，用于计算顶点的Y坐标

    // 定义8个顶点
    m_vertices = {
        // 底面的4个顶点 (底面平行于 X-Y 平面, Y = -halfHeight)
        {-baseHalf, -halfHeight, -baseHalf},  // 顶点0
        {baseHalf, -halfHeight, -baseHalf},   // 顶点1
        {baseHalf, -halfHeight, baseHalf},    // 顶点2
        {-baseHalf, -halfHeight, baseHalf},   // 顶点3

        // 顶面的4个顶点 (顶面平行于 X-Y 平面, Y = halfHeight)
        {-topHalf, halfHeight, -topHalf},     // 顶点4
        {topHalf, halfHeight, -topHalf},      // 顶点5
        {topHalf, halfHeight, topHalf},       // 顶点6
        {-topHalf, halfHeight, topHalf}       // 顶点7
    };

    // 定义四棱台的边 (通过顶点索引进行连接)
    m_edges = {
        // 底面边
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        // 顶面边
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        // 底面与顶面的连接边
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };
}
