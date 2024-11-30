/*
 *
 * Math/Transform3D.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 *
*/

#pragma once
#include "Point3D.hpp"
#include "Matrix4x4.hpp"

namespace MyGraphics {
    Point3D TransformPoint(const Point3D& p, const Matrix4x4& matrix);

    namespace Transform3D {
        // Æ½ÒÆ±ä»»¾ØÕó
        Matrix4x4 Translate(double dx, double dy, double dz);

        // Ðý×ª±ä»»¾ØÕó
        Matrix4x4 RotateX(double angle, const Point3D& center = Point3D(0, 0, 0));
        Matrix4x4 RotateY(double angle, const Point3D& center = Point3D(0, 0, 0));
        Matrix4x4 RotateZ(double angle, const Point3D& center = Point3D(0, 0, 0));

        // Ëõ·Å±ä»»¾ØÕó
        Matrix4x4 Scale(double sx, double sy, double sz, const Point3D& center = Point3D(0, 0, 0));
    }
}
