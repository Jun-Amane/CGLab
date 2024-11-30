
/*
 * Algorithms/PolygonAlgorithms.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */

#pragma once
#include "IPolygonAlgorithm.hpp"

namespace MyGraphics {
    namespace Algorithms {
        class ScanLineFillAlgorithm : public IPolygonAlgorithm {
        public:
            std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices) override;
        };

        class SeedFill4Algorithm : public IPolygonAlgorithm {
        public:
            std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices, const Point2D& seed) override;
        };

        class SeedFill8Algorithm : public IPolygonAlgorithm {
        public:
            std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices, const Point2D& seed) override;
        };
    }
}

