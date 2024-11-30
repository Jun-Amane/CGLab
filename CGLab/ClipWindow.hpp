/*
*
* �ļ�: Models/ClipWindow.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ������˲ü�������ClipWindow
* ����:
* 1. �����άƽ���ϵľ��βü�����
* 2. ֧��Cohen-Sutherland�߶βü��㷨
* 3. ֧��Weiler-Atherton����βü��㷨
*/

#pragma once
#include "pch.h"
#include "Point2D.hpp"

namespace MyGraphics {
    /**
     * ClipWindow�� - ����ü�����
     * ������λ������뷽ʽ��ʶ���λ��
     */
    class ClipWindow {
    public:
        /**
         * ���캯�� - ��ʼ���ü����ڵı߽�
         * @param xmin: ��߽�x����
         * @param ymin: �±߽�y����
         * @param xmax: �ұ߽�x����
         * @param ymax: �ϱ߽�y����
         */
        ClipWindow(int xmin = 0, int ymin = 0, int xmax = 0, int ymax = 0)
            : m_xmin(xmin), m_ymin(ymin), m_xmax(xmax), m_ymax(ymax) {}

        /**
         * ���òü����ڵı߽�
         * @param xmin: ��߽�x����
         * @param ymin: �±߽�y����
         * @param xmax: �ұ߽�x����
         * @param ymax: �ϱ߽�y����
         */
        void SetBounds(int xmin, int ymin, int xmax, int ymax) {
            m_xmin = xmin;
            m_ymin = ymin;
            m_xmax = xmax;
            m_ymax = ymax;
        }

        /**
         * ���������ڲü����ڵ��������
         * @param point: ���������ĵ�
         * @return: 4λ�����Ʊ���,ÿλ��ʾһ���߽�
         * ʹ��Cohen-Sutherland�㷨�ı��뷽��
         */
        unsigned char ComputeCode(const Point2D& point) const {
            unsigned char code = INSIDE;  // ��ʼ��Ϊ�ڲ�
            if (point.x < m_xmin)        // ���
                code |= LEFT;
            else if (point.x > m_xmax)   // �ұ�
                code |= RIGHT;
            if (point.y < m_ymin)        // �±�
                code |= BOTTOM;
            else if (point.y > m_ymax)   // �ϱ�
                code |= TOP;
            return code;
        }

        /**
         * ��ȡ�ü����ڵı߽�ֵ
         */
        int GetXmin() const { return m_xmin; }
        int GetYmin() const { return m_ymin; }
        int GetXmax() const { return m_xmax; }
        int GetYmax() const { return m_ymax; }

        /**
         * ���豸�������л��Ʋü�����
         * @param pDC: �豸������ָ��
         * ʹ����ɫ���߻��ƾ��ο�
         */
        void Draw(CDC* pDC) const {
            // ʹ�����߻��Ʋü�����
            CPen pen(PS_DASH, 1, RGB(0, 0, 255));  // ��ɫ����
            CPen* pOldPen = pDC->SelectObject(&pen);
            pDC->MoveTo(m_xmin, m_ymin);
            pDC->LineTo(m_xmax, m_ymin);
            pDC->LineTo(m_xmax, m_ymax);
            pDC->LineTo(m_xmin, m_ymax);
            pDC->LineTo(m_xmin, m_ymin);
            pDC->SelectObject(pOldPen);
        }

        /**
         * Cohen-Sutherland�㷨��������볣��
         * ʹ��4λ�����Ʊ�ʾ������ڲü����ڵ�λ��
         */
        static const unsigned char INSIDE = 0x00;  // 0000 ���ڴ����ڲ�
        static const unsigned char LEFT = 0x01;    // 0001 ���ڴ������
        static const unsigned char RIGHT = 0x02;   // 0010 ���ڴ����Ҳ�
        static const unsigned char BOTTOM = 0x04;  // 0100 ���ڴ����·�
        static const unsigned char TOP = 0x08;     // 1000 ���ڴ����Ϸ�

    private:
        int m_xmin, m_ymin;  // �ü��������½�����
        int m_xmax, m_ymax;  // �ü��������Ͻ�����
    };
}
