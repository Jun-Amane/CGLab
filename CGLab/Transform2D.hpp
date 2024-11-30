/*
*
* �ļ�: Math/Transform2D.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ������˶�άͼ�α任����غ���
* ������ı任�͸��ֻ����任���������:
* 1. ƽ�Ʊ任
* 2. ��ת�任
* 3. ���б任
* 4. ���ű任
* 5. �ԳƱ任
* ���б任��ʹ��3x3����������ʵ��
*/

#pragma once
#include "Point2D.hpp"
#include "Matrix3x3.hpp"

namespace MyGraphics {
    /**
     * �Ե���о���任
     * @param p: ���任�ĵ�
     * @param matrix: �任����
     * @return: ���ر任����µ�
     */
    Point2D TransformPoint(const Point2D& p, const Matrix3x3& matrix);

    namespace Transform {
        /**
         * ����ƽ�Ʊ任����
         * @param dx: x�����λ����
         * @param dy: y�����λ����
         * @return: ����ƽ�Ʊ任����
         */
        Matrix3x3 Translate(int dx, int dy);

        /**
         * ������ת�任����
         * @param angle: ��ת�Ƕ�(��)
         * @param center: ��ת���ĵ�,Ĭ��Ϊԭ��
         * @return: ������ת�任����
         */
        Matrix3x3 Rotate(double angle, const Point2D& center = Point2D(0, 0));

        /**
         * ���ɴ��б任����
         * @param shx: x����Ĵ�������
         * @param shy: y����Ĵ�������
         * @return: ���ش��б任����
         */
        Matrix3x3 Shear(double shx, double shy);

        /**
         * �������ű任����
         * @param sx: x�������������
         * @param sy: y�������������
         * @param center: �������ĵ�,Ĭ��Ϊԭ��
         * @return: �������ű任����
         */
        Matrix3x3 Scale(double sx, double sy, const Point2D& center = Point2D(0, 0));

        /**
         * ���ɶԳƱ任����
         * @param k: ֱ��б��
         * @param b: ֱ�߽ؾ�
         * @return: ���ع���ֱ��y=kx+b�ĶԳƱ任����
         */
        Matrix3x3 Reflect(double k, double b);

        /**
         * ���ɹ���x��ĶԳƱ任����
         * @return: ���ضԳƱ任����
         */
        Matrix3x3 ReflectX();

        /**
         * ���ɹ���y��ĶԳƱ任����
         * @return: ���ضԳƱ任����
         */
        Matrix3x3 ReflectY();
    }
}