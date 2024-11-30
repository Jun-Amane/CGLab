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
        if (!(code1 | code2)) {           // ��ȫ����
            accept = true;
            break;
        }
        else if (code1 & code2) {         // ��ȫ�ܾ�
            break;
        }
        else {
            // �����߶��ڴ�����
            unsigned char code = code1 ? code1 : code2;
            Point2D intersection;

            // ���㽻��
            if (code & ClipWindow::TOP) {           // ���ϱ߽��ཻ
                intersection.x = start.x + (end.x - start.x) *
                    (window.GetYmax() - start.y) / (end.y - start.y);
                intersection.y = window.GetYmax();
            }
            else if (code & ClipWindow::BOTTOM) {   // ���±߽��ཻ
                intersection.x = start.x + (end.x - start.x) *
                    (window.GetYmin() - start.y) / (end.y - start.y);
                intersection.y = window.GetYmin();
            }
            else if (code & ClipWindow::RIGHT) {    // ���ұ߽��ཻ
                intersection.y = start.y + (end.y - start.y) *
                    (window.GetXmax() - start.x) / (end.x - start.x);
                intersection.x = window.GetXmax();
            }
            else if (code & ClipWindow::LEFT) {     // ����߽��ཻ
                intersection.y = start.y + (end.y - start.y) *
                    (window.GetXmin() - start.x) / (end.x - start.x);
                intersection.x = window.GetXmin();
            }

            // �滻�˵�
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