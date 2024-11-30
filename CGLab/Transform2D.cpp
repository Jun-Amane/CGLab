/*
*
* �ļ�: Math/Transform2D.cpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�ʵ���˶�άͼ�α任����غ���
* ��Ҫ����:
* 1. ��ı任
* 2. ƽ�Ʊ任
* 3. ��ת�任
* 4. ���б任
* 5. ���ű任
* 6. �ԳƱ任
* ���б任��ʹ��3x3����������ʵ��
*/

#include "pch.h"
#include "Transform2D.hpp"

using namespace MyGraphics;

/**
* �Ե���о���任
* @param p: ���任�ĵ�
* @param matrix: �任����
* @return: ���ر任����µ�
*/
Point2D MyGraphics::TransformPoint(const Point2D& p, const Matrix3x3& matrix) {
    const auto& m = matrix.GetData();
    // ������������µı任���
    double x = p.x * m[0][0] + p.y * m[0][1] + m[0][2];
    double y = p.x * m[1][0] + p.y * m[1][1] + m[1][2];
    double w = p.x * m[2][0] + p.y * m[2][1] + m[2][2];

    // ���������ת�صѿ�������
    if (w != 0) {
        x /= w;
        y /= w;
    }
    return Point2D(static_cast<int>(round(x)), static_cast<int>(round(y)));
}

/**
* ����ƽ�Ʊ任����
* @param dx: x�����λ����
* @param dy: y�����λ����
* @return: ����ƽ�Ʊ任����
*/
Matrix3x3 Transform::Translate(int dx, int dy) {
    Matrix3x3 m;
    m.Set(0, 2, dx);  // x����ƽ����
    m.Set(1, 2, dy);  // y����ƽ����
    return m;
}

/**
* ������ת�任����
* @param angle: ��ת�Ƕ�(��)
* @param center: ��ת���ĵ�
* @return: ������ת�任����
*/
Matrix3x3 Transform::Rotate(double angle, const Point2D& center) {
    // �Ƕ�ת����
    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    // ���ϱ任: ��ƽ�Ƶ�ԭ��,����ת,���ƽ�ƻ�ԭλ��
    Matrix3x3 t1 = Translate(-center.x, -center.y);

    Matrix3x3 r;
    r.Set(0, 0, cosA);  r.Set(0, 1, -sinA);
    r.Set(1, 0, sinA);  r.Set(1, 1, cosA);

    Matrix3x3 t2 = Translate(center.x, center.y);

    return t2 * r * t1;
}

/**
* ���ɴ��б任����
* @param shx: x����Ĵ�������
* @param shy: y����Ĵ�������
* @return: ���ش��б任����
*/
Matrix3x3 Transform::Shear(double shx, double shy) {
    Matrix3x3 m;
    m.Set(0, 1, shx);  // x�������
    m.Set(1, 0, shy);  // y�������
    return m;
}

/**
* �������ű任����
* @param sx: x�������������
* @param sy: y�������������
* @param center: �������ĵ�
* @return: �������ű任����
*/
Matrix3x3 Transform::Scale(double sx, double sy, const Point2D& center) {
    // ���ϱ任: ��ƽ�Ƶ�ԭ��,������,���ƽ�ƻ�ԭλ��
    Matrix3x3 t1 = Translate(-center.x, -center.y);

    Matrix3x3 s;
    s.Set(0, 0, sx);
    s.Set(1, 1, sy);

    Matrix3x3 t2 = Translate(center.x, center.y);

    return t2 * s * t1;
}

/**
* ���ɹ���ֱ��y=kx+b�ĶԳƱ任����
* @param k: ֱ��б��
* @param b: ֱ�߽ؾ�
* @return: ���ضԳƱ任����
*/
Matrix3x3 Transform::Reflect(double k, double b) {
    Matrix3x3 m;
    double k2 = k * k;
    double den = 1 + k2;

    // ���öԳƱ任����ĸ���Ԫ��
    m.Set(0, 0, (1 - k2) / den);
    m.Set(0, 1, 2 * k / den);
    m.Set(1, 0, 2 * k / den);
    m.Set(1, 1, (k2 - 1) / den);
    m.Set(0, 2, -2 * k * b / den);
    m.Set(1, 2, 2 * b / den);

    return m;
}

/**
* ���ɹ���x��ĶԳƱ任����
* @return: ���ضԳƱ任����
*/
Matrix3x3 Transform::ReflectX() {
    Matrix3x3 m;
    m.Set(1, 1, -1);  // y����ȡ��
    return m;
}

/**
* ���ɹ���y��ĶԳƱ任����
* @return: ���ضԳƱ任����
*/
Matrix3x3 Transform::ReflectY() {
    Matrix3x3 m;
    m.Set(0, 0, -1);  // x����ȡ��
    return m;
}