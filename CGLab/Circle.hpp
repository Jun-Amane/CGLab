/*
 *
 * Models/Circle.hpp
 * Ziyu ZHOU @ SDAU
 * 27/11/24
 *
*/

#pragma once
#include "Point2D.hpp"
#include "GraphicsObject.hpp"
#include "ICircleAlgorithm.hpp"
#include <memory>

namespace MyGraphics {
	class Circle : public GraphicsObject {
	public:
		enum Algorithm {
			ALGO_MIDPOINT,
			ALGO_BRESENHAM
		};

		Circle();
		~Circle() override = default;

		void SetAlgorithm(Algorithm algo);
		void SetParameters(const Point2D& centre, int radius);
		void GeneratePoints();
		void Draw(CDC* pDC) override;

	private:
		Algorithm m_algorithm;
		Point2D m_centre;
		int m_radius;
		std::vector<Point2D> m_points;
		std::unique_ptr<Algorithms::ICircleAlgorithm> m_circleAlgorithm;
	};

}
