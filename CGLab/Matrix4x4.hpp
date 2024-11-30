/*
*
* �ļ�: Math/Matrix4x4.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�������4x4������
* ��Ҫ���ܰ���:
* 1. ����Ļ����������ʼ��
* 2. ����Ԫ�صķ������޸�
* 3. �����������(�˷����Ƚ�)
* 4. �ڲ����ݵķ���
* ��������ʵ����άͼ�α任����������������
*/

#pragma once
#include <array>

namespace MyGraphics {
    /**
     * 4x4������
     * ʹ�ö�ά����洢����Ԫ��
     * �ṩ�����ľ������㹦��
     */
    class Matrix4x4 {
    public:
        /**
         * Ĭ�Ϲ��캯��
         * ��ʼ��Ϊ4x4��λ����
         */
        Matrix4x4();

        /**
         * ���������캯��
         * @param data: ������ʼֵ�Ķ�ά����
         */
        Matrix4x4(const std::array<std::array<double, 4>, 4>& data);

        /**
         * ��ȡ����Ԫ��
         * @param row: ������(0-3)
         * @param col: ������(0-3)
         * @return: ����ָ��λ�õ�Ԫ��ֵ
         */
        double Get(int row, int col) const;

        /**
         * ���þ���Ԫ��
         * @param row: ������(0-3)
         * @param col: ������(0-3)
         * @param value: Ҫ���õ���ֵ
         */
        void Set(int row, int col, double value);

        /**
         * ����˷�����
         * @param other: �Ҳ���������
         * @return: ���س˷��������
         */
        Matrix4x4 operator*(const Matrix4x4& other) const;

        /**
         * ������ȱȽ�
         * @param other: Ҫ�Ƚϵľ���
         * @return: ��ȷ���true,���򷵻�false
         */
        bool operator==(const Matrix4x4& other) const;

        /**
         * ���󲻵ȱȽ�
         * @param other: Ҫ�Ƚϵľ���
         * @return: ���ȷ���true,���򷵻�false
         */
        bool operator!=(const Matrix4x4& other) const;

        /**
         * ��ȡ�����ڲ����ݵĳ�������
         * @return: �����ڲ���ά����ĳ�������
         */
        const std::array<std::array<double, 4>, 4>& GetData() const { return m_data; }

    private:
        std::array<std::array<double, 4>, 4> m_data;  // �洢����Ԫ�صĶ�ά����
    };
}