/*
*
* �ļ�: Algorithms/WeilerAthertonAlgorithm.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�������Weiler-Atherton����βü��㷨��
* ���㷨��Ҫ���ڲü������,ͨ���ݹ�ϸ�ֵķ�ʽ�������ε�ÿ����
* ʹ�����������ȷ������ü����ڵ����λ�ù�ϵ
*/

#pragma once
#include "Point2D.hpp"
#include "IPolygonAlgorithm.hpp" 
#include "ClipWindow.hpp"
#include <list>

namespace MyGraphics {
    namespace Algorithms {
        /**
         * Weiler-Atherton����βü��㷨��
         * �̳���IPolygonAlgorithm�ӿ�
         */
        class WeilerAthertonAlgorithm : public IPolygonAlgorithm {
        public:
            /**
             * �Զ���ν��вü���������
             * @param vertices: �������εĶ�������
             * @param window: �ü�����
             * @return: ���زü���Ķ���ζ�������
             */
            std::vector<Point2D> ClipPolygon(
                const std::vector<Point2D>& vertices,
                const ClipWindow& window) override;

        private:
            // ������볣������
            static const int CODE_C = 0x0000;  // �ڲ��������:0000
            static const int CODE_N = 0x0008;  // �����������:1000
            static const int CODE_S = 0x0004;  // �Ϸ��������:0100
            static const int CODE_E = 0x0002;  // �����������:0010 
            static const int CODE_W = 0x0001;  // �����������:0001

            /**
             * �������������
             * @param point: ������ĵ�
             * @param window: �ü�����
             * @return: ���ص���������
             */
            int ComputeCode(const Point2D& point, const ClipWindow& window);

            /**
             * ����һ���ߵĲü�
             * @param start: �ߵ����
             * @param end: �ߵ��յ�
             * @param window: �ü�����
             * @param result: �洢�ü�����ĵ㼯
             */
            void ClipEdge(const Point2D& start, const Point2D& end,
                const ClipWindow& window,
                std::vector<Point2D>& result);

            /**
             * ������봰�ڱ߽�Ľ���
             * @param p1: �ߵ����
             * @param p2: �ߵ��յ�
             * @param edge_code: �߽����
             * @param window: �ü�����
             * @return: ���ؽ�������
             */
            Point2D ComputeIntersection(
                const Point2D& p1, const Point2D& p2,
                int edge_code, const ClipWindow& window);
        };
    }
}