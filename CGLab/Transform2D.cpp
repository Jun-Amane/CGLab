/*
*
* 文件: Math/Transform2D.cpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件实现了二维图形变换的相关函数
* 主要包含:
* 1. 点的变换
* 2. 平移变换
* 3. 旋转变换
* 4. 错切变换
* 5. 缩放变换
* 6. 对称变换
* 所有变换都使用3x3齐次坐标矩阵实现
*/

#include "pch.h"
#include "Transform2D.hpp"

using namespace MyGraphics;

/**
* 对点进行矩阵变换
* @param p: 待变换的点
* @param matrix: 变换矩阵
* @return: 返回变换后的新点
*/
Point2D MyGraphics::TransformPoint(const Point2D& p, const Matrix3x3& matrix) {
    const auto& m = matrix.GetData();
    // 计算齐次坐标下的变换结果
    double x = p.x * m[0][0] + p.y * m[0][1] + m[0][2];
    double y = p.x * m[1][0] + p.y * m[1][1] + m[1][2];
    double w = p.x * m[2][0] + p.y * m[2][1] + m[2][2];

    // 将齐次坐标转回笛卡尔坐标
    if (w != 0) {
        x /= w;
        y /= w;
    }
    return Point2D(static_cast<int>(round(x)), static_cast<int>(round(y)));
}

/**
* 生成平移变换矩阵
* @param dx: x方向的位移量
* @param dy: y方向的位移量
* @return: 返回平移变换矩阵
*/
Matrix3x3 Transform::Translate(int dx, int dy) {
    Matrix3x3 m;
    m.Set(0, 2, dx);  // x方向平移量
    m.Set(1, 2, dy);  // y方向平移量
    return m;
}

/**
* 生成旋转变换矩阵
* @param angle: 旋转角度(度)
* @param center: 旋转中心点
* @return: 返回旋转变换矩阵
*/
Matrix3x3 Transform::Rotate(double angle, const Point2D& center) {
    // 角度转弧度
    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    // 复合变换: 先平移到原点,再旋转,最后平移回原位置
    Matrix3x3 t1 = Translate(-center.x, -center.y);

    Matrix3x3 r;
    r.Set(0, 0, cosA);  r.Set(0, 1, -sinA);
    r.Set(1, 0, sinA);  r.Set(1, 1, cosA);

    Matrix3x3 t2 = Translate(center.x, center.y);

    return t2 * r * t1;
}

/**
* 生成错切变换矩阵
* @param shx: x方向的错切因子
* @param shy: y方向的错切因子
* @return: 返回错切变换矩阵
*/
Matrix3x3 Transform::Shear(double shx, double shy) {
    Matrix3x3 m;
    m.Set(0, 1, shx);  // x方向错切
    m.Set(1, 0, shy);  // y方向错切
    return m;
}

/**
* 生成缩放变换矩阵
* @param sx: x方向的缩放因子
* @param sy: y方向的缩放因子
* @param center: 缩放中心点
* @return: 返回缩放变换矩阵
*/
Matrix3x3 Transform::Scale(double sx, double sy, const Point2D& center) {
    // 复合变换: 先平移到原点,再缩放,最后平移回原位置
    Matrix3x3 t1 = Translate(-center.x, -center.y);

    Matrix3x3 s;
    s.Set(0, 0, sx);
    s.Set(1, 1, sy);

    Matrix3x3 t2 = Translate(center.x, center.y);

    return t2 * s * t1;
}

/**
* 生成关于直线y=kx+b的对称变换矩阵
* @param k: 直线斜率
* @param b: 直线截距
* @return: 返回对称变换矩阵
*/
Matrix3x3 Transform::Reflect(double k, double b) {
    Matrix3x3 m;
    double k2 = k * k;
    double den = 1 + k2;

    // 设置对称变换矩阵的各个元素
    m.Set(0, 0, (1 - k2) / den);
    m.Set(0, 1, 2 * k / den);
    m.Set(1, 0, 2 * k / den);
    m.Set(1, 1, (k2 - 1) / den);
    m.Set(0, 2, -2 * k * b / den);
    m.Set(1, 2, 2 * b / den);

    return m;
}

/**
* 生成关于x轴的对称变换矩阵
* @return: 返回对称变换矩阵
*/
Matrix3x3 Transform::ReflectX() {
    Matrix3x3 m;
    m.Set(1, 1, -1);  // y坐标取反
    return m;
}

/**
* 生成关于y轴的对称变换矩阵
* @return: 返回对称变换矩阵
*/
Matrix3x3 Transform::ReflectY() {
    Matrix3x3 m;
    m.Set(0, 0, -1);  // x坐标取反
    return m;
}