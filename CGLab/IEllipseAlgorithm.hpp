/*
*
* 文件名: Algorithms/IEllipseAlgorithm.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 28/11/24
*
* 说明: 本文件定义了椭圆生成算法的接口类
* 所有具体的椭圆生成算法都需要继承并实现该接口
*/

#pragma once
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
    namespace Algorithms {

        /**
         * 椭圆生成算法的抽象接口类
         * 定义了椭圆生成算法的标准接口
         * 提供了算法的多态性支持
         */
        class IEllipseAlgorithm {
        public:
            /**
             * 虚析构函数,确保正确的多态析构
             */
            virtual ~IEllipseAlgorithm() = default;

            /**
             * 纯虚函数,生成椭圆上的所有点
             * @param center 椭圆中心点的坐标
             * @param a 椭圆长轴的长度
             * @param b 椭圆短轴的长度
             * @return 返回椭圆上所有点的坐标集合
             */
            virtual std::vector<Point2D> GeneratePoints(const Point2D& center, int a, int b) = 0;
        };

    } // namespace Algorithms
} // namespace MyGraphics