/*
 *
 * Algorithms/LineClipAlgorithms.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 *
*/


#pragma once
#include "ILineClipAlgorithm.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

class CohenSutherlandAlgorithm : public ILineClipAlgorithm {
public:
    bool ClipLine(Point2D& start, Point2D& end, const ClipWindow& window) override;
};
