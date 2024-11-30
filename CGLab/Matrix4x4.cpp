/*
*
* 文件: Math/Matrix4x4.cpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件实现了4x4矩阵类的基本操作
* 主要包含:
* 1. 矩阵的构造与初始化
* 2. 矩阵元素的访问与修改
* 3. 矩阵乘法运算
* 4. 矩阵相等比较
* 通常用于三维图形变换中的齐次坐标运算
*/

#include "pch.h"
#include "Matrix4x4.hpp"

using namespace MyGraphics;

/**
* 默认构造函数
* 将矩阵初始化为4x4单位矩阵
* |1 0 0 0|
* |0 1 0 0|
* |0 0 1 0|
* |0 0 0 1|
*/
Matrix4x4::Matrix4x4() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m_data[i][j] = (i == j) ? 1.0 : 0.0;
}

/**
* 带参数构造函数
* @param data: 包含初始值的二维数组
*/
Matrix4x4::Matrix4x4(const std::array<std::array<double, 4>, 4>& data)
    : m_data(data) {}

/**
* 获取矩阵指定位置的元素值
* @param row: 行索引(0-3)
* @param col: 列索引(0-3)
* @return: 返回对应位置的元素值
*/
double Matrix4x4::Get(int row, int col) const {
    return m_data[row][col];
}

/**
* 设置矩阵指定位置的元素值
* @param row: 行索引(0-3)
* @param col: 列索引(0-3)
* @param value: 要设置的新值
*/
void Matrix4x4::Set(int row, int col, double value) {
    m_data[row][col] = value;
}

/**
* 矩阵乘法运算符重载
* 实现两个4x4矩阵的乘法运算
* @param other: 右操作数矩阵
* @return: 返回乘法运算结果矩阵
*/
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            result.m_data[i][j] = 0;
            for (int k = 0; k < 4; ++k)
                result.m_data[i][j] += m_data[i][k] * other.m_data[k][j];
        }
    return result;
}

/**
* 相等运算符重载
* 判断两个矩阵是否相等
* @param other: 要比较的矩阵
* @return: 如果两个矩阵完全相等返回true,否则返回false
*/
bool Matrix4x4::operator==(const Matrix4x4& other) const {
    return m_data == other.m_data;
}

/**
* 不等运算符重载
* 判断两个矩阵是否不等
* @param other: 要比较的矩阵
* @return: 如果两个矩阵不相等返回true,否则返回false
*/
bool Matrix4x4::operator!=(const Matrix4x4& other) const {
    return !(*this == other);
}