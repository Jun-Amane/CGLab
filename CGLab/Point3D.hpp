/*
*
* 文件: Math/Point3D.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件声明了三维点类
* 主要功能:
* 1. 存储三维空间中点的浮点坐标(x,y,z)
* 2. 提供点的构造与初始化
* 3. 实现点的相等性比较
* 该类用于三维图形变换和投影计算
*/

#pragma once

namespace MyGraphics {
    /**
     * 三维点类
     * 使用浮点数坐标表示空间中的点
     */
    class Point3D {
    public:
        double x;  // x坐标
        double y;  // y坐标 
        double z;  // z坐标

        /**
         * 构造函数
         * @param x: x坐标值,默认为0.0
         * @param y: y坐标值,默认为0.0
         * @param z: z坐标值,默认为0.0
         */
        Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

        /**
         * 相等运算符重载
         * @param other: 要比较的另一个点
         * @return: 如果两点坐标完全相同返回true,否则返回false
         */
        bool operator==(const Point3D& other) const {
            return x == other.x && y == other.y && z == other.z;
        }

        /**
         * 不等运算符重载
         * @param other: 要比较的另一个点
         * @return: 如果两点坐标不完全相同返回true,否则返回false
         */
        bool operator!=(const Point3D& other) const {
            return x != other.x || y != other.y || z != other.z;
        }
    };
}