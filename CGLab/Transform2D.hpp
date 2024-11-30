/*
*
* 文件: Math/Transform2D.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件声明了二维图形变换的相关函数
* 包括点的变换和各种基本变换矩阵的生成:
* 1. 平移变换
* 2. 旋转变换
* 3. 错切变换
* 4. 缩放变换
* 5. 对称变换
* 所有变换都使用3x3齐次坐标矩阵实现
*/

#pragma once
#include "Point2D.hpp"
#include "Matrix3x3.hpp"

namespace MyGraphics {
    /**
     * 对点进行矩阵变换
     * @param p: 待变换的点
     * @param matrix: 变换矩阵
     * @return: 返回变换后的新点
     */
    Point2D TransformPoint(const Point2D& p, const Matrix3x3& matrix);

    namespace Transform {
        /**
         * 生成平移变换矩阵
         * @param dx: x方向的位移量
         * @param dy: y方向的位移量
         * @return: 返回平移变换矩阵
         */
        Matrix3x3 Translate(int dx, int dy);

        /**
         * 生成旋转变换矩阵
         * @param angle: 旋转角度(度)
         * @param center: 旋转中心点,默认为原点
         * @return: 返回旋转变换矩阵
         */
        Matrix3x3 Rotate(double angle, const Point2D& center = Point2D(0, 0));

        /**
         * 生成错切变换矩阵
         * @param shx: x方向的错切因子
         * @param shy: y方向的错切因子
         * @return: 返回错切变换矩阵
         */
        Matrix3x3 Shear(double shx, double shy);

        /**
         * 生成缩放变换矩阵
         * @param sx: x方向的缩放因子
         * @param sy: y方向的缩放因子
         * @param center: 缩放中心点,默认为原点
         * @return: 返回缩放变换矩阵
         */
        Matrix3x3 Scale(double sx, double sy, const Point2D& center = Point2D(0, 0));

        /**
         * 生成对称变换矩阵
         * @param k: 直线斜率
         * @param b: 直线截距
         * @return: 返回关于直线y=kx+b的对称变换矩阵
         */
        Matrix3x3 Reflect(double k, double b);

        /**
         * 生成关于x轴的对称变换矩阵
         * @return: 返回对称变换矩阵
         */
        Matrix3x3 ReflectX();

        /**
         * 生成关于y轴的对称变换矩阵
         * @return: 返回对称变换矩阵
         */
        Matrix3x3 ReflectY();
    }
}