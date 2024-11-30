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
            // �������ӵ������
            virtual std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices) {
                return std::vector<Point2D>();
            }
            virtual std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices, const Point2D& seed) {
                return std::vector<Point2D>();
            }
            // ���Ƿ����ڶ�����ڲ�
            bool isPointInPolygon(const Point2D& p, const std::vector<Point2D>& vertices);
        };
    }
}
