/*
*
* �ļ���: Algorithms/IEllipseAlgorithm.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 28/11/24
*
* ˵��: ���ļ���������Բ�����㷨�Ľӿ���
* ���о������Բ�����㷨����Ҫ�̳в�ʵ�ָýӿ�
*/

#pragma once
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
    namespace Algorithms {

        /**
         * ��Բ�����㷨�ĳ���ӿ���
         * ��������Բ�����㷨�ı�׼�ӿ�
         * �ṩ���㷨�Ķ�̬��֧��
         */
        class IEllipseAlgorithm {
        public:
            /**
             * ����������,ȷ����ȷ�Ķ�̬����
             */
            virtual ~IEllipseAlgorithm() = default;

            /**
             * ���麯��,������Բ�ϵ����е�
             * @param center ��Բ���ĵ������
             * @param a ��Բ����ĳ���
             * @param b ��Բ����ĳ���
             * @return ������Բ�����е�����꼯��
             */
            virtual std::vector<Point2D> GeneratePoints(const Point2D& center, int a, int b) = 0;
        };

    } // namespace Algorithms
} // namespace MyGraphics