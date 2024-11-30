/*
*
* 文件: Models/Line.cpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 26/11/24
*
* 说明: 本文件实现了Line类,用于直线的生成和绘制
* 支持四种算法:
* 1. DDA直线生成算法(默认)
* 2. 中点直线生成算法
* 3. Bresenham直线生成算法
* 4. Cohen-Sutherland直线裁剪算法
*/

#include "pch.h"
#include "Line.hpp"
#include "LineAlgorithms.hpp"
#include "LineClipAlgorithms.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* Line类构造函数
* 初始化:
* - 图形类型为直线(OT_LINE)
* - 默认使用DDA算法
* - 创建DDA算法对象
*/
Line::Line()
    : GraphicsObject(OT_LINE)
    , m_algorithm(ALGO_DDA)
    , m_lineAlgorithm(std::make_unique<DDALineAlgorithm>())
{
}

/**
* 设置直线的生成/裁剪算法
* @param algo: 算法类型
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
        // Cohen-Sutherland算法需要两个组件:
        m_lineAlgorithm = std::make_unique<DDALineAlgorithm>();  // 用于绘制裁剪后的线段
        m_clipAlgorithm = std::make_unique<CohenSutherlandAlgorithm>();  // 用于裁剪计算
        break;
    }
}

/**
* 设置直线的起点和终点
* @param start: 起点坐标
* @param end: 终点坐标
*/
void Line::SetPoints(const Point2D& start, const Point2D& end) {
    m_startPoint = start;
    m_endPoint = end;
}

/**
* 生成构成直线的所有点
* 对于裁剪算法,先进行裁剪再生成点
*/
void Line::GeneratePoints() {
    if (m_algorithm == ALGO_COHEN_SUTHERLAND && m_clipAlgorithm) {
        // 保存原始端点用于绘制虚线
        m_clippedStart = m_startPoint;
        m_clippedEnd = m_endPoint;

        // 进行裁剪计算
        m_isClipped = m_clipAlgorithm->ClipLine(m_clippedStart, m_clippedEnd, m_clipWindow);

        if (m_isClipped) {
            // 使用裁剪后的端点生成直线点集
            m_points = m_lineAlgorithm->GeneratePoints(m_clippedStart, m_clippedEnd);
        }
        else {
            // 线段完全在窗口外,清空点集
            m_points.clear();
        }
    }
    else if (m_lineAlgorithm) {
        // 普通直线生成算法
        m_points = m_lineAlgorithm->GeneratePoints(m_startPoint, m_endPoint);
    }
}

/**
* 在指定设备上下文中绘制直线
* @param pDC: 设备上下文指针
*/
void Line::Draw(CDC* pDC) {
    // Cohen-Sutherland算法需要额外绘制裁剪窗口和原始线段
    if (m_algorithm == ALGO_COHEN_SUTHERLAND) {
        // 绘制裁剪窗口
        m_clipWindow.Draw(pDC);

        // 用绯红色虚线绘制原始线段
        CPen dashPen(PS_DASH, 1, RGB(255, 128, 128));
        CPen* pOldPen = pDC->SelectObject(&dashPen);
        pDC->MoveTo(m_startPoint.x, m_startPoint.y);
        pDC->LineTo(m_endPoint.x, m_endPoint.y);
        pDC->SelectObject(pOldPen);
    }

    // 绘制实际的线段点集
    for (const auto& point : m_points) {
        pDC->SetPixel(point.x, point.y, m_color);
    }
}