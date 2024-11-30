/*
*
* 文件: Math/Matrix4x4.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件声明了4x4矩阵类
* 主要功能包括:
* 1. 矩阵的基本构造与初始化
* 2. 矩阵元素的访问与修改
* 3. 矩阵基本运算(乘法、比较)
* 4. 内部数据的访问
* 该类用于实现三维图形变换的齐次坐标矩阵运算
*/

#pragma once
#include <array>

namespace MyGraphics {
    /**
     * 4x4矩阵类
     * 使用二维数组存储矩阵元素
     * 提供基本的矩阵运算功能
     */
    class Matrix4x4 {
    public:
        /**
         * 默认构造函数
         * 初始化为4x4单位矩阵
         */
        Matrix4x4();

        /**
         * 带参数构造函数
         * @param data: 包含初始值的二维数组
         */
        Matrix4x4(const std::array<std::array<double, 4>, 4>& data);

        /**
         * 获取矩阵元素
         * @param row: 行索引(0-3)
         * @param col: 列索引(0-3)
         * @return: 返回指定位置的元素值
         */
        double Get(int row, int col) const;

        /**
         * 设置矩阵元素
         * @param row: 行索引(0-3)
         * @param col: 列索引(0-3)
         * @param value: 要设置的新值
         */
        void Set(int row, int col, double value);

        /**
         * 矩阵乘法运算
         * @param other: 右操作数矩阵
         * @return: 返回乘法结果矩阵
         */
        Matrix4x4 operator*(const Matrix4x4& other) const;

        /**
         * 矩阵相等比较
         * @param other: 要比较的矩阵
         * @return: 相等返回true,否则返回false
         */
        bool operator==(const Matrix4x4& other) const;

        /**
         * 矩阵不等比较
         * @param other: 要比较的矩阵
         * @return: 不等返回true,否则返回false
         */
        bool operator!=(const Matrix4x4& other) const;

        /**
         * 获取矩阵内部数据的常量引用
         * @return: 返回内部二维数组的常量引用
         */
        const std::array<std::array<double, 4>, 4>& GetData() const { return m_data; }

    private:
        std::array<std::array<double, 4>, 4> m_data;  // 存储矩阵元素的二维数组
    };
}