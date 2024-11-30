/*
 * Math/Matrix3x3.cpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */

#include "pch.h"
#include "Matrix3x3.hpp"

using namespace MyGraphics;

Matrix3x3::Matrix3x3() {
    // 初始化为单位矩阵
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m_data[i][j] = (i == j) ? 1.0 : 0.0;
}

Matrix3x3::Matrix3x3(const std::array<std::array<double, 3>, 3>& data)
    : m_data(data) {}

double Matrix3x3::Get(int row, int col) const {
    return m_data[row][col];
}

void Matrix3x3::Set(int row, int col, double value) {
    m_data[row][col] = value;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const {
    Matrix3x3 result;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            result.m_data[i][j] = 0;
            for (int k = 0; k < 3; ++k)
                result.m_data[i][j] += m_data[i][k] * other.m_data[k][j];
        }
    return result;
}

bool Matrix3x3::operator==(const Matrix3x3& other) const {
    return m_data == other.m_data;
}

bool Matrix3x3::operator!=(const Matrix3x3& other) const {
    return !(*this == other);
}
