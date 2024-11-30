/*
 *
 * Models/Ellipse.hpp
 * Ziyu ZHOU @ SDAU
 * 28/11/24
 *
*/

#pragma once
#include "Point2D.hpp"
#include "GraphicsObject.hpp"
#include "IEllipseAlgorithm.hpp"
#include <memory>

namespace MyGraphics {
	class Ellipse : public GraphicsObject {
	public:
		enum Algorithm {
			ALGO_BRESENHAM
		};

		Ellipse();
		~Ellipse() override = default;

		void SetAlgorithm(Algorithm algo);
		void SetParameters(const Point2D& center, int a, int b);  // a�ǳ��ᣬb�Ƕ���
		void GeneratePoints();
		void Draw(CDC* pDC) override;

	private:
		Algorithm m_algorithm;
		Point2D m_center;
		int m_a;  // ����
		int m_b;  // ����
		std::vector<Point2D> m_points;
		std::unique_ptr<Algorithms::IEllipseAlgorithm> m_ellipseAlgorithm;
	};


}
