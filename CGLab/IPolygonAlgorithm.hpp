/*
 * Algorithms/IPolygonAlgorithm.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */

#pragma once
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
    namespace Algorithms {
        class IPolygonAlgorithm {
        public:
            virtual ~IPolygonAlgorithm() = default;
            // 有无种子点的重载
            virtual std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices) {
                return std::vector<Point2D>();
            }
            virtual std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices, const Point2D& seed) {
                return std::vector<Point2D>();
            }
            // 点是否属于多边形内部
            bool isPointInPolygon(const Point2D& p, const std::vector<Point2D>& vertices);
        };
    }
}
