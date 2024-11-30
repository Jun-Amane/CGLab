/*
* �ļ���: Algorithms/IPolygonAlgorithm.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ������˶���δ����㷨�Ļ����ӿ���
* ������������ɡ����Ͳü�������㷨
*/

#pragma once
#include "Point2D.hpp"
#include "ClipWindow.hpp"
#include <vector>

namespace MyGraphics {
    namespace Algorithms {

        /**
         * ������㷨�ĳ���ӿ���
         * �ṩ�˶���δ�����صĻ������ܽӿ�:
         * - ��������ɺ����
         * - �������ε�λ�ù�ϵ�ж�
         * - ����βü�
         */
        class IPolygonAlgorithm {
        public:
            /**
             * ����������,ȷ����ȷ�Ķ�̬����
             */
            virtual ~IPolygonAlgorithm() = default;

            /**
             * ���ɶ�����ϵĵ�(�����ӵ�汾)
             * ��Ҫ����ɨ�������Ȳ���Ҫ���ӵ���㷨
             * @param vertices ����ζ�������
             * @return ���ض���������е�����꼯��
             */
            virtual std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices) {
                return std::vector<Point2D>();
            }

            /**
             * ���ɶ�����ϵĵ�(�����ӵ�汾)
             * ��Ҫ��������������Ҫ���ӵ���㷨
             * @param vertices ����ζ�������
             * @param seed ���ӵ�����
             * @return ���ض���������е�����꼯��
             */
            virtual std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices, const Point2D& seed) {
                return std::vector<Point2D>();
            }

            /**
             * �жϵ��Ƿ��ڶ�����ڲ�
             * @param p ���жϵĵ�
             * @param vertices ����ζ�������
             * @return true - ���ڶ�����ڲ�
             *         false - ���ڶ�����ⲿ��߽���
             */
            bool isPointInPolygon(const Point2D& p, const std::vector<Point2D>& vertices);

            /**
             * �Զ���ν��вü�
             * @param vertices ����ζ�������
             * @param window �ü�����
             * @return �ü���Ķ���ζ�������
             */
            virtual std::vector<Point2D> ClipPolygon(const std::vector<Point2D>& vertices, const ClipWindow& window) {
                return std::vector<Point2D>();
            }
        };

    } // namespace Algorithms
} // namespace MyGraphics