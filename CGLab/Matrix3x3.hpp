/*
*
* �ļ�: Math/Matrix3x3.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�������3x3������
* ��Ҫ���ܰ���:
* 1. ����Ļ����������ʼ��
* 2. ����Ԫ�صķ������޸�
* 3. �����������(�˷����Ƚ�)
* 4. �ڲ����ݵķ���
* ��������ʵ�ֶ�άͼ�α任�ľ�������
*/

#pragma once
#include <array>

namespace MyGraphics {
    /**
     * 3x3������
     * ʹ�ö�ά����洢����Ԫ��
     * �ṩ�����ľ������㹦��
     */
    class Matrix3x3 {
    public:
        /**
         * Ĭ�Ϲ��캯��
         * ��ʼ��Ϊ3x3��λ����
         */
        Matrix3x3();

        /**
         * ���������캯��
         * @param data: ������ʼֵ�Ķ�ά����
         */
        Matrix3x3(const std::array<std::array<double, 3>, 3>& data);

        /**
         * ��ȡ����Ԫ��
         * @param row: ������(0-2)
         * @param col: ������(0-2)
         * @return: ����ָ��λ�õ�Ԫ��ֵ
         */
        double Get(int row, int col) const;

        /**
         * ���þ���Ԫ��
         * @param row: ������(0-2)
         * @param col: ������(0-2)
         * @param value: Ҫ���õ���ֵ
         */
        void Set(int row, int col, double value);

        /**
         * ����˷�����
         * @param other: �Ҳ���������
         * @return: ���س˷��������
         */
        Matrix3x3 operator*(const Matrix3x3& other) const;

        /**
         * ������ȱȽ�
         * @param other: Ҫ�Ƚϵľ���
         * @return: ��ȷ���true,���򷵻�false
         */
        bool operator==(const Matrix3x3& other) const;

        /**
         * ���󲻵ȱȽ�
         * @param other: Ҫ�Ƚϵľ���
         * @return: ���ȷ���true,���򷵻�false
         */
        bool operator!=(const Matrix3x3& other) const;

        /**
         * ��ȡ�����ڲ����ݵĳ�������
         * @return: �����ڲ���ά����ĳ�������
         */
        const std::array<std::array<double, 3>, 3>& GetData() const { return m_data; }

    private:
        std::array<std::array<double, 3>, 3> m_data;  // �洢����Ԫ�صĶ�ά����
    };
}