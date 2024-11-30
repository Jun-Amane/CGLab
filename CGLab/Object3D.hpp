/*
* �ļ�: Models/Object3D.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�������Object3D��,������άͼ�ζ���Ļ�������
* ����:
* 1. �ṩ��άͼ�εĻ������ݽṹ(����ͱ�)
* 2. ֧����ά���α任
* 3. ��������ͼ(����ͼ/����ͼ/����ͼ)
*/

#pragma once
#include "Point3D.hpp"
#include "Point2D.hpp"
#include "Matrix4x4.hpp"
#include "Transform3D.hpp"
#include <vector>
#include <utility>

namespace MyGraphics {
    /**
     * Object3D�� - ��άͼ�ζ������
     * �ṩ��άͼ�εĻ������ܺ����ݽṹ
     */
    class Object3D {
    public:
        // �������������
        Object3D() = default;
        virtual ~Object3D() = default;

        /**
         * ����ά������б任
         * @param matrix: 4x4�任����
         */
        void Transform(const Matrix4x4& matrix);

        /**
         * ��ȡ���������ͼͶӰ�㼯
         * @param frontView: ����ͼ(ǰ��ͼ)�㼯,XOYƽ��ͶӰ
         * @param topView: ����ͼ�㼯,XOZƽ��ͶӰ
         * @param sideView: ����ͼ�㼯,YOZƽ��ͶӰ
         */
        void GetProjections(
            std::vector<Point2D>& frontView,   // ����ͼ(ǰ��ͼ)
            std::vector<Point2D>& topView,     // ����ͼ
            std::vector<Point2D>& sideView     // ����ͼ
        ) const;

        /**
         * ��ָ���������ͶӰͼ
         * @param pDC: �豸������ָ��
         * @param points: ͶӰ�㼯
         * @param rect: ��������
         * @param color: ������ɫ,Ĭ��Ϊ��ɫ
         */
        void DrawProjection(CDC* pDC, const std::vector<Point2D>& points,
            CRect rect, COLORREF color = RGB(0, 0, 0)) const;

        /**
         * ��ȡ��ά����ı߼���
         * @return: �ɶ��������Թ��ɵı߼���
         */
        const std::vector<std::pair<int, int>>& GetEdges() const { return m_edges; }

        /**
         * ��ȡ��ά����Ķ��㼯��
         * @return: ��ά��ļ���
         */
        const std::vector<Point3D>& GetVertices() const { return m_vertices; }

    protected:
        std::vector<Point3D> m_vertices;               // �洢��ά��������ж���
        std::vector<std::pair<int, int>> m_edges;      // �洢�ߵ���Ϣ,ÿ��������������������ʾ
    };
}