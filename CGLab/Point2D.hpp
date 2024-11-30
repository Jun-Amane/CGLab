/*
*
* 文件: Math/Point2D.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 26/11/24
*
* 说明: 本文件声明了二维点类
* 主要功能:
* 1. 存储二维平面上点的整数坐标(x,y)
* 2. 提供点的构造与初始化
* 3. 实现点的相等性比较
* 该类作为图形算法的基本数据类型使用
*/

#pragma once

namespace MyGraphics {
    /**
     * 二维点类
     * 使用整数坐标表示平面上的点
     */
    class Point2D {
    public:
        int x;  // x坐标
        int y;  // y坐标

        /**
         * 构造函数
         * @param x: x坐标值,默认为0
         * @param y: y坐标值,默认为0
         */
        Point2D(int x = 0, int y = 0) : x(x), y(y) {}

        /**
         * 相等运算符重载
         * @param other: 要比较的另一个点
         * @return: 如果两点坐标完全相同返回true,否则返回false
         */
        bool operator==(const Point2D& other) const {
            return x == other.x && y == other.y;
        }

        /**
         * 不等运算符重载
         * @param other: 要比较的另一个点
         * @return: 如果两点坐标不完全相同返回true,否则返回false
         */
        bool operator!=(const Point2D& other) const {
            return x != other.x || y != other.y;
        }
    };
}