/*
*
* �ļ���: Algorithms/LineAlgorithms.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 26/11/24
*
* ˵��: ���ļ�����������ֱ�������㷨�ľ���ʵ����
* �����඼�̳���ILineAlgorithm�ӿ�
*/

#pragma once
#include "ILineAlgorithm.hpp"

namespace MyGraphics {
    namespace Algorithms {

        /**
         * DDAֱ�������㷨��
         * Digital Differential Analyzer(��ֵ΢�ַ�����)
         * ʹ�ø���������,ʵ�ּ򵥵�Ч�ʽϵ�
         */
        class DDALineAlgorithm : public ILineAlgorithm {
        public:
            /**
             * ����ֱ���ϵ����е�
             * @param start ֱ�����
             * @param end ֱ���յ�
             * @return ����ֱ�������е�����꼯��
             */
            std::vector<Point2D> GeneratePoints(const Point2D& start, const Point2D& end) override;
        };

        /**
         * �е�ֱ�������㷨��
         * �����е��б��˼��,ʹ����������
         * Ч�ʸ���DDA�㷨
         */
        class MidpointLineAlgorithm : public ILineAlgorithm {
        public:
            /**
             * ����ֱ���ϵ����е�
             * @param start ֱ�����
             * @param end ֱ���յ�
             * @return ����ֱ�������е�����꼯��
             */
            std::vector<Point2D> GeneratePoints(const Point2D& start, const Point2D& end) override;
        };

        /**
         * Bresenhamֱ�������㷨��
         * ʹ������ۻ���˼��,��ȫʹ����������
         * �����Ч��ֱ�������㷨֮һ
         */
        class BresenhamLineAlgorithm : public ILineAlgorithm {
        public:
            /**
             * ����ֱ���ϵ����е�
             * @param start ֱ�����
             * @param end ֱ���յ�
             * @return ����ֱ�������е�����꼯��
             */
            std::vector<Point2D> GeneratePoints(const Point2D& start, const Point2D& end) override;
        };

    } // namespace Algorithms
} // namespace MyGraphics