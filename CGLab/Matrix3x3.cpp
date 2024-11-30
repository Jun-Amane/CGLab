/*
*
* �ļ�: Math/Matrix3x3.cpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�ʵ����3x3������Ļ�������
* ��Ҫ����:
* 1. ����Ĺ������ʼ��
* 2. ����Ԫ�صķ������޸�
* 3. ����˷�����
* 4. ������ȱȽ�
*/

#include "pch.h"
#include "Matrix3x3.hpp"

using namespace MyGraphics;

/**
* Ĭ�Ϲ��캯��
* �������ʼ��Ϊ3x3��λ����
* |1 0 0|
* |0 1 0|
* |0 0 1|
*/
Matrix3x3::Matrix3x3() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m_data[i][j] = (i == j) ? 1.0 : 0.0;
}

/**
* ���������캯��
* @param data: ������ʼֵ�Ķ�ά����
*/
Matrix3x3::Matrix3x3(const std::array<std::array<double, 3>, 3>& data)
    : m_data(data) {}

/**
* ��ȡ����ָ��λ�õ�Ԫ��ֵ
* @param row: ������(0-2)
* @param col: ������(0-2)
* @return: ���ض�Ӧλ�õ�Ԫ��ֵ
*/
double Matrix3x3::Get(int row, int col) const {
    return m_data[row][col];
}

/**
* ���þ���ָ��λ�õ�Ԫ��ֵ
* @param row: ������(0-2)
* @param col: ������(0-2)
* @param value: Ҫ���õ���ֵ
*/
void Matrix3x3::Set(int row, int col, double value) {
    m_data[row][col] = value;
}

/**
* ����˷����������
* ʵ������3x3����ĳ˷�����
* @param other: �Ҳ���������
* @return: ���س˷�����������
*/
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

/**
* ������������
* �ж����������Ƿ����
* @param other: Ҫ�Ƚϵľ���
* @return: �������������ȫ��ȷ���true,���򷵻�false
*/
bool Matrix3x3::operator==(const Matrix3x3& other) const {
    return m_data == other.m_data;
}

/**
* �������������
* �ж����������Ƿ񲻵�
* @param other: Ҫ�Ƚϵľ���
* @return: �������������ȷ���true,���򷵻�false
*/
bool Matrix3x3::operator!=(const Matrix3x3& other) const {
    return !(*this == other);
}