/*
 *
 * Math/Point3D.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 *
*/

#pragma once

namespace MyGraphics {
    class Point3D {
    public:
        double x;
        double y;
        double z;

        Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

        bool operator==(const Point3D& other) const {
            return x == other.x && y == other.y && z == other.z;
        }

        bool operator!=(const Point3D& other) const {
            return x != other.x || y != other.y || z != other.z;
        }
    };
}