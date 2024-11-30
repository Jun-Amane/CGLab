/*
*
* 文件: Algorithms/PolygonAlgorithms.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件声明了三种多边形填充算法的类:
* 1. ScanLineFillAlgorithm - X扫描线填充算法
* 2. SeedFill4Algorithm - 四邻域种子填充算法
* 3. SeedFill8Algorithm - 八邻域种子填充算法
* 所有算法类都继承自IPolygonAlgorithm接口
*/

#pragma once
#include "IPolygonAlgorithm.hpp"

namespace MyGraphics {
    namespace Algorithms {
        /**
         * X扫描线填充算法类
         * 通过从下到上逐行扫描的方式对多边形进行填充
         */
        class ScanLineFillAlgorithm : public IPolygonAlgorithm {
        public:
            /**
             * 生成填充用的像素点集
             * @param vertices: 多边形顶点数组
             * @return: 返回所有填充点的坐标集合
             */
            std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices) override;
        };

        /**
         * 四邻域种子填充算法类
         * 从种子点开始,向上下左右四个方向扩展填充
         */
        class SeedFill4Algorithm : public IPolygonAlgorithm {
        public:
            /**
             * 生成填充用的像素点集
             * @param vertices: 多边形顶点数组
             * @param seed: 种子点坐标
             * @return: 返回所有填充点的坐标集合
             */
            std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices, const Point2D& seed) override;
        };

        /**
         * 八邻域种子填充算法类
         * 从种子点开始,向周围八个方向扩展填充
         */
        class SeedFill8Algorithm : public IPolygonAlgorithm {
        public:
            /**
             * 生成填充用的像素点集
             * @param vertices: 多边形顶点数组
             * @param seed: 种子点坐标
             * @return: 返回所有填充点的坐标集合
             */
            std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices, const Point2D& seed) override;
        };
    }
}