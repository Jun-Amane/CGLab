/*
*
* 文件: Models/Ellipse.cpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 28/11/24
*
* 说明: 本文件实现了Ellipse类,用于椭圆的生成和绘制
* 当前支持:
* - Bresenham椭圆生成算法
*/

#include "pch.h"
#include "Ellipse.hpp"
#include "EllipseAlgorithms.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* Ellipse类构造函数
* 初始化:
* - 图形类型为椭圆(OT_ELLIPSE)
* - 默认使用Bresenham算法
* - 长轴和短轴初始化为0
* - 创建Bresenham算法对象
*/
Ellipse::Ellipse()
    : GraphicsObject(OT_ELLIPSE)
    , m_algorithm(ALGO_BRESENHAM)
    , m_a(0)  // 长轴初始化为0
    , m_b(0)  // 短轴初始化为0
    , m_ellipseAlgorithm(std::make_unique<BresenhamEllipseAlgorithm>())
{
}

/**
* 设置椭圆的生成算法
* @param algo: 算法类型(当前仅支持ALGO_BRESENHAM)
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
* 设置椭圆的基本参数
* @param center: 椭圆中心点坐标
* @param a: 椭圆长轴长度
* @param b: 椭圆短轴长度
*/
void Ellipse::SetParameters(const Point2D& center, int a, int b) {
    m_center = center;
    m_a = a;
    m_b = b;
}

/**
* 生成椭圆上的所有点
* 调用选定算法的GeneratePoints方法
*/
void Ellipse::GeneratePoints() {
    if (m_ellipseAlgorithm) {
        m_points = m_ellipseAlgorithm->GeneratePoints(m_center, m_a, m_b);
    }
}

/**
* 在指定设备上下文中绘制椭圆
* @param pDC: 设备上下文指针
* 通过遍历所有生成的点,依次用SetPixel绘制
*/
void Ellipse::Draw(CDC* pDC) {
    for (const auto& point : m_points) {
        pDC->SetPixel(point.x, point.y, m_color);
    }
}