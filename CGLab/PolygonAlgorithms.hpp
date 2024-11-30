/*
*
* �ļ�: Algorithms/PolygonAlgorithms.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ����������ֶ��������㷨����:
* 1. ScanLineFillAlgorithm - Xɨ��������㷨
* 2. SeedFill4Algorithm - ��������������㷨
* 3. SeedFill8Algorithm - ��������������㷨
* �����㷨�඼�̳���IPolygonAlgorithm�ӿ�
*/

#pragma once
#include "IPolygonAlgorithm.hpp"

namespace MyGraphics {
    namespace Algorithms {
        /**
         * Xɨ��������㷨��
         * ͨ�����µ�������ɨ��ķ�ʽ�Զ���ν������
         */
        class ScanLineFillAlgorithm : public IPolygonAlgorithm {
        public:
            /**
             * ��������õ����ص㼯
             * @param vertices: ����ζ�������
             * @return: ����������������꼯��
             */
            std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices) override;
        };

        /**
         * ��������������㷨��
         * �����ӵ㿪ʼ,�����������ĸ�������չ���
         */
        class SeedFill4Algorithm : public IPolygonAlgorithm {
        public:
            /**
             * ��������õ����ص㼯
             * @param vertices: ����ζ�������
             * @param seed: ���ӵ�����
             * @return: ����������������꼯��
             */
            std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices, const Point2D& seed) override;
        };

        /**
         * ��������������㷨��
         * �����ӵ㿪ʼ,����Χ�˸�������չ���
         */
        class SeedFill8Algorithm : public IPolygonAlgorithm {
        public:
            /**
             * ��������õ����ص㼯
             * @param vertices: ����ζ�������
             * @param seed: ���ӵ�����
             * @return: ����������������꼯��
             */
            std::vector<Point2D> GeneratePoints(const std::vector<Point2D>& vertices, const Point2D& seed) override;
        };
    }
}