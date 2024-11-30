/*
*
* �ļ�: Models/Ellipse.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 28/11/24
*
* ˵��: ���ļ�������Ellipse��,������Բ�����ɺͻ���
* �ص�:
* 1. �̳���GraphicsObject����
* 2. Ŀǰ��֧��Bresenham��Բ�����㷨
* 3. ʹ��Strategy���ģʽʵ���㷨�л�(Ϊ������չ�㷨��׼��)
*/

#pragma once
#include "Point2D.hpp"
#include "GraphicsObject.hpp"
#include "IEllipseAlgorithm.hpp"
#include <memory>

namespace MyGraphics {
    /**
     * Ellipse�� - ��Բͼ�ζ���
     * �̳���GraphicsObject����
     */
    class Ellipse : public GraphicsObject {
    public:
        /**
         * ����֧�ֵ���Բ�����㷨����
         * Ŀǰ��֧��Bresenham�㷨
         */
        enum Algorithm {
            ALGO_BRESENHAM    // Bresenham��Բ�����㷨
        };

        // �������������
        Ellipse();
        ~Ellipse() override = default;

        /**
         * ������Բ�������㷨
         * @param algo: �㷨����(��ǰ��֧��ALGO_BRESENHAM)
         */
        void SetAlgorithm(Algorithm algo);

        /**
         * ������Բ�Ļ�������
         * @param center: ��Բ���ĵ�����
         * @param a: ��Բ���᳤��(semi-major axis)
         * @param b: ��Բ���᳤��(semi-minor axis)
         */
        void SetParameters(const Point2D& center, int a, int b);

        /**
         * ������Բ�ϵ����е�
         * ����ѡ���㷨��GeneratePoints����
         */
        void GeneratePoints();

        /**
         * ��ָ���豸�����Ļ�����Բ
         * @param pDC: �豸������ָ��
         */
        void Draw(CDC* pDC) override;

    private:
        Algorithm m_algorithm;      // ��ǰʹ�õ��㷨����
        Point2D m_center;          // ��Բ���ĵ�����
        int m_a;                   // ���᳤��(semi-major axis)
        int m_b;                   // ���᳤��(semi-minor axis)
        std::vector<Point2D> m_points;  // �洢��Բ�ϵ����е�

        // ��Բ�����㷨���������ָ��
        // ʹ��Strategyģʽʵ���㷨�л�
        std::unique_ptr<Algorithms::IEllipseAlgorithm> m_ellipseAlgorithm;
    };
}