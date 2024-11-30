/*
*
* 文件名: Algorithms/LineAlgorithms.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 26/11/24
*
* 说明: 本文件声明了三种直线生成算法的具体实现类
* 所有类都继承自ILineAlgorithm接口
*/

#pragma once
#include "ILineAlgorithm.hpp"

namespace MyGraphics {
    namespace Algorithms {

        /**
         * DDA直线生成算法类
         * Digital Differential Analyzer(数值微分分析法)
         * 使用浮点数运算,实现简单但效率较低
         */
        class DDALineAlgorithm : public ILineAlgorithm {
        public:
            /**
             * 生成直线上的所有点
             * @param start 直线起点
             * @param end 直线终点
             * @return 返回直线上所有点的坐标集合
             */
            std::vector<Point2D> GeneratePoints(const Point2D& start, const Point2D& end) override;
        };

        /**
         * 中点直线生成算法类
         * 基于中点判别的思想,使用整数运算
         * 效率高于DDA算法
         */
        class MidpointLineAlgorithm : public ILineAlgorithm {
        public:
            /**
             * 生成直线上的所有点
             * @param start 直线起点
             * @param end 直线终点
             * @return 返回直线上所有点的坐标集合
             */
            std::vector<Point2D> GeneratePoints(const Point2D& start, const Point2D& end) override;
        };

        /**
         * Bresenham直线生成算法类
         * 使用误差累积的思想,完全使用整数运算
         * 是最高效的直线生成算法之一
         */
        class BresenhamLineAlgorithm : public ILineAlgorithm {
        public:
            /**
             * 生成直线上的所有点
             * @param start 直线起点
             * @param end 直线终点
             * @return 返回直线上所有点的坐标集合
             */
            std::vector<Point2D> GeneratePoints(const Point2D& start, const Point2D& end) override;
        };

    } // namespace Algorithms
} // namespace MyGraphics