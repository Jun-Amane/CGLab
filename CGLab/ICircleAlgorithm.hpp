/*
*
* �ļ���: Algorithms/ICircleAlgorithm.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 27/11/24
*
* ˵��: ���ļ�������Բ�����㷨�Ľӿ���
* ���о����Բ�����㷨����Ҫ�̳в�ʵ�ָýӿ�
*/

#pragma once
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
    namespace Algorithms {

        /**
         * Բ�����㷨�ĳ���ӿ���
         * ������Բ�����㷨�ı�׼�ӿ�
         * �ṩ���㷨�Ķ�̬��֧��
         */
        class ICircleAlgorithm {
        public:
            /**
             * ����������,ȷ����ȷ�Ķ�̬����
             */
            virtual ~ICircleAlgorithm() = default;

            /**
             * ���麯��,����Բ�ϵ����е�
             * @param centre Բ������
             * @param radius Բ�İ뾶
             * @return ����Բ�����е�����꼯��
             */
            virtual std::vector<Point2D> GeneratePoints(const Point2D& centre, int radius) = 0;
        };

    } // namespace Algorithms
} // namespace MyGraphics