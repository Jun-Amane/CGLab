/*
 * Math/Transform2D.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */

#pragma once
#include "Point2D.hpp"
#include "Matrix3x3.hpp"

namespace MyGraphics {
    // 点的变换函数声明
    Point2D TransformPoint(const Point2D& p, const Matrix3x3& matrix);

    namespace Transform {
        // 平移变换矩阵
        Matrix3x3 Translate(int dx, int dy);

        // 旋转变换矩阵（角度制）
        Matrix3x3 Rotate(double angle, const Point2D& center = Point2D(0, 0));

        // 错切变换矩阵
        Matrix3x3 Shear(double shx, double shy);

        // 缩放变换矩阵
        Matrix3x3 Scale(double sx, double sy, const Point2D& center = Point2D(0, 0));

        // 对称变换矩阵
        Matrix3x3 Reflect(double k, double b);  // 关于直线y=kx+b对称
        Matrix3x3 ReflectX();                   // 关于x轴对称
        Matrix3x3 ReflectY();                   // 关于y轴对称
    }
}