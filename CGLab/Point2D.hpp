/*
 *
 * Math/Point2D.hpp
 * Ziyu ZHOU @ SDAU
 * 26/11/24
 *
*/

#pragma once

namespace MyGraphics {
	class Point2D {
	public:
		int x;
		int y;

		Point2D(int x = 0, int y = 0) : x(x), y(y) {}

		bool operator==(const Point2D& other) const {
			return x == other.x && y == other.y;
		}

		bool operator!=(const Point2D& other) const {
			return x != other.x || y != other.y;
		}
	};


}
