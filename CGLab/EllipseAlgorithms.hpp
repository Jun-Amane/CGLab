/*
 *
 * Algorithms/EllipseAlgorithms.hpp
 * Ziyu ZHOU @ SDAU
 * 28/11/24
 *
*/

#pragma once
#include "IEllipseAlgorithm.hpp"

namespace MyGraphics {
namespace Algorithms {
    class BresenhamEllipseAlgorithm : public IEllipseAlgorithm {
    public:
        std::vector<Point2D> GeneratePoints(const Point2D& center, int a, int b) override;
    private:
        void AddPoints(std::vector<Point2D>& points, const Point2D& center, int x, int y);
    };
}
}
