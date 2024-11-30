/*
 *
 * �ļ�: Math/Transform3D.hpp
 * ����: Ziyu ZHOU @ SDAU
 * ����: 30/11/24
 *
 * ˵��: ���ļ���������άͼ�α任��صĺ�������
 * ʵ�������¹���:
 * 1. ��ά��ı任����
 * 2. ��ά�����任��������
 *   - ƽ�Ʊ任
 *   - ��ת�任(��x�ᡢy�ᡢz��)
 *   - ���ű任
 * ���б任��֧��ָ���任���ĵ�
 */

#pragma once
#include "Point3D.hpp"
#include "Matrix4x4.hpp"

namespace MyGraphics {

    /**
     * ����ά����о���任
     * @param p: ���任����ά��
     * @param matrix: 4x4�任����
     * @return: �任����µ�
     */
    Point3D TransformPoint(const Point3D& p, const Matrix4x4& matrix);

    namespace Transform3D {
        /**
         * ������άƽ�Ʊ任����
         * @param dx: x����ƽ����
         * @param dy: y����ƽ����
         * @param dz: z����ƽ����
         * @return: 4x4ƽ�Ʊ任����
         */
        Matrix4x4 Translate(double dx, double dy, double dz);

        /**
         * ������x����ת�ı任����
         * @param angle: ��ת�Ƕ�(��)
         * @param center: ��ת���ĵ�,Ĭ��Ϊԭ��
         * @return: 4x4��ת�任����
         */
        Matrix4x4 RotateX(double angle, const Point3D& center = Point3D(0, 0, 0));

        /**
         * ������y����ת�ı任����
         * @param angle: ��ת�Ƕ�(��)
         * @param center: ��ת���ĵ�,Ĭ��Ϊԭ��
         * @return: 4x4��ת�任����
         */
        Matrix4x4 RotateY(double angle, const Point3D& center = Point3D(0, 0, 0));

        /**
         * ������z����ת�ı任����
         * @param angle: ��ת�Ƕ�(��)
         * @param center: ��ת���ĵ�,Ĭ��Ϊԭ��
         * @return: 4x4��ת�任����
         */
        Matrix4x4 RotateZ(double angle, const Point3D& center = Point3D(0, 0, 0));

        /**
         * ������ά���ű任����
         * @param sx: x��������ϵ��
         * @param sy: y��������ϵ��
         * @param sz: z��������ϵ��
         * @param center: �������ĵ�,Ĭ��Ϊԭ��
         * @return: 4x4���ű任����
         */
        Matrix4x4 Scale(double sx, double sy, double sz, const Point3D& center = Point3D(0, 0, 0));
    }
}