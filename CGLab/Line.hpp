/*
 *
 * Models/Line.hpp
 * Ziyu ZHOU @ SDAU
 * 26/11/24
 *
*/

#pragma once
#include "Point2D.hpp"
#include "GraphicsObject.hpp"
#include "ILineAlgorithm.hpp"
#include <memory>

namespace MyGraphics {
	class Line : public GraphicsObject {
	public:
		enum Algorithm {
			ALGO_DDA,
			ALGO_MIDPOINT,
			ALGO_BRESENHAM
		};

		Line();
		~Line() override = default;

		// �����㷨
		void SetAlgorithm(Algorithm algo);
		// ���������յ�
		void SetPoints(const Point2D& start, const Point2D& end);

		// ���ɵ㼯
		void GeneratePoints();
		// ����
		void Draw(CDC* pDC) override;

	private:
		Algorithm m_algorithm;
		Point2D m_startPoint;
		Point2D m_endPoint;
		std::vector<Point2D> m_points;
		std::unique_ptr<Algorithms::ILineAlgorithm> m_lineAlgorithm;
	};


}
