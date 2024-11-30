/*
* 文件: Models/Object3D.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件定义了Object3D类,用于三维图形对象的基本操作
* 功能:
* 1. 提供三维图形的基本数据结构(顶点和边)
* 2. 支持三维几何变换
* 3. 生成三视图(主视图/俯视图/左视图)
*/

#pragma once
#include "Point3D.hpp"
#include "Point2D.hpp"
#include "Matrix4x4.hpp"
#include "Transform3D.hpp"
#include <vector>
#include <utility>

namespace MyGraphics {
    /**
     * Object3D类 - 三维图形对象基类
     * 提供三维图形的基本功能和数据结构
     */
    class Object3D {
    public:
        // 构造和析构函数
        Object3D() = default;
        virtual ~Object3D() = default;

        /**
         * 对三维对象进行变换
         * @param matrix: 4x4变换矩阵
         */
        void Transform(const Matrix4x4& matrix);

        /**
         * 获取对象的三视图投影点集
         * @param frontView: 主视图(前视图)点集,XOY平面投影
         * @param topView: 俯视图点集,XOZ平面投影
         * @param sideView: 左视图点集,YOZ平面投影
         */
        void GetProjections(
            std::vector<Point2D>& frontView,   // 主视图(前视图)
            std::vector<Point2D>& topView,     // 俯视图
            std::vector<Point2D>& sideView     // 左视图
        ) const;

        /**
         * 在指定区域绘制投影图
         * @param pDC: 设备上下文指针
         * @param points: 投影点集
         * @param rect: 绘制区域
         * @param color: 绘制颜色,默认为黑色
         */
        void DrawProjection(CDC* pDC, const std::vector<Point2D>& points,
            CRect rect, COLORREF color = RGB(0, 0, 0)) const;

        /**
         * 获取三维对象的边集合
         * @return: 由顶点索引对构成的边集合
         */
        const std::vector<std::pair<int, int>>& GetEdges() const { return m_edges; }

        /**
         * 获取三维对象的顶点集合
         * @return: 三维点的集合
         */
        const std::vector<Point3D>& GetVertices() const { return m_vertices; }

    protected:
        std::vector<Point3D> m_vertices;               // 存储三维对象的所有顶点
        std::vector<std::pair<int, int>> m_edges;      // 存储边的信息,每条边由两个顶点索引表示
    };
}