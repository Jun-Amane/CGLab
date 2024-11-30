/*
 *
 * Algorithms/CircleAlgorithms.hpp
 * Ziyu ZHOU @ SDAU
 * 27/11/24
 *
*/

#pragma once
#include "ICircleAlgorithm.hpp"

namespace MyGraphics {
	namespace Algorithms {
		class MidpointCircleAlgorithm : public ICircleAlgorithm {
		public:
			std::vector<Point2D> GeneratePoints(const Point2D& centre, int radius) override;
		private:
			void AddCirclePoints(std::vector<Point2D>& points, const Point2D& center, int x, int y);
		};

		class BresenhamCircleAlgorithm : public ICircleAlgorithm {
		public:
			std::vector<Point2D> GeneratePoints(const Point2D& centre, int radius) override;
		private:
			void AddCirclePoints(std::vector<Point2D>& points, const Point2D& center, int x, int y);
		};
	}

}
