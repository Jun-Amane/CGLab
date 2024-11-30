/*
*
* �ļ���: Algorithms/LineClipAlgorithms.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 30/11/24
*
* ˵��: ���ļ�������ֱ�߲ü��㷨�ľ���ʵ����
* Ŀǰʵ����Cohen-Sutherlandֱ�߲ü��㷨
*/

#pragma once
#include "ILineClipAlgorithm.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* Cohen-Sutherlandֱ�߲ü��㷨��
* ͨ������ķ�ʽ��ֱ�߽��вü�
* �ŵ���ʵ�ּ�,��һ���������Ч�ʽϸ�
*/
class CohenSutherlandAlgorithm : public ILineClipAlgorithm {
public:
    /**
     * ��ֱ�߽��вü�
     * @param start ֱ�����(�ᱻ�޸�Ϊ�ü�������)
     * @param end ֱ���յ�(�ᱻ�޸�Ϊ�ü�����յ�)
     * @param window �ü����ڶ���
     * @return �����Ƿ�����ֱ��
     *         true - ֱ��(���ܾ����ü�)Ӧ�ñ�����
     *         false - ֱ����ȫ�ڴ�����,Ӧ�ñ�����
     */
    bool ClipLine(Point2D& start, Point2D& end, const ClipWindow& window) override;
};