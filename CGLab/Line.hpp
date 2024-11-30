/*
*
* �ļ�: Models/Line.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 26/11/24
*
* ˵��: ���ļ�������Line��,����ֱ�ߵ����ɺͻ���
* �ص�:
* 1. �̳���GraphicsObject����
* 2. ֧�����������㷨��һ�ֲü��㷨
* 3. ʹ��Strategy���ģʽʵ���㷨�л�
*/

#pragma once
#include "Point2D.hpp"
#include "GraphicsObject.hpp"
#include "ILineAlgorithm.hpp"
#include "ILineClipAlgorithm.hpp"
#include "ClipWindow.hpp"
#include <memory>

namespace MyGraphics {
    /**
     * Line�� - ֱ��ͼ�ζ���
     * �̳���GraphicsObject����
     */
    class Line : public GraphicsObject {
    public:
        /**
         * ����֧�ֵ�ֱ�����ɺͲü��㷨����
         */
        enum Algorithm {
            ALGO_DDA,             // DDAֱ�������㷨
            ALGO_MIDPOINT,        // �е�ֱ�������㷨
            ALGO_BRESENHAM,       // Bresenhamֱ�������㷨
            ALGO_COHEN_SUTHERLAND // Cohen-Sutherlandֱ�߲ü��㷨
        };

        // �������������
        Line();
        ~Line() override = default;

        /**
         * ����ֱ�ߵ����ɻ�ü��㷨
         * @param algo: ѡ����㷨����
         */
        void SetAlgorithm(Algorithm algo);

        /**
         * ����ֱ�ߵ������յ�
         * @param start: �������
         * @param end: �յ�����
         */
        void SetPoints(const Point2D& start, const Point2D& end);

        /**
         * ���òü�����(����Cohen-Sutherland�㷨)
         * @param window: �ü����ڶ���
         */
        void SetClipWindow(const ClipWindow& window) { m_clipWindow = window; }

        /**
         * ����ѡ���㷨����ֱ�ߵĵ㼯
         * ���ڲü��㷨,���Ƚ��вü�����
         */
        void GeneratePoints();

        /**
         * ��ָ���豸�����Ļ���ֱ��
         * @param pDC: �豸������ָ��
         */
        void Draw(CDC* pDC) override;

    private:
        Algorithm m_algorithm;      // ��ǰʹ�õ��㷨����
        Point2D m_startPoint;      // ԭʼ���
        Point2D m_endPoint;        // ԭʼ�յ�
        Point2D m_clippedStart;    // �ü�������
        Point2D m_clippedEnd;      // �ü�����յ�
        std::vector<Point2D> m_points;  // �洢ֱ���ϵ����е�
        ClipWindow m_clipWindow;    // �ü�����
        bool m_isClipped;          // ����߶��Ƿ񱻲ü�

        // ʹ��Strategyģʽʵ�ֵ��㷨����
        std::unique_ptr<Algorithms::ILineAlgorithm> m_lineAlgorithm;       // ֱ�������㷨
        std::unique_ptr<Algorithms::ILineClipAlgorithm> m_clipAlgorithm;   // ֱ�߲ü��㷨
    };
}
