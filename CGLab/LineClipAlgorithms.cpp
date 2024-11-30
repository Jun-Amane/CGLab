/*
 *
 * Algorithms/LineClipAlgorithms.cpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 *
*/


#include "pch.h"
#include "LineClipAlgorithms.hpp"

bool CohenSutherlandAlgorithm::ClipLine(Point2D& start, Point2D& end, const ClipWindow& window)
{
    unsigned char code1 = window.ComputeCode(start);
    unsigned char code2 = window.ComputeCode(end);
    bool accept = false;

    while (true) {
        if (!(code1 | code2)) {           // 完全接受
            accept = true;
            break;
        }
        else if (code1 & code2) {         // 完全拒绝
            break;
        }
        else {
            // 部分线段在窗口内
            unsigned char code = code1 ? code1 : code2;
            Point2D intersection;

            // 计算交点
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

            // 替换端点
            if (code == code1) {
                start = intersection;
                code1 = window.ComputeCode(start);
            }
            else {
                end = intersection;
                code2 = window.ComputeCode(end);
            }
        }
    }

    return accept;
}
