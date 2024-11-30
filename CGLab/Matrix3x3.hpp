/*
 * Math/Matrix3x3.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */

#pragma once
#include <array>

namespace MyGraphics {
    class Matrix3x3 {
    public:
        Matrix3x3();  // 构造单位矩阵
        Matrix3x3(const std::array<std::array<double, 3>, 3>& data);

        // 获取和设置元素
        double Get(int row, int col) const;
        void Set(int row, int col, double value);

        // 矩阵操作
        Matrix3x3 operator*(const Matrix3x3& other) const;
        bool operator==(const Matrix3x3& other) const;
        bool operator!=(const Matrix3x3& other) const;

        // 获取内部数据
        const std::array<std::array<double, 3>, 3>& GetData() const { return m_data; }

    private:
        std::array<std::array<double, 3>, 3> m_data;
    };
}