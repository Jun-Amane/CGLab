/*
*
* 文件: Models/Line.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 26/11/24
*
* 说明: 本文件定义了Line类,用于直线的生成和绘制
* 特点:
* 1. 继承自GraphicsObject基类
* 2. 支持三种生成算法和一种裁剪算法
* 3. 使用Strategy设计模式实现算法切换
*/

#pragma once
#include "Point2D.hpp"
#include "GraphicsObject.hpp"
#include "ILineAlgorithm.hpp"
#include "ILineClipAlgorithm.hpp"
#include "ClipWindow.hpp"
#include <memory>

namespace MyGraphics {
    /**
     * Line类 - 直线图形对象
     * 继承自GraphicsObject基类
     */
    class Line : public GraphicsObject {
    public:
        /**
         * 定义支持的直线生成和裁剪算法类型
         */
        enum Algorithm {
            ALGO_DDA,             // DDA直线生成算法
            ALGO_MIDPOINT,        // 中点直线生成算法
            ALGO_BRESENHAM,       // Bresenham直线生成算法
            ALGO_COHEN_SUTHERLAND // Cohen-Sutherland直线裁剪算法
        };

        // 构造和析构函数
        Line();
        ~Line() override = default;

        /**
         * 设置直线的生成或裁剪算法
         * @param algo: 选择的算法类型
         */
        void SetAlgorithm(Algorithm algo);

        /**
         * 设置直线的起点和终点
         * @param start: 起点坐标
         * @param end: 终点坐标
         */
        void SetPoints(const Point2D& start, const Point2D& end);

        /**
         * 设置裁剪窗口(用于Cohen-Sutherland算法)
         * @param window: 裁剪窗口对象
         */
        void SetClipWindow(const ClipWindow& window) { m_clipWindow = window; }

        /**
         * 根据选定算法生成直线的点集
         * 对于裁剪算法,会先进行裁剪计算
         */
        void GeneratePoints();

        /**
         * 在指定设备上下文绘制直线
         * @param pDC: 设备上下文指针
         */
        void Draw(CDC* pDC) override;

    private:
        Algorithm m_algorithm;      // 当前使用的算法类型
        Point2D m_startPoint;      // 原始起点
        Point2D m_endPoint;        // 原始终点
        Point2D m_clippedStart;    // 裁剪后的起点
        Point2D m_clippedEnd;      // 裁剪后的终点
        std::vector<Point2D> m_points;  // 存储直线上的所有点
        ClipWindow m_clipWindow;    // 裁剪窗口
        bool m_isClipped;          // 标记线段是否被裁剪

        // 使用Strategy模式实现的算法对象
        std::unique_ptr<Algorithms::ILineAlgorithm> m_lineAlgorithm;       // 直线生成算法
        std::unique_ptr<Algorithms::ILineClipAlgorithm> m_clipAlgorithm;   // 直线裁剪算法
    };
}
