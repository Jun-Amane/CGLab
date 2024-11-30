/*
 * Math/Transform2D.cpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */

#include "pch.h"
#include "Transform2D.hpp"

using namespace MyGraphics;

Point2D MyGraphics::TransformPoint(const Point2D& p, const Matrix3x3& matrix) {
    const auto& m = matrix.GetData();
    double x = p.x * m[0][0] + p.y * m[0][1] + m[0][2];
    double y = p.x * m[1][0] + p.y * m[1][1] + m[1][2];
    double w = p.x * m[2][0] + p.y * m[2][1] + m[2][2];

    // 转回非齐次坐标
    if (w != 0) {
        x /= w;
        y /= w;
    }

    return Point2D(static_cast<int>(round(x)), static_cast<int>(round(y)));
}

Matrix3x3 Transform::Translate(int dx, int dy) {
    Matrix3x3 m;
    m.Set(0, 2, dx);
    m.Set(1, 2, dy);
    return m;
}

Matrix3x3 Transform::Rotate(double angle, const Point2D& center) {
    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    // 先平移到原点
    Matrix3x3 t1 = Translate(-center.x, -center.y);

    // 旋转矩阵
    Matrix3x3 r;
    r.Set(0, 0, cosA);  r.Set(0, 1, -sinA);
    r.Set(1, 0, sinA);  r.Set(1, 1, cosA);

    // 平移回原位置
    Matrix3x3 t2 = Translate(center.x, center.y);

    return t2 * r * t1;
}

Matrix3x3 Transform::Shear(double shx, double shy) {
    Matrix3x3 m;
    m.Set(0, 1, shx);  // x方向错切
    m.Set(1, 0, shy);  // y方向错切
    return m;
}

Matrix3x3 Transform::Scale(double sx, double sy, const Point2D& center) {
    // 先平移到原点
    Matrix3x3 t1 = Translate(-center.x, -center.y);

    // 缩放矩阵
    Matrix3x3 s;
    s.Set(0, 0, sx);
    s.Set(1, 1, sy);

    // 平移回原位置
    Matrix3x3 t2 = Translate(center.x, center.y);

    return t2 * s * t1;
}

Matrix3x3 Transform::Reflect(double k, double b) {
    Matrix3x3 m;
    double k2 = k * k;
    double den = 1 + k2;

    m.Set(0, 0, (1 - k2) / den);
    m.Set(0, 1, 2 * k / den);
    m.Set(1, 0, 2 * k / den);
    m.Set(1, 1, (k2 - 1) / den);
    m.Set(0, 2, -2 * k * b / den);
    m.Set(1, 2, 2 * b / den);

    return m;
}

Matrix3x3 Transform::ReflectX() {
    Matrix3x3 m;
    m.Set(1, 1, -1);
    return m;
}

Matrix3x3 Transform::ReflectY() {
    Matrix3x3 m;
    m.Set(0, 0, -1);
    return m;
}