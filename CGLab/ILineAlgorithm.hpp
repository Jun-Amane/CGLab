/*
 *
 * Algorithms/ILineAlgorithm.hpp
 * Ziyu ZHOU @ SDAU
 * 26/11/24
 *
*/

#pragma once
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
	namespace Algorithms {
		class ILineAlgorithm {
		public:
			virtual ~ILineAlgorithm() = default;
			virtual std::vector<Point2D> GeneratePoints(const Point2D& start, const Point2D& end) = 0;
		};


	}
}


