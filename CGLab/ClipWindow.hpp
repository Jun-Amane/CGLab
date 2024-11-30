/*
*
* 文件: Models/ClipWindow.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件定义了裁剪窗口类ClipWindow
* 用于:
* 1. 定义二维平面上的矩形裁剪区域
* 2. 支持Cohen-Sutherland线段裁剪算法
* 3. 支持Weiler-Atherton多边形裁剪算法
*/

#pragma once
#include "pch.h"
#include "Point2D.hpp"

namespace MyGraphics {
    /**
     * ClipWindow类 - 定义裁剪窗口
     * 采用四位区域编码方式标识点的位置
     */
    class ClipWindow {
    public:
        /**
         * 构造函数 - 初始化裁剪窗口的边界
         * @param xmin: 左边界x坐标
         * @param ymin: 下边界y坐标
         * @param xmax: 右边界x坐标
         * @param ymax: 上边界y坐标
         */
        ClipWindow(int xmin = 0, int ymin = 0, int xmax = 0, int ymax = 0)
            : m_xmin(xmin), m_ymin(ymin), m_xmax(xmax), m_ymax(ymax) {}

        /**
         * 设置裁剪窗口的边界
         * @param xmin: 左边界x坐标
         * @param ymin: 下边界y坐标
         * @param xmax: 右边界x坐标
         * @param ymax: 上边界y坐标
         */
        void SetBounds(int xmin, int ymin, int xmax, int ymax) {
            m_xmin = xmin;
            m_ymin = ymin;
            m_xmax = xmax;
            m_ymax = ymax;
        }

        /**
         * 计算点相对于裁剪窗口的区域编码
         * @param point: 待计算编码的点
         * @return: 4位二进制编码,每位表示一个边界
         * 使用Cohen-Sutherland算法的编码方案
         */
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

        /**
         * 获取裁剪窗口的边界值
         */
        int GetXmin() const { return m_xmin; }
        int GetYmin() const { return m_ymin; }
        int GetXmax() const { return m_xmax; }
        int GetYmax() const { return m_ymax; }

        /**
         * 在设备上下文中绘制裁剪窗口
         * @param pDC: 设备上下文指针
         * 使用蓝色虚线绘制矩形框
         */
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

        /**
         * Cohen-Sutherland算法的区域编码常量
         * 使用4位二进制表示点相对于裁剪窗口的位置
         */
        static const unsigned char INSIDE = 0x00;  // 0000 点在窗口内部
        static const unsigned char LEFT = 0x01;    // 0001 点在窗口左侧
        static const unsigned char RIGHT = 0x02;   // 0010 点在窗口右侧
        static const unsigned char BOTTOM = 0x04;  // 0100 点在窗口下方
        static const unsigned char TOP = 0x08;     // 1000 点在窗口上方

    private:
        int m_xmin, m_ymin;  // 裁剪窗口左下角坐标
        int m_xmax, m_ymax;  // 裁剪窗口右上角坐标
    };
}
