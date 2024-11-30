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
        Matrix3x3();  // ���쵥λ����
        Matrix3x3(const std::array<std::array<double, 3>, 3>& data);

        // ��ȡ������Ԫ��
        double Get(int row, int col) const;
        void Set(int row, int col, double value);

        // �������
        Matrix3x3 operator*(const Matrix3x3& other) const;
        bool operator==(const Matrix3x3& other) const;
        bool operator!=(const Matrix3x3& other) const;

        // ��ȡ�ڲ�����
        const std::array<std::array<double, 3>, 3>& GetData() const { return m_data; }

    private:
        std::array<std::array<double, 3>, 3> m_data;
    };
}