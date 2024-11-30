/*
*
* �ļ���: Algorithms/EllipseAlgorithms.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 28/11/24
*
* ˵��: ���ļ���������Բ�����㷨�ľ���ʵ����
* ʵ���˻���Bresenham�㷨����Բ���ɷ���
*/

#pragma once
#include "IEllipseAlgorithm.hpp"

namespace MyGraphics {
    namespace Algorithms {

        /**
         * Bresenham��Բ�����㷨��
         * �̳���IEllipseAlgorithm�ӿ�
         * ʹ��Bresenham�㷨��˼��������Բ�ϵ����ص�
         * ����Բ��Ϊ��������ֱ���,�������ķֶԳ���
         */
        class BresenhamEllipseAlgorithm : public IEllipseAlgorithm {
        public:
            /**
             * ������Բ�ϵ����е�����
             * @param center ��Բ���ĵ�����
             * @param a ��Բ���᳤��
             * @param b ��Բ���᳤��
             * @return ������Բ�����е�����꼯��
             */
            std::vector<Point2D> GeneratePoints(const Point2D& center, int a, int b) override;

        private:
            /**
             * ������Բ���ķֶԳ������ɶԳƵ�
             * @param points �洢���ɵ������
             * @param center ��Բ���ĵ�����
             * @param x ��ǰ���xƫ����
             * @param y ��ǰ���yƫ����
             */
            void AddPoints(std::vector<Point2D>& points, const Point2D& center, int x, int y);
        };

    } // namespace Algorithms
} // namespace MyGraphics