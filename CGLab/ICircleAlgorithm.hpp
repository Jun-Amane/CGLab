/*
*
* 文件名: Algorithms/ICircleAlgorithm.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 27/11/24
*
* 说明: 本文件定义了圆生成算法的接口类
* 所有具体的圆生成算法都需要继承并实现该接口
*/

#pragma once
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
    namespace Algorithms {

        /**
         * 圆生成算法的抽象接口类
         * 定义了圆生成算法的标准接口
         * 提供了算法的多态性支持
         */
        class ICircleAlgorithm {
        public:
            /**
             * 虚析构函数,确保正确的多态析构
             */
            virtual ~ICircleAlgorithm() = default;

            /**
             * 纯虚函数,生成圆上的所有点
             * @param centre 圆心坐标
             * @param radius 圆的半径
             * @return 返回圆上所有点的坐标集合
             */
            virtual std::vector<Point2D> GeneratePoints(const Point2D& centre, int radius) = 0;
        };

    } // namespace Algorithms
} // namespace MyGraphics