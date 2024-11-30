/*
 *
 * Models/Frustum.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 * 
 */

#pragma once
#include "Object3D.hpp"

namespace MyGraphics {
    class Frustum : public Object3D {
    public:
        Frustum(double baseSize = 100.0, double topSize = 60.0, double height = 120.0);
        ~Frustum() override = default;
    };
}

