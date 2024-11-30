/*
 *
 * Algorithms/ILineClipAlgorithm.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 *
*/

#pragma once
#include "Point2D.hpp"
#include "ClipWindow.hpp"

namespace MyGraphics {
    namespace Algorithms {
        class ILineClipAlgorithm {
        public:
            virtual ~ILineClipAlgorithm() = default;
            virtual bool ClipLine(Point2D& start, Point2D& end, const ClipWindow& window) = 0;
        };

    }
}