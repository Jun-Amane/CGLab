/*
 *
 * Math/Matrix4x4.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 * 
 */


#pragma once
#include <array>

namespace MyGraphics {
    class Matrix4x4 {
    public:
        Matrix4x4();  // 构造单位矩阵
        Matrix4x4(const std::array<std::array<double, 4>, 4>& data);

        // 获取和设置元素
        double Get(int row, int col) const;
        void Set(int row, int col, double value);

        // 矩阵操作
        Matrix4x4 operator*(const Matrix4x4& other) const;
        bool operator==(const Matrix4x4& other) const;
        bool operator!=(const Matrix4x4& other) const;

        // 获取内部数据
        const std::array<std::array<double, 4>, 4>& GetData() const { return m_data; }

    private:
        std::array<std::array<double, 4>, 4> m_data;
    };
}