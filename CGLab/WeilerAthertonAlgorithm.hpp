/*
*
* 文件: Algorithms/WeilerAthertonAlgorithm.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件声明了Weiler-Atherton多边形裁剪算法类
* 该算法主要用于裁剪多边形,通过递归细分的方式处理多边形的每条边
* 使用区域编码来确定点与裁剪窗口的相对位置关系
*/

#pragma once
#include "Point2D.hpp"
#include "IPolygonAlgorithm.hpp" 
#include "ClipWindow.hpp"
#include <list>

namespace MyGraphics {
    namespace Algorithms {
        /**
         * Weiler-Atherton多边形裁剪算法类
         * 继承自IPolygonAlgorithm接口
         */
        class WeilerAthertonAlgorithm : public IPolygonAlgorithm {
        public:
            /**
             * 对多边形进行裁剪的主函数
             * @param vertices: 输入多边形的顶点数组
             * @param window: 裁剪窗口
             * @return: 返回裁剪后的多边形顶点数组
             */
            std::vector<Point2D> ClipPolygon(
                const std::vector<Point2D>& vertices,
                const ClipWindow& window) override;

        private:
            // 区域编码常量定义
            static const int CODE_C = 0x0000;  // 内部区域编码:0000
            static const int CODE_N = 0x0008;  // 北方区域编码:1000
            static const int CODE_S = 0x0004;  // 南方区域编码:0100
            static const int CODE_E = 0x0002;  // 东方区域编码:0010 
            static const int CODE_W = 0x0001;  // 西方区域编码:0001

            /**
             * 计算点的区域编码
             * @param point: 待编码的点
             * @param window: 裁剪窗口
             * @return: 返回点的区域编码
             */
            int ComputeCode(const Point2D& point, const ClipWindow& window);

            /**
             * 处理一条边的裁剪
             * @param start: 边的起点
             * @param end: 边的终点
             * @param window: 裁剪窗口
             * @param result: 存储裁剪结果的点集
             */
            void ClipEdge(const Point2D& start, const Point2D& end,
                const ClipWindow& window,
                std::vector<Point2D>& result);

            /**
             * 计算边与窗口边界的交点
             * @param p1: 边的起点
             * @param p2: 边的终点
             * @param edge_code: 边界编码
             * @param window: 裁剪窗口
             * @return: 返回交点坐标
             */
            Point2D ComputeIntersection(
                const Point2D& p1, const Point2D& p2,
                int edge_code, const ClipWindow& window);
        };
    }
}