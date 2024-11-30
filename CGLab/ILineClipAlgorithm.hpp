/*
*
* �ļ���: Algorithms/ILineClipAlgorithm.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�������ֱ�߲ü��㷨�Ľӿ���
* ���о����ֱ�߲ü��㷨����Ҫ�̳в�ʵ�ָýӿ�
*/

#pragma once
#include "Point2D.hpp"
#include "ClipWindow.hpp"

namespace MyGraphics {
    namespace Algorithms {

        /**
         * ֱ�߲ü��㷨�ĳ���ӿ���
         * ������ֱ�߲ü��㷨�ı�׼�ӿ�
         * �ṩ���㷨�Ķ�̬��֧��
         */
        class ILineClipAlgorithm {
        public:
            /**
             * ����������,ȷ����ȷ�Ķ�̬����
             */
            virtual ~ILineClipAlgorithm() = default;

            /**
             * ���麯��,��ֱ�߽��вü�
             * @param start ֱ�ߵ��������(�����޸�Ϊ�ü�������)
             * @param end ֱ�ߵ��յ�����(�����޸�Ϊ�ü�����յ�)
             * @param window �ü����ڶ���
             * @return �����Ƿ�����ֱ��
             *         true - ֱ����ü������ཻ,�����ü���Ĳ���
             *         false - ֱ����ȫ�ڲü�������,Ӧ�ñ���ȫ�ü�
             */
            virtual bool ClipLine(Point2D& start, Point2D& end, const ClipWindow& window) = 0;
        };

    } // namespace Algorithms
} // namespace MyGraphics