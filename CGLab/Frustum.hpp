/*
 * �ļ�: Models/Frustum.hpp
 * ����: Ziyu ZHOU @ SDAU
 * ����: 30/11/24
 *
 * ˵��: ���ļ�������Frustum�࣬����̳���Object3D
 */

#pragma once
#include "Object3D.hpp"

namespace MyGraphics {
    class Frustum : public Object3D {
    public:
        /**
         * ���캯��
         * @param baseSize: ����߳���Ĭ��ֵΪ100.0
         * @param topSize: ����߳���Ĭ��ֵΪ60.0
         * @param height: �ߣ�Ĭ��ֵΪ120.0
         */
        Frustum(double baseSize = 100.0, double topSize = 60.0, double height = 120.0);

        /**
         * Ĭ����������
         * ����ʹ���˼̳У���������Ϊvirtual��ȷ������������ʱ������ȷ�������߼���
         */
        ~Frustum() override = default;
    };
}
