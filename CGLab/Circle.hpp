/*
*
* 文件: Models/Circle.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 27/11/24
*
* 说明: 本文件定义了Circle类,用于圆的生成和绘制
* 特点:
* 1. 继承自GraphicsObject基类
* 2. 支持中点和Bresenham两种圆生成算法
* 3. 使用Strategy设计模式实现算法切换
*/

#pragma once
#include "Point2D.hpp"
#include "GraphicsObject.hpp"
#include "ICircleAlgorithm.hpp"
#include <memory>

namespace MyGraphics {
    /**
     * Circle类 - 圆形图形对象
     * 继承自GraphicsObject基类
     */
    class Circle : public GraphicsObject {
    public:
        /**
         * 定义支持的圆生成算法类型
         */
        enum Algorithm {
            ALGO_MIDPOINT,    // 中点圆生成算法
            ALGO_BRESENHAM    // Bresenham圆生成算法
        };

        // 构造和析构函数
        Circle();
        ~Circle() override = default;

        /**
         * 设置圆的生成算法
         * @param algo: 算法类型(ALGO_MIDPOINT或ALGO_BRESENHAM)
         */
        void SetAlgorithm(Algorithm algo);

        /**
         * 设置圆的基本参数
         * @param centre: 圆心坐标
         * @param radius: 圆的半径
         */
        void SetParameters(const Point2D& centre, int radius);

        /**
         * 生成圆上的所有点
         * 调用选定算法的GeneratePoints方法
         */
        void GeneratePoints();

        /**
         * 在指定设备上下文绘制圆
         * @param pDC: 设备上下文指针
         */
        void Draw(CDC* pDC) override;

    private:
        Algorithm m_algorithm;      // 当前使用的算法类型
        Point2D m_centre;          // 圆心坐标
        int m_radius;              // 圆的半径
        std::vector<Point2D> m_points;  // 存储圆上的所有点

        // 圆生成算法对象的智能指针
        // 使用Strategy模式实现算法切换
        std::unique_ptr<Algorithms::ICircleAlgorithm> m_circleAlgorithm;
    };
}