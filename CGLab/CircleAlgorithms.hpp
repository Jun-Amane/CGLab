/*
 *
 * �ļ���: Algorithms/CircleAlgorithms.hpp
 * ����: Ziyu ZHOU @ SDAU
 * ����: 27/11/24
 *
 * ˵��: ���ļ�������Բ�����㷨�ľ���ʵ����
 * �����е�Բ�㷨��BresenhamԲ�㷨����ʵ��
 * �����඼�̳���ICircleAlgorithm�ӿ���
 */

#pragma once
#include "ICircleAlgorithm.hpp"

namespace MyGraphics {
    namespace Algorithms {

        /**
         * �е�Բ�����㷨��
         * ʹ���е��㷨����Բ�ϵ����ص�
         * ͨ���ж��е���Բ��λ�ù�ϵ��ѡ����һ�����ص�
         */
        class MidpointCircleAlgorithm : public ICircleAlgorithm {
        public:
            /**
             * ����Բ�ϵ����е�����
             * @param centre Բ������
             * @param radius Բ�İ뾶
             * @return ����Բ�����е�����꼯��
             */
            std::vector<Point2D> GeneratePoints(const Point2D& centre, int radius) override;

        private:
            /**
             * ����Բ�İ˷ֶԳ������ɶԳƵ�
             * @param points �洢���ɵ������
             * @param center Բ������
             * @param x ��ǰ���xƫ����
             * @param y ��ǰ���yƫ����
             */
            void AddCirclePoints(std::vector<Point2D>& points, const Point2D& center, int x, int y);
        };

        /**
         * BresenhamԲ�����㷨��
         * ʹ��Bresenham�㷨����Բ�ϵ����ص�
         * ͨ���������ۼ���ѡ����һ�����ص�,���⸡������
         */
        class BresenhamCircleAlgorithm : public ICircleAlgorithm {
        public:
            /**
             * ����Բ�ϵ����е�����
             * @param centre Բ������
             * @param radius Բ�İ뾶
             * @return ����Բ�����е�����꼯��
             */
            std::vector<Point2D> GeneratePoints(const Point2D& centre, int radius) override;

        private:
            /**
             * ����Բ�İ˷ֶԳ������ɶԳƵ�
             * @param points �洢���ɵ������
             * @param center Բ������
             * @param x ��ǰ���xƫ����
             * @param y ��ǰ���yƫ����
             */
            void AddCirclePoints(std::vector<Point2D>& points, const Point2D& center, int x, int y);
        };

    } // namespace Algorithms
} // namespace MyGraphics