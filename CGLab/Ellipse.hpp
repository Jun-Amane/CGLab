/*
*
* 文件: Models/Ellipse.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 28/11/24
*
* 说明: 本文件定义了Ellipse类,用于椭圆的生成和绘制
* 特点:
* 1. 继承自GraphicsObject基类
* 2. 目前仅支持Bresenham椭圆生成算法
* 3. 使用Strategy设计模式实现算法切换(为后续扩展算法做准备)
*/

#pragma once
#include "Point2D.hpp"
#include "GraphicsObject.hpp"
#include "IEllipseAlgorithm.hpp"
#include <memory>

namespace MyGraphics {
    /**
     * Ellipse类 - 椭圆图形对象
     * 继承自GraphicsObject基类
     */
    class Ellipse : public GraphicsObject {
    public:
        /**
         * 定义支持的椭圆生成算法类型
         * 目前仅支持Bresenham算法
         */
        enum Algorithm {
            ALGO_BRESENHAM    // Bresenham椭圆生成算法
        };

        // 构造和析构函数
        Ellipse();
        ~Ellipse() override = default;

        /**
         * 设置椭圆的生成算法
         * @param algo: 算法类型(当前仅支持ALGO_BRESENHAM)
         */
        void SetAlgorithm(Algorithm algo);

        /**
         * 设置椭圆的基本参数
         * @param center: 椭圆中心点坐标
         * @param a: 椭圆长轴长度(semi-major axis)
         * @param b: 椭圆短轴长度(semi-minor axis)
         */
        void SetParameters(const Point2D& center, int a, int b);

        /**
         * 生成椭圆上的所有点
         * 调用选定算法的GeneratePoints方法
         */
        void GeneratePoints();

        /**
         * 在指定设备上下文绘制椭圆
         * @param pDC: 设备上下文指针
         */
        void Draw(CDC* pDC) override;

    private:
        Algorithm m_algorithm;      // 当前使用的算法类型
        Point2D m_center;          // 椭圆中心点坐标
        int m_a;                   // 长轴长度(semi-major axis)
        int m_b;                   // 短轴长度(semi-minor axis)
        std::vector<Point2D> m_points;  // 存储椭圆上的所有点

        // 椭圆生成算法对象的智能指针
        // 使用Strategy模式实现算法切换
        std::unique_ptr<Algorithms::IEllipseAlgorithm> m_ellipseAlgorithm;
    };
}