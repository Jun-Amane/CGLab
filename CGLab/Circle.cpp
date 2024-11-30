/*
*
* 文件: Models/Circle.cpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 27/11/24
*
* 说明: 本文件实现了Circle类,用于圆的生成和绘制
* 支持两种生成算法:
* 1. 中点圆生成算法
* 2. Bresenham圆生成算法
*/

#include "pch.h"
#include "Circle.hpp"
#include "CircleAlgorithms.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* Circle类构造函数
* 初始化:
* - 图形类型为圆形(OT_CIRCLE)
* - 默认使用中点生成算法
* - 半径初始化为0
* - 创建中点算法对象
*/
Circle::Circle()
    : GraphicsObject(OT_CIRCLE)
    , m_algorithm(ALGO_MIDPOINT)
    , m_radius(0)
    , m_circleAlgorithm(std::make_unique<MidpointCircleAlgorithm>())
{
}

/**
* 设置圆的生成算法
* @param algo: 算法类型(ALGO_MIDPOINT或ALGO_BRESENHAM)
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
* 设置圆的参数
* @param centre: 圆心坐标
* @param radius: 圆的半径
*/
void Circle::SetParameters(const Point2D& centre, int radius) {
    m_centre = centre;
    m_radius = radius;
}

/**
* 使用选定的算法生成圆上的点
* 如果算法对象存在,则调用其GeneratePoints方法生成点集
*/
void Circle::GeneratePoints() {
    if (m_circleAlgorithm) {
        m_points = m_circleAlgorithm->GeneratePoints(m_centre, m_radius);
    }
}

/**
* 在指定设备上下文中绘制圆
* @param pDC: 设备上下文指针
* 通过遍历所有生成的点,依次用SetPixel绘制
*/
void Circle::Draw(CDC* pDC) {
    for (const auto& point : m_points) {
        pDC->SetPixel(point.x, point.y, m_color);
    }
}