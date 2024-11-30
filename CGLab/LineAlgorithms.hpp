/*
 *
 * Algorithms/LineAlgorithms.hpp
 * Ziyu ZHOU @ SDAU
 * 26/11/24
 *
*/

#pragma once
#include "ILineAlgorithm.hpp"

namespace MyGraphics {
	namespace Algorithms {
		class DDALineAlgorithm : public ILineAlgorithm {
		public:
			std::vector<Point2D> GeneratePoints(const Point2D& start, const Point2D& end) override;
		};

		class MidpointLineAlgorithm : public ILineAlgorithm {
		public:
			std::vector<Point2D> GeneratePoints(const Point2D& start, const Point2D& end) override;
		};

		class BresenhamLineAlgorithm : public ILineAlgorithm {
		public:
			std::vector<Point2D> GeneratePoints(const Point2D& start, const Point2D& end) override;
		};


	}
}

