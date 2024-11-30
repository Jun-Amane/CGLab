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
#include "ILineClipAlgorithm.hpp"
#include "ClipWindow.hpp"
#include <memory>

namespace MyGraphics {
	class Line : public GraphicsObject {
	public:
		enum Algorithm {
			ALGO_DDA,
			ALGO_MIDPOINT,
			ALGO_BRESENHAM,
			ALGO_COHEN_SUTHERLAND
		};

		Line();
		~Line() override = default;

		// 设置算法
		void SetAlgorithm(Algorithm algo);
		// 设置起点和终点
		void SetPoints(const Point2D& start, const Point2D& end);

		void SetClipWindow(const ClipWindow& window) { m_clipWindow = window; }

		// 生成点集
		void GeneratePoints();
		// 绘制
		void Draw(CDC* pDC) override;


    private:
        Algorithm m_algorithm;
        Point2D m_startPoint;
        Point2D m_endPoint;
        Point2D m_clippedStart;  // 裁剪后的起点
        Point2D m_clippedEnd;    // 裁剪后的终点
        std::vector<Point2D> m_points;
        ClipWindow m_clipWindow;
        bool m_isClipped;       // 是否已被裁剪
        
        std::unique_ptr<Algorithms::ILineAlgorithm> m_lineAlgorithm;
        std::unique_ptr<Algorithms::ILineClipAlgorithm> m_clipAlgorithm;
	};


}
