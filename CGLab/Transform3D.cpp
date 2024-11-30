/*
 *
 * 文件: Math/Transform3D.cpp
 * 作者: Ziyu ZHOU @ SDAU
 * 日期: 30/11/24
 *
 * 说明: 本文件实现了三维图形变换的相关函数
 * 包括:
 * 1. 三维点的矩阵变换
 * 2. 三维基本变换矩阵的生成
 *   - 平移变换
 *   - 旋转变换(绕x轴、y轴、z轴)
 *   - 缩放变换
 */

#include "pch.h"
#include "Transform3D.hpp"

using namespace MyGraphics;

/**
 * 对三维点进行矩阵变换
 * 实现方式：将点的坐标与变换矩阵相乘，并处理齐次坐标
 */
Point3D MyGraphics::TransformPoint(const Point3D& p, const Matrix4x4& matrix) {
    const auto& m = matrix.GetData();
    // 计算变换后的齐次坐标
    double x = p.x * m[0][0] + p.y * m[0][1] + p.z * m[0][2] + m[0][3];
    double y = p.x * m[1][0] + p.y * m[1][1] + p.z * m[1][2] + m[1][3];
    double z = p.x * m[2][0] + p.y * m[2][1] + p.z * m[2][2] + m[2][3];
    double w = p.x * m[3][0] + p.y * m[3][1] + p.z * m[3][2] + m[3][3];

    // 将齐次坐标转换回三维坐标
    if (w != 0) {
        x /= w;
        y /= w;
        z /= w;
    }

    // 对结果进行四舍五入并返回
    return Point3D(static_cast<double>(round(x)),
        static_cast<double>(round(y)),
        static_cast<double>(round(z)));
}

/**
 * 生成三维平移变换矩阵
 * 通过设置矩阵最后一列的平移量实现
 */
Matrix4x4 Transform3D::Translate(double dx, double dy, double dz) {
    Matrix4x4 m;  // 默认构造单位矩阵
    m.Set(0, 3, dx);  // 设置x方向平移量
    m.Set(1, 3, dy);  // 设置y方向平移量
    m.Set(2, 3, dz);  // 设置z方向平移量
    return m;
}

/**
 * 生成三维缩放变换矩阵
 * 实现方式：将对象先平移到原点，进行缩放后再平移回原位置
 */
Matrix4x4 Transform3D::Scale(double sx, double sy, double sz, const Point3D& center) {
    // 第一步：平移到原点
    Matrix4x4 t1 = Translate(-center.x, -center.y, -center.z);

    // 第二步：构造基本缩放矩阵
    Matrix4x4 s;
    s.Set(0, 0, sx);  // x方向缩放系数
    s.Set(1, 1, sy);  // y方向缩放系数
    s.Set(2, 2, sz);  // z方向缩放系数

    // 第三步：平移回原位置
    Matrix4x4 t2 = Translate(center.x, center.y, center.z);

    // 返回变换矩阵的组合
    return t2 * s * t1;
}

/**
 * 生成绕x轴旋转的变换矩阵
 * 实现方式：将对象先平移到原点，绕x轴旋转后再平移回原位置
 */
Matrix4x4 Transform3D::RotateX(double angle, const Point3D& center) {
    // 第一步：平移到原点
    Matrix4x4 t1 = Translate(-center.x, -center.y, -center.z);

    // 将角度转换为弧度并计算三角函数值
    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    // 第二步：构造绕x轴旋转矩阵
    Matrix4x4 r;
    r.Set(1, 1, cosA);  r.Set(1, 2, -sinA);
    r.Set(2, 1, sinA);  r.Set(2, 2, cosA);

    // 第三步：平移回原位置
    Matrix4x4 t2 = Translate(center.x, center.y, center.z);

    return t2 * r * t1;
}

/**
 * 生成绕y轴旋转的变换矩阵
 * 实现方式：将对象先平移到原点，绕y轴旋转后再平移回原位置
 */
Matrix4x4 Transform3D::RotateY(double angle, const Point3D& center) {
    Matrix4x4 t1 = Translate(-center.x, -center.y, -center.z);

    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    // 构造绕y轴旋转矩阵
    Matrix4x4 r;
    r.Set(0, 0, cosA);  r.Set(0, 2, sinA);
    r.Set(2, 0, -sinA); r.Set(2, 2, cosA);

    Matrix4x4 t2 = Translate(center.x, center.y, center.z);

    return t2 * r * t1;
}

/**
 * 生成绕z轴旋转的变换矩阵
 * 实现方式：将对象先平移到原点，绕z轴旋转后再平移回原位置
 */
Matrix4x4 Transform3D::RotateZ(double angle, const Point3D& center) {
    Matrix4x4 t1 = Translate(-center.x, -center.y, -center.z);

    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    // 构造绕z轴旋转矩阵
    Matrix4x4 r;
    r.Set(0, 0, cosA);  r.Set(0, 1, -sinA);
    r.Set(1, 0, sinA);  r.Set(1, 1, cosA);

    Matrix4x4 t2 = Translate(center.x, center.y, center.z);

    return t2 * r * t1;
}
