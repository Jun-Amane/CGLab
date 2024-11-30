/*
 *
 * Models/ClipWindow.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 *
*/

#pragma once
#include "pch.h"
#include "Point2D.hpp"

namespace MyGraphics {
    class ClipWindow {
    public:
        ClipWindow(int xmin = 0, int ymin = 0, int xmax = 0, int ymax = 0)
            : m_xmin(xmin), m_ymin(ymin), m_xmax(xmax), m_ymax(ymax) {}

        void SetBounds(int xmin, int ymin, int xmax, int ymax) {
            m_xmin = xmin;
            m_ymin = ymin;
            m_xmax = xmax;
            m_ymax = ymax;
        }

        // �����ı���
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

        // ��ȡ�߽�ֵ
        int GetXmin() const { return m_xmin; }
        int GetYmin() const { return m_ymin; }
        int GetXmax() const { return m_xmax; }
        int GetYmax() const { return m_ymax; }

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

        // ������볣��
        static const unsigned char INSIDE = 0x00;  // 0000
        static const unsigned char LEFT = 0x01;  // 0001
        static const unsigned char RIGHT = 0x02;  // 0010
        static const unsigned char BOTTOM = 0x04;  // 0100
        static const unsigned char TOP = 0x08;  // 1000

    private:
        int m_xmin, m_ymin;  // �ü��������½�
        int m_xmax, m_ymax;  // �ü��������Ͻ�
    };
}
