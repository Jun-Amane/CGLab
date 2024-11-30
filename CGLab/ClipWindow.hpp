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

        // 计算点的编码
        unsigned char ComputeCode(const Point2D& point) const {
            unsigned char code = INSIDE;  // 初始化为内部

            if (point.x < m_xmin)        // 左边
                code |= LEFT;
            else if (point.x > m_xmax)   // 右边
                code |= RIGHT;

            if (point.y < m_ymin)        // 下边
                code |= BOTTOM;
            else if (point.y > m_ymax)   // 上边
                code |= TOP;

            return code;
        }

        // 获取边界值
        int GetXmin() const { return m_xmin; }
        int GetYmin() const { return m_ymin; }
        int GetXmax() const { return m_xmax; }
        int GetYmax() const { return m_ymax; }

        void Draw(CDC* pDC) const {
            // 使用虚线绘制裁剪窗口
            CPen pen(PS_DASH, 1, RGB(0, 0, 255));  // 蓝色虚线
            CPen* pOldPen = pDC->SelectObject(&pen);

            pDC->MoveTo(m_xmin, m_ymin);
            pDC->LineTo(m_xmax, m_ymin);
            pDC->LineTo(m_xmax, m_ymax);
            pDC->LineTo(m_xmin, m_ymax);
            pDC->LineTo(m_xmin, m_ymin);

            pDC->SelectObject(pOldPen);
        }

        // 区域编码常量
        static const unsigned char INSIDE = 0x00;  // 0000
        static const unsigned char LEFT = 0x01;  // 0001
        static const unsigned char RIGHT = 0x02;  // 0010
        static const unsigned char BOTTOM = 0x04;  // 0100
        static const unsigned char TOP = 0x08;  // 1000

    private:
        int m_xmin, m_ymin;  // 裁剪窗口左下角
        int m_xmax, m_ymax;  // 裁剪窗口右上角
    };
}
