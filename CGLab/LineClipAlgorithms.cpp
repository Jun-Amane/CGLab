/*
*
* 文件名: Algorithms/LineClipAlgorithms.cpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件实现了Cohen-Sutherland直线裁剪算法
* 通过编码的方式逐步裁剪直线段
*/

#include "pch.h"
#include "LineClipAlgorithms.hpp"

/**
* Cohen-Sutherland直线裁剪算法实现
* @param start 直线起点(会被修改为裁剪后的起点)
* @param end 直线终点(会被修改为裁剪后的终点)
* @param window 裁剪窗口
* @return 返回是否保留该直线
*/
bool CohenSutherlandAlgorithm::ClipLine(Point2D& start, Point2D& end, const ClipWindow& window)
{
    // 计算端点的区域编码
    unsigned char code1 = window.ComputeCode(start);
    unsigned char code2 = window.ComputeCode(end);
    bool accept = false;

    while (true) {
        if (!(code1 | code2)) {           // 两个端点的编码都是0,表示完全在窗口内
            accept = true;
            break;
        }
        else if (code1 & code2) {         // 两个端点在窗口的同一外侧,完全舍弃
            break;
        }
        else {
            // 计算直线与窗口的交点
            unsigned char code = code1 ? code1 : code2;  // 选择在窗口外的端点
            Point2D intersection;

            // 依次判断与哪个边界相交并计算交点
            if (code & ClipWindow::TOP) {           // 与上边界相交
                intersection.x = start.x + (end.x - start.x) *
                    (window.GetYmax() - start.y) / (end.y - start.y);
                intersection.y = window.GetYmax();
            }
            else if (code & ClipWindow::BOTTOM) {   // 与下边界相交
                intersection.x = start.x + (end.x - start.x) *
                    (window.GetYmin() - start.y) / (end.y - start.y);
                intersection.y = window.GetYmin();
            }
            else if (code & ClipWindow::RIGHT) {    // 与右边界相交
                intersection.y = start.y + (end.y - start.y) *
                    (window.GetXmax() - start.x) / (end.x - start.x);
                intersection.x = window.GetXmax();
            }
            else if (code & ClipWindow::LEFT) {     // 与左边界相交 
                intersection.y = start.y + (end.y - start.y) *
                    (window.GetXmin() - start.x) / (end.x - start.x);
                intersection.x = window.GetXmin();
            }

            // 用交点替换原来的端点
            if (code == code1) {          // 替换起点
                start = intersection;
                code1 = window.ComputeCode(start);
            }
            else {                        // 替换终点
                end = intersection;
                code2 = window.ComputeCode(end);
            }
        }
    }

    return accept;
}