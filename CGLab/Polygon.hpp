/*
* �ļ�: Models/Polygon.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�������Polygon��,���ڶ���ε����ɡ���䡢�ü��ͱ任
* �ص�:
* 1. �̳���GraphicsObject����
* 2. ֧��ɨ���ߺ����������������㷨
* 3. ֧��Weiler-Atherton����βü��㷨
* 4. ֧�ֻ����Ķ�ά���α任
*/

#pragma once
#include "Point2D.hpp"
#include "Matrix3x3.hpp"
#include "Transform2D.hpp"
#include "GraphicsObject.hpp"
#include "IPolygonAlgorithm.hpp"
#include <memory>

namespace MyGraphics {
    /**
     * Polygon�� - �����ͼ�ζ���
     * �ṩ����εĹ�������䡢�ü��ͱ任����
     */
    class Polygon : public GraphicsObject {
    public:
        /**
         * ����֧�ֵ��㷨����
         */
        enum Algorithm {
            ALGO_SCANLINE,       // x-ɨ��������㷨
            ALGO_SEEDFILL_4,     // ��������������㷨
            ALGO_SEEDFILL_8,     // ��������������㷨
            ALGO_WEILER_ATHERTON // Weiler-Atherton����βü��㷨
        };

        // �������������
        Polygon();
        ~Polygon() override = default;

        /**
         * ������������
         */
        void SetAlgorithm(Algorithm algo);                     // ���ô����㷨
        void AddVertex(const Point2D& point);                  // ��Ӷ���
        void SetSeed(const Point2D& seed);                     // �������ӵ�
        void Close();                                          // ��ն����
        bool IsClosed() const { return m_closed; }             // �ж��Ƿ��ѱպ�
        void GeneratePoints() override;                        // ���ɹ��ɶ���εĵ㼯
        const std::vector<Point2D>& GetVertices() const { return m_vertices; }  // ��ȡ��������

        /**
         * ������غ���
         */
        void Draw(CDC* pDC) override;                          // �������������
        void DrawVertex(CDC* pDC, const Point2D& point);       // ���ƶ���
        void DrawSeed(CDC* pDC, const Point2D& point);        // �������ӵ�

        /**
         * ���������غ���
         */
        bool HasSeed() const { return m_hasSeed; }            // ����Ƿ��������ӵ�

        /**
         * �任�Ͳü���غ���
         */
        void Transform(const Matrix3x3& matrix);              // �Զ���ν��б任
        void SetClipWindow(const ClipWindow& window) { m_clipWindow = window; }  // ���òü�����
        ClipWindow& GetClipWindow() { return m_clipWindow; }  // ��ȡ�ü�����

    private:
        Algorithm m_algorithm;           // ��ǰʹ�õ��㷨����
        std::vector<Point2D> m_vertices; // ����ζ��㼯��

        // ��ʾ����
        static const int VERTEX_SIZE = 4;  // ������ʾ�Ĵ�С(����)
        static const int SEED_SIZE = 6;    // ���ӵ���ʾ�Ĵ�С(����)

        // ����������
        bool m_hasSeed = false;         // �Ƿ����������ӵ��־
        Point2D m_seed;                 // ���ӵ�����

        // �����״̬
        bool m_closed;                  // ����αպϱ�־
        std::vector<Point2D> m_points;  // ���㼯

        // �ü����
        ClipWindow m_clipWindow;                // �ü�����
        std::vector<Point2D> m_originalVertices; // �ü�ǰ��ԭʼ����
        bool m_isClipped;                       // �ü�״̬��־

        // �㷨����(Strategyģʽ)
        std::unique_ptr<Algorithms::IPolygonAlgorithm> m_polygonAlgorithm;

    protected:
        /**
         * �Զ���ζ�����б任����
         * @param matrix: �任����
         */
        void TransformVertices(const Matrix3x3& matrix);
    };
}