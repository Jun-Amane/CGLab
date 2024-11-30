/*
* 文件: Models/Polygon.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件定义了Polygon类,用于多边形的生成、填充、裁剪和变换
* 特点:
* 1. 继承自GraphicsObject基类
* 2. 支持扫描线和种子填充两类填充算法
* 3. 支持Weiler-Atherton多边形裁剪算法
* 4. 支持基本的二维几何变换
*/

#pragma once
#include "Point2D.hpp"
#include "Matrix3x3.hpp"
#include "Transform2D.hpp"
#include "GraphicsObject.hpp"
#include "IPolygonAlgorithm.hpp"
#include <memory>

namespace MyGraphics {
    /**
     * Polygon类 - 多边形图形对象
     * 提供多边形的构建、填充、裁剪和变换功能
     */
    class Polygon : public GraphicsObject {
    public:
        /**
         * 定义支持的算法类型
         */
        enum Algorithm {
            ALGO_SCANLINE,       // x-扫描线填充算法
            ALGO_SEEDFILL_4,     // 四邻域种子填充算法
            ALGO_SEEDFILL_8,     // 八邻域种子填充算法
            ALGO_WEILER_ATHERTON // Weiler-Atherton多边形裁剪算法
        };

        // 构造和析构函数
        Polygon();
        ~Polygon() override = default;

        /**
         * 基本操作函数
         */
        void SetAlgorithm(Algorithm algo);                     // 设置处理算法
        void AddVertex(const Point2D& point);                  // 添加顶点
        void SetSeed(const Point2D& seed);                     // 设置种子点
        void Close();                                          // 封闭多边形
        bool IsClosed() const { return m_closed; }             // 判断是否已闭合
        void GeneratePoints() override;                        // 生成构成多边形的点集
        const std::vector<Point2D>& GetVertices() const { return m_vertices; }  // 获取顶点数组

        /**
         * 绘制相关函数
         */
        void Draw(CDC* pDC) override;                          // 绘制完整多边形
        void DrawVertex(CDC* pDC, const Point2D& point);       // 绘制顶点
        void DrawSeed(CDC* pDC, const Point2D& point);        // 绘制种子点

        /**
         * 种子填充相关函数
         */
        bool HasSeed() const { return m_hasSeed; }            // 检查是否设置种子点

        /**
         * 变换和裁剪相关函数
         */
        void Transform(const Matrix3x3& matrix);              // 对多边形进行变换
        void SetClipWindow(const ClipWindow& window) { m_clipWindow = window; }  // 设置裁剪窗口
        ClipWindow& GetClipWindow() { return m_clipWindow; }  // 获取裁剪窗口

    private:
        Algorithm m_algorithm;           // 当前使用的算法类型
        std::vector<Point2D> m_vertices; // 多边形顶点集合

        // 显示参数
        static const int VERTEX_SIZE = 4;  // 顶点显示的大小(像素)
        static const int SEED_SIZE = 6;    // 种子点显示的大小(像素)

        // 种子填充相关
        bool m_hasSeed = false;         // 是否已设置种子点标志
        Point2D m_seed;                 // 种子点坐标

        // 多边形状态
        bool m_closed;                  // 多边形闭合标志
        std::vector<Point2D> m_points;  // 填充点集

        // 裁剪相关
        ClipWindow m_clipWindow;                // 裁剪窗口
        std::vector<Point2D> m_originalVertices; // 裁剪前的原始顶点
        bool m_isClipped;                       // 裁剪状态标志

        // 算法对象(Strategy模式)
        std::unique_ptr<Algorithms::IPolygonAlgorithm> m_polygonAlgorithm;

    protected:
        /**
         * 对多边形顶点进行变换操作
         * @param matrix: 变换矩阵
         */
        void TransformVertices(const Matrix3x3& matrix);
    };
}