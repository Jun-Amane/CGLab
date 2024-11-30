/*
*
* 文件名: Algorithms/EllipseAlgorithms.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 28/11/24
*
* 说明: 本文件声明了椭圆生成算法的具体实现类
* 实现了基于Bresenham算法的椭圆生成方法
*/

#pragma once
#include "IEllipseAlgorithm.hpp"

namespace MyGraphics {
    namespace Algorithms {

        /**
         * Bresenham椭圆生成算法类
         * 继承自IEllipseAlgorithm接口
         * 使用Bresenham算法的思想生成椭圆上的像素点
         * 将椭圆分为两个区域分别处理,并利用四分对称性
         */
        class BresenhamEllipseAlgorithm : public IEllipseAlgorithm {
        public:
            /**
             * 生成椭圆上的所有点坐标
             * @param center 椭圆中心点坐标
             * @param a 椭圆长轴长度
             * @param b 椭圆短轴长度
             * @return 返回椭圆上所有点的坐标集合
             */
            std::vector<Point2D> GeneratePoints(const Point2D& center, int a, int b) override;

        private:
            /**
             * 利用椭圆的四分对称性生成对称点
             * @param points 存储生成点的向量
             * @param center 椭圆中心点坐标
             * @param x 当前点的x偏移量
             * @param y 当前点的y偏移量
             */
            void AddPoints(std::vector<Point2D>& points, const Point2D& center, int x, int y);
        };

    } // namespace Algorithms
} // namespace MyGraphics