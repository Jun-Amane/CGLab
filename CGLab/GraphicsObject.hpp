/*
*
* �ļ�: Models/GraphicsObject.hpp
* ����: Ziyu ZHOU @ SDAU
* ����: 26/11/24
*
* ˵��: ���ļ������˶�άͼ�ζ���ĳ������
* �ṩ��:
* 1. ����ͼ�����͵�ö��
* 2. ͼ�λ��Ƶ��麯���ӿ�
* 3. ͼ�ζ����ͨ������
*/

#pragma once
#include "pch.h"
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
    /**
     * GraphicsObject�� - ��άͼ�ζ���ĳ������
     * ���������ж�άͼ�ζ���Ĺ�ͬ�ӿں�����
     */
    class GraphicsObject {
    public:
        /**
         * ֧�ֵ�ͼ�ζ�������ö��
         */
        enum ObjectType {
            OT_NONE,     // δ��������
            OT_LINE,     // ֱ��
            OT_CIRCLE,   // Բ��
            OT_ELLIPSE,  // ��Բ
            OT_POLYGON   // �����
        };

        /**
         * ���캯��
         * @param type: ͼ������,Ĭ��ΪOT_NONE
         * ��ʼ��:
         * - ͼ������
         * - ��ɫ(Ĭ�Ϻ�ɫ)
         * - �߿�(Ĭ��Ϊ1)
         */
        GraphicsObject(ObjectType type = OT_NONE)
            : m_type(type)
            , m_color(RGB(0, 0, 0))
            , m_width(1) {}

        /**
         * ����������
         * ȷ����ȷ�ͷ����������
         */
        virtual ~GraphicsObject() {}

        /**
         * ���麯��������ͼ��
         * @param pDC: �豸������ָ��
         * ���������ʵ�ִ˺�������ɾ���ͼ�εĻ���
         */
        virtual void Draw(CDC* pDC) = 0;

        /**
         * ���麯��������ͼ�εĵ㼯
         * ���������ʵ�ִ˺��������ɹ���ͼ�ε����е�
         */
        virtual void GeneratePoints() = 0;

    protected:
        ObjectType m_type;   // ͼ������
        COLORREF m_color;    // ͼ����ɫ
        int m_width;         // �߿�
    };
}