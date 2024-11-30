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
        Matrix4x4();  // ���쵥λ����
        Matrix4x4(const std::array<std::array<double, 4>, 4>& data);

        // ��ȡ������Ԫ��
        double Get(int row, int col) const;
        void Set(int row, int col, double value);

        // �������
        Matrix4x4 operator*(const Matrix4x4& other) const;
        bool operator==(const Matrix4x4& other) const;
        bool operator!=(const Matrix4x4& other) const;

        // ��ȡ�ڲ�����
        const std::array<std::array<double, 4>, 4>& GetData() const { return m_data; }

    private:
        std::array<std::array<double, 4>, 4> m_data;
    };
}