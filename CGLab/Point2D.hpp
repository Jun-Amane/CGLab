/*
*
* �ļ�: Math/Point2D.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 26/11/24
*
* ˵��: ���ļ������˶�ά����
* ��Ҫ����:
* 1. �洢��άƽ���ϵ����������(x,y)
* 2. �ṩ��Ĺ������ʼ��
* 3. ʵ�ֵ������ԱȽ�
* ������Ϊͼ���㷨�Ļ�����������ʹ��
*/

#pragma once

namespace MyGraphics {
    /**
     * ��ά����
     * ʹ�����������ʾƽ���ϵĵ�
     */
    class Point2D {
    public:
        int x;  // x����
        int y;  // y����

        /**
         * ���캯��
         * @param x: x����ֵ,Ĭ��Ϊ0
         * @param y: y����ֵ,Ĭ��Ϊ0
         */
        Point2D(int x = 0, int y = 0) : x(x), y(y) {}

        /**
         * ������������
         * @param other: Ҫ�Ƚϵ���һ����
         * @return: �������������ȫ��ͬ����true,���򷵻�false
         */
        bool operator==(const Point2D& other) const {
            return x == other.x && y == other.y;
        }

        /**
         * �������������
         * @param other: Ҫ�Ƚϵ���һ����
         * @return: ����������겻��ȫ��ͬ����true,���򷵻�false
         */
        bool operator!=(const Point2D& other) const {
            return x != other.x || y != other.y;
        }
    };
}