/*
 * Math/Transform2D.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */

#pragma once
#include "Point2D.hpp"
#include "Matrix3x3.hpp"

namespace MyGraphics {
    // ��ı任��������
    Point2D TransformPoint(const Point2D& p, const Matrix3x3& matrix);

    namespace Transform {
        // ƽ�Ʊ任����
        Matrix3x3 Translate(int dx, int dy);

        // ��ת�任���󣨽Ƕ��ƣ�
        Matrix3x3 Rotate(double angle, const Point2D& center = Point2D(0, 0));

        // ���б任����
        Matrix3x3 Shear(double shx, double shy);

        // ���ű任����
        Matrix3x3 Scale(double sx, double sy, const Point2D& center = Point2D(0, 0));

        // �ԳƱ任����
        Matrix3x3 Reflect(double k, double b);  // ����ֱ��y=kx+b�Գ�
        Matrix3x3 ReflectX();                   // ����x��Գ�
        Matrix3x3 ReflectY();                   // ����y��Գ�
    }
}