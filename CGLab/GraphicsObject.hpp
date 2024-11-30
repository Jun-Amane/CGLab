/*
 *
 * Models/GraphicsObject.hpp
 * Ziyu ZHOU @ SDAU
 * 26/11/24
 *
*/

#pragma once

#include "pch.h"
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
	class GraphicsObject {
	public:
		enum ObjectType {
			OT_NONE,
			OT_LINE,
			OT_CIRCLE,
			OT_ELLIPSE,
			OT_POLYGON
		};

		GraphicsObject(ObjectType type = OT_NONE)
			: m_type(type)
			, m_color(RGB(0, 0, 0))
			, m_width(1) {}

		virtual ~GraphicsObject() {}

		virtual void Draw(CDC* pDC) = 0;
		virtual void GeneratePoints() = 0;

	protected:
		ObjectType m_type;
		COLORREF m_color;
		int m_width;
	};


}
