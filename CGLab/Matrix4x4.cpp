/*
*
* �ļ�: Math/Matrix4x4.cpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�ʵ����4x4������Ļ�������
* ��Ҫ����:
* 1. ����Ĺ������ʼ��
* 2. ����Ԫ�صķ������޸�
* 3. ����˷�����
* 4. ������ȱȽ�
* ͨ��������άͼ�α任�е������������
*/

#include "pch.h"
#include "Matrix4x4.hpp"

using namespace MyGraphics;

/**
* Ĭ�Ϲ��캯��
* �������ʼ��Ϊ4x4��λ����
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
* ���������캯��
* @param data: ������ʼֵ�Ķ�ά����
*/
Matrix4x4::Matrix4x4(const std::array<std::array<double, 4>, 4>& data)
    : m_data(data) {}

/**
* ��ȡ����ָ��λ�õ�Ԫ��ֵ
* @param row: ������(0-3)
* @param col: ������(0-3)
* @return: ���ض�Ӧλ�õ�Ԫ��ֵ
*/
double Matrix4x4::Get(int row, int col) const {
    return m_data[row][col];
}

/**
* ���þ���ָ��λ�õ�Ԫ��ֵ
* @param row: ������(0-3)
* @param col: ������(0-3)
* @param value: Ҫ���õ���ֵ
*/
void Matrix4x4::Set(int row, int col, double value) {
    m_data[row][col] = value;
}

/**
* ����˷����������
* ʵ������4x4����ĳ˷�����
* @param other: �Ҳ���������
* @return: ���س˷�����������
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
* ������������
* �ж����������Ƿ����
* @param other: Ҫ�Ƚϵľ���
* @return: �������������ȫ��ȷ���true,���򷵻�false
*/
bool Matrix4x4::operator==(const Matrix4x4& other) const {
    return m_data == other.m_data;
}

/**
* �������������
* �ж����������Ƿ񲻵�
* @param other: Ҫ�Ƚϵľ���
* @return: �������������ȷ���true,���򷵻�false
*/
bool Matrix4x4::operator!=(const Matrix4x4& other) const {
    return !(*this == other);
}