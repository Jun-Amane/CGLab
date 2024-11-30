/*
*
* �ļ���: Algorithms/LineClipAlgorithms.cpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�ʵ����Cohen-Sutherlandֱ�߲ü��㷨
* ͨ������ķ�ʽ�𲽲ü�ֱ�߶�
*/

#include "pch.h"
#include "LineClipAlgorithms.hpp"

/**
* Cohen-Sutherlandֱ�߲ü��㷨ʵ��
* @param start ֱ�����(�ᱻ�޸�Ϊ�ü�������)
* @param end ֱ���յ�(�ᱻ�޸�Ϊ�ü�����յ�)
* @param window �ü�����
* @return �����Ƿ�����ֱ��
*/
bool CohenSutherlandAlgorithm::ClipLine(Point2D& start, Point2D& end, const ClipWindow& window)
{
    // ����˵���������
    unsigned char code1 = window.ComputeCode(start);
    unsigned char code2 = window.ComputeCode(end);
    bool accept = false;

    while (true) {
        if (!(code1 | code2)) {           // �����˵�ı��붼��0,��ʾ��ȫ�ڴ�����
            accept = true;
            break;
        }
        else if (code1 & code2) {         // �����˵��ڴ��ڵ�ͬһ���,��ȫ����
            break;
        }
        else {
            // ����ֱ���봰�ڵĽ���
            unsigned char code = code1 ? code1 : code2;  // ѡ���ڴ�����Ķ˵�
            Point2D intersection;

            // �����ж����ĸ��߽��ཻ�����㽻��
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

            // �ý����滻ԭ���Ķ˵�
            if (code == code1) {          // �滻���
                start = intersection;
                code1 = window.ComputeCode(start);
            }
            else {                        // �滻�յ�
                end = intersection;
                code2 = window.ComputeCode(end);
            }
        }
    }

    return accept;
}