/*
 *
 * Algorithms/ICircleAlgorithm.hpp
 * Ziyu ZHOU @ SDAU
 * 27/11/24
 *
*/

#pragma once
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
	namespace Algorithms {
		class ICircleAlgorithm {
		public:
			virtual ~ICircleAlgorithm() = default;
			virtual std::vector<Point2D> GeneratePoints(const Point2D& centre, int radius) = 0;
		};

	}
}

