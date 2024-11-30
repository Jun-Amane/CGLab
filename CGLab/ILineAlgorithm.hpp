/*
*
* 文件名: Algorithms/ILineAlgorithm.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 26/11/24
*
* 说明: 本文件定义了直线生成算法的接口类
* 所有具体的直线生成算法都需要继承并实现该接口
*/

#pragma once
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
    namespace Algorithms {

        /**
         * 直线生成算法的抽象接口类
         * 定义了直线生成算法的标准接口
         * 提供了算法的多态性支持
         */
        class ILineAlgorithm {
        public:
            /**
             * 虚析构函数,确保正确的多态析构
             */
            virtual ~ILineAlgorithm() = default;

            /**
             * 纯虚函数,生成直线上的所有点
             * @param start 直线的起点坐标
             * @param end 直线的终点坐标
             * @return 返回直线上所有点的坐标集合
             */
            virtual std::vector<Point2D> GeneratePoints(const Point2D& start, const Point2D& end) = 0;
        };

    } // namespace Algorithms
} // namespace MyGraphics