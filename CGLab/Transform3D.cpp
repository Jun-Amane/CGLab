/*
 *
 * �ļ�: Math/Transform3D.cpp
 * ����: Ziyu ZHOU @ SDAU
 * ����: 30/11/24
 *
 * ˵��: ���ļ�ʵ������άͼ�α任����غ���
 * ����:
 * 1. ��ά��ľ���任
 * 2. ��ά�����任���������
 *   - ƽ�Ʊ任
 *   - ��ת�任(��x�ᡢy�ᡢz��)
 *   - ���ű任
 */

#include "pch.h"
#include "Transform3D.hpp"

using namespace MyGraphics;

/**
 * ����ά����о���任
 * ʵ�ַ�ʽ�������������任������ˣ��������������
 */
Point3D MyGraphics::TransformPoint(const Point3D& p, const Matrix4x4& matrix) {
    const auto& m = matrix.GetData();
    // ����任����������
    double x = p.x * m[0][0] + p.y * m[0][1] + p.z * m[0][2] + m[0][3];
    double y = p.x * m[1][0] + p.y * m[1][1] + p.z * m[1][2] + m[1][3];
    double z = p.x * m[2][0] + p.y * m[2][1] + p.z * m[2][2] + m[2][3];
    double w = p.x * m[3][0] + p.y * m[3][1] + p.z * m[3][2] + m[3][3];

    // ���������ת������ά����
    if (w != 0) {
        x /= w;
        y /= w;
        z /= w;
    }

    // �Խ�������������벢����
    return Point3D(static_cast<double>(round(x)),
        static_cast<double>(round(y)),
        static_cast<double>(round(z)));
}

/**
 * ������άƽ�Ʊ任����
 * ͨ�����þ������һ�е�ƽ����ʵ��
 */
Matrix4x4 Transform3D::Translate(double dx, double dy, double dz) {
    Matrix4x4 m;  // Ĭ�Ϲ��쵥λ����
    m.Set(0, 3, dx);  // ����x����ƽ����
    m.Set(1, 3, dy);  // ����y����ƽ����
    m.Set(2, 3, dz);  // ����z����ƽ����
    return m;
}

/**
 * ������ά���ű任����
 * ʵ�ַ�ʽ����������ƽ�Ƶ�ԭ�㣬�������ź���ƽ�ƻ�ԭλ��
 */
Matrix4x4 Transform3D::Scale(double sx, double sy, double sz, const Point3D& center) {
    // ��һ����ƽ�Ƶ�ԭ��
    Matrix4x4 t1 = Translate(-center.x, -center.y, -center.z);

    // �ڶ���������������ž���
    Matrix4x4 s;
    s.Set(0, 0, sx);  // x��������ϵ��
    s.Set(1, 1, sy);  // y��������ϵ��
    s.Set(2, 2, sz);  // z��������ϵ��

    // ��������ƽ�ƻ�ԭλ��
    Matrix4x4 t2 = Translate(center.x, center.y, center.z);

    // ���ر任��������
    return t2 * s * t1;
}

/**
 * ������x����ת�ı任����
 * ʵ�ַ�ʽ����������ƽ�Ƶ�ԭ�㣬��x����ת����ƽ�ƻ�ԭλ��
 */
Matrix4x4 Transform3D::RotateX(double angle, const Point3D& center) {
    // ��һ����ƽ�Ƶ�ԭ��
    Matrix4x4 t1 = Translate(-center.x, -center.y, -center.z);

    // ���Ƕ�ת��Ϊ���Ȳ��������Ǻ���ֵ
    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    // �ڶ�����������x����ת����
    Matrix4x4 r;
    r.Set(1, 1, cosA);  r.Set(1, 2, -sinA);
    r.Set(2, 1, sinA);  r.Set(2, 2, cosA);

    // ��������ƽ�ƻ�ԭλ��
    Matrix4x4 t2 = Translate(center.x, center.y, center.z);

    return t2 * r * t1;
}

/**
 * ������y����ת�ı任����
 * ʵ�ַ�ʽ����������ƽ�Ƶ�ԭ�㣬��y����ת����ƽ�ƻ�ԭλ��
 */
Matrix4x4 Transform3D::RotateY(double angle, const Point3D& center) {
    Matrix4x4 t1 = Translate(-center.x, -center.y, -center.z);

    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    // ������y����ת����
    Matrix4x4 r;
    r.Set(0, 0, cosA);  r.Set(0, 2, sinA);
    r.Set(2, 0, -sinA); r.Set(2, 2, cosA);

    Matrix4x4 t2 = Translate(center.x, center.y, center.z);

    return t2 * r * t1;
}

/**
 * ������z����ת�ı任����
 * ʵ�ַ�ʽ����������ƽ�Ƶ�ԭ�㣬��z����ת����ƽ�ƻ�ԭλ��
 */
Matrix4x4 Transform3D::RotateZ(double angle, const Point3D& center) {
    Matrix4x4 t1 = Translate(-center.x, -center.y, -center.z);

    double rad = angle * M_PI / 180.0;
    double cosA = cos(rad);
    double sinA = sin(rad);

    // ������z����ת����
    Matrix4x4 r;
    r.Set(0, 0, cosA);  r.Set(0, 1, -sinA);
    r.Set(1, 0, sinA);  r.Set(1, 1, cosA);

    Matrix4x4 t2 = Translate(center.x, center.y, center.z);

    return t2 * r * t1;
}
