/*
* 文件名: Algorithms/IPolygonAlgorithm.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件定义了多边形处理算法的基础接口类
* 包括多边形生成、填充和裁剪等相关算法
*/

#pragma once
#include "Point2D.hpp"
#include "ClipWindow.hpp"
#include <vector>

namespace MyGraphics {
    namespace Algorithms {

        /**
         * 多边形算法的抽象接口类
         * 提供了多边形处理相关的基础功能接口:
         * - 多边形生成和填充
         * - 点与多边形的位置关系判断
         * - 多边形裁剪
         */
        class IPolygonAlgorithm {
        public:
            /**
             * 虚析构函数,确保正确的多态析构
             */
            virtual ~IPolygonAlgorithm() = default;

            /**
             * 生成多边形上的点(无种子点版本)
             * 主要用于扫描线填充等不需要种子点的算法
             * @param vertices 多边形顶点数组
             * @return 返回多边形上所有点的坐标集合
             */
            virtual std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices) {
                return std::vector<Point2D>();
            }

            /**
             * 生成多边形上的点(有种子点版本)
             * 主要用于种子填充等需要种子点的算法
             * @param vertices 多边形顶点数组
             * @param seed 种子点坐标
             * @return 返回多边形上所有点的坐标集合
             */
            virtual std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices, const Point2D& seed) {
                return std::vector<Point2D>();
            }

            /**
             * 判断点是否在多边形内部
             * @param p 待判断的点
             * @param vertices 多边形顶点数组
             * @return true - 点在多边形内部
             *         false - 点在多边形外部或边界上
             */
            bool isPointInPolygon(const Point2D& p, const std::vector<Point2D>& vertices);

            /**
             * 对多边形进行裁剪
             * @param vertices 多边形顶点数组
             * @param window 裁剪窗口
             * @return 裁剪后的多边形顶点数组
             */
            virtual std::vector<Point2D> ClipPolygon(const std::vector<Point2D>& vertices, const ClipWindow& window) {
                return std::vector<Point2D>();
            }
        };

    } // namespace Algorithms
} // namespace MyGraphics