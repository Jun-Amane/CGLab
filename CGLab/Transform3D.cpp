/*
 *
 * Math/Transform3D.cpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 *
*/

#include "pch.h"
#include "Transform3D.hpp"

using namespace MyGraphics;

Point3D MyGraphics::TransformPoint(const Point3D& p, const Matrix4x4& matrix) {
    const auto& m = matrix.GetData();
    double x = p.x * m[0][0] + p.y * m[0][1] + p.z * m[0][2] + m[0][3];
    double y = p.x * m[1][0] + p.y * m[1][1] + p.z * m[1][2] + m[1][3];
    double z = p.x * m[2][0] + p.y * m[2][1] + p.z * m[2][2] + m[2][3];
    double w = p.x * m[3][0] + p.y * m[3][1] + p.z * m[3][2] + m[3][3];

    // 转回非齐次坐标
    if (w != 0) {
        x /= w;
        y /= w;
        z /= w;
    }

    return Point3D(static_cast<double>(round(x)),
        static_cast<double>(round(y)),
        static_cast<double>(round(z)));
}

Matrix4x4 Transform3D::Translate(double dx, double dy, double dz) {
    Matrix4x4 m;
    m.Set(0, 3, dx);
    m.Set(1, 3, dy);
    m.Set(2, 3, dz);
    return m;
}

Matrix4x4 Transform3D::Scale(double sx, double sy, double sz, const Point3D& center) {
    // 先平移到原点
    Matrix4x4 t1 = Translate(-center.x, -center.y, -center.z);

    // 缩放矩阵
    Matrix4x4 s;
    s.Set(0, 0, sx);
    s.Set(1, 1, sy);
    s.Set(2, 2, sz);

    // 平移回原位置
    Matrix4x4 t2 = Translate(center.x, center.y, center.z);

    return t2 * s * t1;
}

Matrix4x4 Transform3D::RotateX(double angle, const Point3D& center) {
    // 先平移到原点
    Matrix4x4 t1 = Translate(-center.x, -center.y, -center.z);

    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    // 旋转矩阵
    Matrix4x4 r;
    r.Set(1, 1, cosA);
    r.Set(1, 2, -sinA);
    r.Set(2, 1, sinA);
    r.Set(2, 2, cosA);

    // 平移回原位置
    Matrix4x4 t2 = Translate(center.x, center.y, center.z);

    return t2 * r * t1;
}

Matrix4x4 Transform3D::RotateY(double angle, const Point3D& center) {
    Matrix4x4 t1 = Translate(-center.x, -center.y, -center.z);

    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    Matrix4x4 r;
    r.Set(0, 0, cosA);
    r.Set(0, 2, sinA);
    r.Set(2, 0, -sinA);
    r.Set(2, 2, cosA);

    Matrix4x4 t2 = Translate(center.x, center.y, center.z);

    return t2 * r * t1;
}

Matrix4x4 Transform3D::RotateZ(double angle, const Point3D& center) {
    Matrix4x4 t1 = Translate(-center.x, -center.y, -center.z);

    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    Matrix4x4 r;
    r.Set(0, 0, cosA);
    r.Set(0, 1, -sinA);
    r.Set(1, 0, sinA);
    r.Set(1, 1, cosA);

    Matrix4x4 t2 = Translate(center.x, center.y, center.z);

    return t2 * r * t1;
}