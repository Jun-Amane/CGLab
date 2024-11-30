/*
 * Algorithms/WeilerAthertonAlgorithm.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */


#pragma once
#include "Point2D.hpp"
#include "IPolygonAlgorithm.hpp"
#include "ClipWindow.hpp"
#include <list>

namespace MyGraphics {
    namespace Algorithms {
        class WeilerAthertonAlgorithm : public IPolygonAlgorithm {
        public:
            std::vector<Point2D> ClipPolygon(
                const std::vector<Point2D>& vertices,
                const ClipWindow& window) override;

        private:
            // 定义区域编码
            static const int CODE_C = 0x0000;  // 内部
            static const int CODE_N = 0x0008;  // 北
            static const int CODE_S = 0x0004;  // 南
            static const int CODE_E = 0x0002;  // 东
            static const int CODE_W = 0x0001;  // 西

            // 计算点的区域编码
            int ComputeCode(const Point2D& point, const ClipWindow& window);
            
            // 处理一条边的裁剪
            void ClipEdge(const Point2D& start, const Point2D& end, 
                         const ClipWindow& window,
                         std::vector<Point2D>& result);

            // 计算交点
            Point2D ComputeIntersection(
                const Point2D& p1, const Point2D& p2,
                int edge_code, const ClipWindow& window);
        };
    }
}
