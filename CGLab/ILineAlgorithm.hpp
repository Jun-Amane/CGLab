/*
*
* �ļ���: Algorithms/ILineAlgorithm.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 26/11/24
*
* ˵��: ���ļ�������ֱ�������㷨�Ľӿ���
* ���о����ֱ�������㷨����Ҫ�̳в�ʵ�ָýӿ�
*/

#pragma once
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
    namespace Algorithms {

        /**
         * ֱ�������㷨�ĳ���ӿ���
         * ������ֱ�������㷨�ı�׼�ӿ�
         * �ṩ���㷨�Ķ�̬��֧��
         */
        class ILineAlgorithm {
        public:
            /**
             * ����������,ȷ����ȷ�Ķ�̬����
             */
            virtual ~ILineAlgorithm() = default;

            /**
             * ���麯��,����ֱ���ϵ����е�
             * @param start ֱ�ߵ��������
             * @param end ֱ�ߵ��յ�����
             * @return ����ֱ�������е�����꼯��
             */
            virtual std::vector<Point2D> GeneratePoints(const Point2D& start, const Point2D& end) = 0;
        };

    } // namespace Algorithms
} // namespace MyGraphics