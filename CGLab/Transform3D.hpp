/*
 *
 * 文件: Math/Transform3D.hpp
 * 作者: Ziyu ZHOU @ SDAU
 * 日期: 30/11/24
 *
 * 说明: 本文件定义了三维图形变换相关的函数和类
 * 实现了以下功能:
 * 1. 三维点的变换函数
 * 2. 三维基本变换矩阵生成
 *   - 平移变换
 *   - 旋转变换(绕x轴、y轴、z轴)
 *   - 缩放变换
 * 所有变换都支持指定变换中心点
 */

#pragma once
#include "Point3D.hpp"
#include "Matrix4x4.hpp"

namespace MyGraphics {

    /**
     * 对三维点进行矩阵变换
     * @param p: 待变换的三维点
     * @param matrix: 4x4变换矩阵
     * @return: 变换后的新点
     */
    Point3D TransformPoint(const Point3D& p, const Matrix4x4& matrix);

    namespace Transform3D {
        /**
         * 生成三维平移变换矩阵
         * @param dx: x方向平移量
         * @param dy: y方向平移量
         * @param dz: z方向平移量
         * @return: 4x4平移变换矩阵
         */
        Matrix4x4 Translate(double dx, double dy, double dz);

        /**
         * 生成绕x轴旋转的变换矩阵
         * @param angle: 旋转角度(度)
         * @param center: 旋转中心点,默认为原点
         * @return: 4x4旋转变换矩阵
         */
        Matrix4x4 RotateX(double angle, const Point3D& center = Point3D(0, 0, 0));

        /**
         * 生成绕y轴旋转的变换矩阵
         * @param angle: 旋转角度(度)
         * @param center: 旋转中心点,默认为原点
         * @return: 4x4旋转变换矩阵
         */
        Matrix4x4 RotateY(double angle, const Point3D& center = Point3D(0, 0, 0));

        /**
         * 生成绕z轴旋转的变换矩阵
         * @param angle: 旋转角度(度)
         * @param center: 旋转中心点,默认为原点
         * @return: 4x4旋转变换矩阵
         */
        Matrix4x4 RotateZ(double angle, const Point3D& center = Point3D(0, 0, 0));

        /**
         * 生成三维缩放变换矩阵
         * @param sx: x方向缩放系数
         * @param sy: y方向缩放系数
         * @param sz: z方向缩放系数
         * @param center: 缩放中心点,默认为原点
         * @return: 4x4缩放变换矩阵
         */
        Matrix4x4 Scale(double sx, double sy, double sz, const Point3D& center = Point3D(0, 0, 0));
    }
}