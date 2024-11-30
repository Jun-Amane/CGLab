/*
*
* �ļ�: Models/Circle.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 27/11/24
*
* ˵��: ���ļ�������Circle��,����Բ�����ɺͻ���
* �ص�:
* 1. �̳���GraphicsObject����
* 2. ֧���е��Bresenham����Բ�����㷨
* 3. ʹ��Strategy���ģʽʵ���㷨�л�
*/

#pragma once
#include "Point2D.hpp"
#include "GraphicsObject.hpp"
#include "ICircleAlgorithm.hpp"
#include <memory>

namespace MyGraphics {
    /**
     * Circle�� - Բ��ͼ�ζ���
     * �̳���GraphicsObject����
     */
    class Circle : public GraphicsObject {
    public:
        /**
         * ����֧�ֵ�Բ�����㷨����
         */
        enum Algorithm {
            ALGO_MIDPOINT,    // �е�Բ�����㷨
            ALGO_BRESENHAM    // BresenhamԲ�����㷨
        };

        // �������������
        Circle();
        ~Circle() override = default;

        /**
         * ����Բ�������㷨
         * @param algo: �㷨����(ALGO_MIDPOINT��ALGO_BRESENHAM)
         */
        void SetAlgorithm(Algorithm algo);

        /**
         * ����Բ�Ļ�������
         * @param centre: Բ������
         * @param radius: Բ�İ뾶
         */
        void SetParameters(const Point2D& centre, int radius);

        /**
         * ����Բ�ϵ����е�
         * ����ѡ���㷨��GeneratePoints����
         */
        void GeneratePoints();

        /**
         * ��ָ���豸�����Ļ���Բ
         * @param pDC: �豸������ָ��
         */
        void Draw(CDC* pDC) override;

    private:
        Algorithm m_algorithm;      // ��ǰʹ�õ��㷨����
        Point2D m_centre;          // Բ������
        int m_radius;              // Բ�İ뾶
        std::vector<Point2D> m_points;  // �洢Բ�ϵ����е�

        // Բ�����㷨���������ָ��
        // ʹ��Strategyģʽʵ���㷨�л�
        std::unique_ptr<Algorithms::ICircleAlgorithm> m_circleAlgorithm;
    };
}