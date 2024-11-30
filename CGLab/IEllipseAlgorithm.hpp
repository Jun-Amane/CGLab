/*
 *
 * Algorithms/IEllipseAlgorithm.hpp
 * Ziyu ZHOU @ SDAU
 * 28/11/24
 *
*/

#pragma once
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
	namespace Algorithms {
		class IEllipseAlgorithm {
		public:
			virtual ~IEllipseAlgorithm() = default;
			virtual std::vector<Point2D> GeneratePoints(const Point2D& center, int a, int b) = 0;
		};

	}
}

