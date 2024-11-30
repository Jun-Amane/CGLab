/*
*
* �ļ�: Math/Point3D.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ���������ά����
* ��Ҫ����:
* 1. �洢��ά�ռ��е�ĸ�������(x,y,z)
* 2. �ṩ��Ĺ������ʼ��
* 3. ʵ�ֵ������ԱȽ�
* ����������άͼ�α任��ͶӰ����
*/

#pragma once

namespace MyGraphics {
    /**
     * ��ά����
     * ʹ�ø����������ʾ�ռ��еĵ�
     */
    class Point3D {
    public:
        double x;  // x����
        double y;  // y���� 
        double z;  // z����

        /**
         * ���캯��
         * @param x: x����ֵ,Ĭ��Ϊ0.0
         * @param y: y����ֵ,Ĭ��Ϊ0.0
         * @param z: z����ֵ,Ĭ��Ϊ0.0
         */
        Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

        /**
         * ������������
         * @param other: Ҫ�Ƚϵ���һ����
         * @return: �������������ȫ��ͬ����true,���򷵻�false
         */
        bool operator==(const Point3D& other) const {
            return x == other.x && y == other.y && z == other.z;
        }

        /**
         * �������������
         * @param other: Ҫ�Ƚϵ���һ����
         * @return: ����������겻��ȫ��ͬ����true,���򷵻�false
         */
        bool operator!=(const Point3D& other) const {
            return x != other.x || y != other.y || z != other.z;
        }
    };
}