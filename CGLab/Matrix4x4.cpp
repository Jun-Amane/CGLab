/*
 *
 * Math/Matrix4x4.cpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 * 
 */


#include "pch.h"
#include "Matrix4x4.hpp"

using namespace MyGraphics;

Matrix4x4::Matrix4x4() {
    // 初始化为单位矩阵
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m_data[i][j] = (i == j) ? 1.0 : 0.0;
}

Matrix4x4::Matrix4x4(const std::array<std::array<double, 4>, 4>& data)
    : m_data(data) {}

double Matrix4x4::Get(int row, int col) const {
    return m_data[row][col];
}

void Matrix4x4::Set(int row, int col, double value) {
    m_data[row][col] = value;
}

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

bool Matrix4x4::operator==(const Matrix4x4& other) const {
    return m_data == other.m_data;
}

bool Matrix4x4::operator!=(const Matrix4x4& other) const {
    return !(*this == other);
}