/*
*
* 文件: Models/GraphicsObject.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 26/11/24
*
* 说明: 本文件定义了二维图形对象的抽象基类
* 提供了:
* 1. 基本图形类型的枚举
* 2. 图形绘制的虚函数接口
* 3. 图形对象的通用属性
*/

#pragma once
#include "pch.h"
#include "Point2D.hpp"
#include <vector>

namespace MyGraphics {
    /**
     * GraphicsObject类 - 二维图形对象的抽象基类
     * 定义了所有二维图形对象的共同接口和属性
     */
    class GraphicsObject {
    public:
        /**
         * 支持的图形对象类型枚举
         */
        enum ObjectType {
            OT_NONE,     // 未定义类型
            OT_LINE,     // 直线
            OT_CIRCLE,   // 圆形
            OT_ELLIPSE,  // 椭圆
            OT_POLYGON   // 多边形
        };

        /**
         * 构造函数
         * @param type: 图形类型,默认为OT_NONE
         * 初始化:
         * - 图形类型
         * - 颜色(默认黑色)
         * - 线宽(默认为1)
         */
        GraphicsObject(ObjectType type = OT_NONE)
            : m_type(type)
            , m_color(RGB(0, 0, 0))
            , m_width(1) {}

        /**
         * 虚析构函数
         * 确保正确释放派生类对象
         */
        virtual ~GraphicsObject() {}

        /**
         * 纯虚函数：绘制图形
         * @param pDC: 设备上下文指针
         * 派生类必须实现此函数以完成具体图形的绘制
         */
        virtual void Draw(CDC* pDC) = 0;

        /**
         * 纯虚函数：生成图形的点集
         * 派生类必须实现此函数以生成构成图形的所有点
         */
        virtual void GeneratePoints() = 0;

    protected:
        ObjectType m_type;   // 图形类型
        COLORREF m_color;    // 图形颜色
        int m_width;         // 线宽
    };
}