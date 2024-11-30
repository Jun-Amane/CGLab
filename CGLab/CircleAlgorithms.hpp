/*
 *
 * 文件名: Algorithms/CircleAlgorithms.hpp
 * 作者: Ziyu ZHOU @ SDAU
 * 日期: 27/11/24
 *
 * 说明: 本文件声明了圆生成算法的具体实现类
 * 包括中点圆算法和Bresenham圆算法两种实现
 * 两个类都继承自ICircleAlgorithm接口类
 */

#pragma once
#include "ICircleAlgorithm.hpp"

namespace MyGraphics {
    namespace Algorithms {

        /**
         * 中点圆生成算法类
         * 使用中点算法生成圆上的像素点
         * 通过判断中点与圆的位置关系来选择下一个像素点
         */
        class MidpointCircleAlgorithm : public ICircleAlgorithm {
        public:
            /**
             * 生成圆上的所有点坐标
             * @param centre 圆心坐标
             * @param radius 圆的半径
             * @return 返回圆上所有点的坐标集合
             */
            std::vector<Point2D> GeneratePoints(const Point2D& centre, int radius) override;

        private:
            /**
             * 利用圆的八分对称性生成对称点
             * @param points 存储生成点的向量
             * @param center 圆心坐标
             * @param x 当前点的x偏移量
             * @param y 当前点的y偏移量
             */
            void AddCirclePoints(std::vector<Point2D>& points, const Point2D& center, int x, int y);
        };

        /**
         * Bresenham圆生成算法类
         * 使用Bresenham算法生成圆上的像素点
         * 通过误差项的累计来选择下一个像素点,避免浮点运算
         */
        class BresenhamCircleAlgorithm : public ICircleAlgorithm {
        public:
            /**
             * 生成圆上的所有点坐标
             * @param centre 圆心坐标
             * @param radius 圆的半径
             * @return 返回圆上所有点的坐标集合
             */
            std::vector<Point2D> GeneratePoints(const Point2D& centre, int radius) override;

        private:
            /**
             * 利用圆的八分对称性生成对称点
             * @param points 存储生成点的向量
             * @param center 圆心坐标
             * @param x 当前点的x偏移量
             * @param y 当前点的y偏移量
             */
            void AddCirclePoints(std::vector<Point2D>& points, const Point2D& center, int x, int y);
        };

    } // namespace Algorithms
} // namespace MyGraphics