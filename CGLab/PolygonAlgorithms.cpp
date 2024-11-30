/*
 *
 * 文件: Algorithms/PolygonAlgorithms.cpp
 * 作者: Ziyu ZHOU @ SDAU
 * 日期: 30/11/24
 *
 * 说明: 本文件实现了三种多边形填充算法：
 * 1. X扫描线填充算法
 * 2. 四邻域种子填充算法
 * 3. 八邻域种子填充算法
 * 所有算法都基于多边形顶点数组，并生成填充用的像素点集
 */

#include "pch.h"
#include "PolygonAlgorithms.hpp"
#include <cmath>
#include <stack>
#include <queue>

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/* 点与多边形的位置关系判断 */
/**
 * 使用射线法判断点是否位于多边形内部
 * 从目标点向右发出射线，统计与多边形边的相交次数
 * 相交次数为奇数表示点在内部，偶数表示点在外部
 *
 * @param p: 待判断的点
 * @param vertices: 多边形顶点数组
 * @return: 点在多边形内返回true，否则返回false
 */
bool IPolygonAlgorithm::isPointInPolygon(const Point2D& p, const std::vector<Point2D>& vertices) {
    bool inside = false;
    int j = vertices.size() - 1;

    for (int i = 0; i < vertices.size(); i++) {
        if (((vertices[i].y > p.y) != (vertices[j].y > p.y)) &&
            (p.x < (vertices[j].x - vertices[i].x) * (p.y - vertices[i].y) /
                (vertices[j].y - vertices[i].y) + vertices[i].x)) {
            inside = !inside;
        }
        j = i;
    }
    return inside;
}

/* X扫描线填充算法实现 */
/**
 * 使用扫描线算法对多边形进行填充
 * 算法基本步骤:
 * 1. 构建边表NET(New Edge Table)和活动边表AET(Active Edge Table)
 * 2. 自下而上扫描，在每个扫描线位置:
 *    - 更新AET中边的x坐标
 *    - 将新的边加入AET
 *    - 删除过期的边
 *    - 对AET中的边配对，在配对之间填充像素
 *
 * @param vertices: 多边形顶点数组
 * @return: 返回填充后的所有像素点坐标
 */
std::vector<Point2D> ScanLineFillAlgorithm::GeneratePoints(const std::vector<Point2D>& vertices) {
    std::vector<Point2D> points;
    if (vertices.empty()) return points;

    // 定义边表结点结构
    struct EdgeNode {
        float x;       // 当前扫描线与边的交点x坐标
        float dx;      // 边的斜率倒数(x的增量)
        int ymax;      // 边的最高点y坐标
        std::shared_ptr<EdgeNode> next;

        EdgeNode() : x(0), dx(0), ymax(0), next(nullptr) {}
    };

    // 找到最高的y坐标，确定扫描范围
    int maxY = vertices[0].y;
    for (const auto& p : vertices) {
        maxY = std::max<int>(maxY, p.y);
    }

    // 初始化NET和AET表
    std::vector<std::shared_ptr<EdgeNode>> NET(maxY + 1);
    for (int i = 0; i <= maxY; i++) {
        NET[i] = std::make_shared<EdgeNode>();
    }
    auto AET = std::make_shared<EdgeNode>();

    // 构建NET表
    int vertexCount = static_cast<int>(vertices.size());
    for (int i = 0; i <= maxY; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (vertices[j].y == i) {
                // 处理以当前点为下端点的边
                int prev = (j - 1 + vertexCount) % vertexCount;
                if (vertices[prev].y > vertices[j].y) {
                    auto p = std::make_shared<EdgeNode>();
                    p->x = static_cast<float>(vertices[j].x);
                    p->ymax = vertices[prev].y;
                    p->dx = static_cast<float>(vertices[prev].x - vertices[j].x) /
                        (vertices[prev].y - vertices[j].y);
                    p->next = NET[i]->next;
                    NET[i]->next = p;
                }

                int next = (j + 1) % vertexCount;
                if (vertices[next].y > vertices[j].y) {
                    auto p = std::make_shared<EdgeNode>();
                    p->x = static_cast<float>(vertices[j].x);
                    p->ymax = vertices[next].y;
                    p->dx = static_cast<float>(vertices[next].x - vertices[j].x) /
                        (vertices[next].y - vertices[j].y);
                    p->next = NET[i]->next;
                    NET[i]->next = p;
                }
            }
        }
    }

    // 扫描线处理过程
    for (int i = 0; i <= maxY; i++) {
        // 更新AET中边的x值
        auto p = AET->next;
        while (p) {
            p->x += p->dx;
            p = p->next;
        }

        // 按x值对AET进行排序
        auto tq = AET;
        p = AET->next;
        tq->next = nullptr;
        while (p) {
            while (tq->next && p->x >= tq->next->x)
                tq = tq->next;
            auto s = p->next;
            p->next = tq->next;
            tq->next = p;
            p = s;
            tq = AET;
        }

        // 删除已完成的边(ymax=i的边)
        auto q = AET;
        p = q->next;
        while (p) {
            if (p->ymax == i) {
                q->next = p->next;
                p = q->next;
            }
            else {
                q = q->next;
                p = q->next;
            }
        }

        // 将NET中新的边加入AET
        p = NET[i]->next;
        q = AET;
        while (p) {
            while (q->next && p->x >= q->next->x)
                q = q->next;
            auto s = p->next;
            p->next = q->next;
            q->next = p;
            p = s;
            q = AET;
        }

        // 配对填充扫描线
        p = AET->next;
        while (p && p->next) {
            for (int j = static_cast<int>(p->x); j <= static_cast<int>(p->next->x); j++) {
                points.push_back(Point2D(j, i));
            }
            p = p->next->next;
        }
    }

    return points;
}

/* 四邻域种子填充算法实现 */
/**
 * 使用四邻域种子填充算法填充多边形
 * 算法从种子点开始，递归检查上下左右四个相邻点
 * 如果相邻点在多边形内部且未被访问过，则将其加入填充集合
 *
 * @param vertices: 多边形顶点数组
 * @param seed: 种子点坐标
 * @return: 返回填充后的所有像素点坐标
 */
std::vector<Point2D> SeedFill4Algorithm::GeneratePoints(
    const std::vector<Point2D>& vertices, const Point2D& seed) {

    // 检查输入合法性
    if (vertices.empty() || !isPointInPolygon(seed, vertices)) {
        return std::vector<Point2D>();
    }

    // 计算多边形的边界范围
    int minX = vertices[0].x, maxX = vertices[0].x;
    int minY = vertices[0].y, maxY = vertices[0].y;
    for (const auto& p : vertices) {
        minX = std::min<int>(minX, p.x);
        maxX = std::max<int>(maxX, p.x);
        minY = std::min<int>(minY, p.y);
        maxY = std::max<int>(maxY, p.y);
    }

    // 初始化数据结构
    std::vector<Point2D> fillPoints;
    std::vector<std::vector<bool>> visited(
        maxX - minX + 1,
        std::vector<bool>(maxY - minY + 1, false)
    );

    // 使用队列进行广度优先搜索
    std::queue<Point2D> queue;
    queue.push(seed);

    // 定义四个方向的偏移量：上、下、左、右
    const int dx[] = { 0, 0, -1, 1 };
    const int dy[] = { -1, 1, 0, 0 };

    // 广度优先搜索主循环
    while (!queue.empty()) {
        Point2D current = queue.front();
        queue.pop();

        // 验证点是否在多边形内
        if (!isPointInPolygon(current, vertices)) {
            continue;
        }

        // 转换为相对坐标进行访问标记
        int relativeX = current.x - minX;
        int relativeY = current.y - minY;

        // 检查边界和访问状态
        if (relativeX < 0 || relativeX >= visited.size() ||
            relativeY < 0 || relativeY >= visited[0].size() ||
            visited[relativeX][relativeY]) {
            continue;
        }

        // 标记并添加当前点
        visited[relativeX][relativeY] = true;
        fillPoints.push_back(current);

        // 检查四个邻域点
        for (int i = 0; i < 4; ++i) {
            Point2D next(current.x + dx[i], current.y + dy[i]);
            queue.push(next);
        }
    }

    return fillPoints;
}

/* 八邻域种子填充算法实现 */
/**
 * 使用八邻域种子填充算法填充多边形
 * 与四邻域算法类似，但同时检查对角线方向的相邻点
 *
 * @param vertices: 多边形顶点数组
 * @param seed: 种子点坐标
 * @return: 返回填充后的所有像素点坐标
 */
std::vector<Point2D> SeedFill8Algorithm::GeneratePoints(
    const std::vector<Point2D>& vertices, const Point2D& seed) {

    // 检查输入合法性
    if (vertices.empty() || !isPointInPolygon(seed, vertices)) {
        return std::vector<Point2D>();
    }

    // 计算边界范围
    int minX = vertices[0].x, maxX = vertices[0].x;
    int minY = vertices[0].y, maxY = vertices[0].y;
    for (const auto& p : vertices) {
        minX = std::min<int>(minX, p.x);
        maxX = std::max<int>(maxX, p.x);
        minY = std::min<int>(minY, p.y);
        maxY = std::max<int>(maxY, p.y);
    }

    // 初始化数据结构
    std::vector<Point2D> fillPoints;
    std::vector<std::vector<bool>> visited(
        maxX - minX + 1,
        std::vector<bool>(maxY - minY + 1, false)
    );

    std::queue<Point2D> queue;
    queue.push(seed);

    // 定义八个方向的偏移量：上、下、左、右、左上、右上、左下、右下
    const int dx[] = { 0, 0, -1, 1, -1, 1, -1, 1 };
    const int dy[] = { -1, 1, 0, 0, -1, -1, 1, 1 };

    // 广度优先搜索主循环
    while (!queue.empty()) {
        Point2D current = queue.front();
        queue.pop();

        if (!isPointInPolygon(current, vertices)) {
            continue;
        }

        int relativeX = current.x - minX;
        int relativeY = current.y - minY;

        if (relativeX < 0 || relativeX >= visited.size() ||
            relativeY < 0 || relativeY >= visited[0].size() ||
            visited[relativeX][relativeY]) {
            continue;
        }

        visited[relativeX][relativeY] = true;
        fillPoints.push_back(current);

        // 检查八个邻域点
        for (int i = 0; i < 8; ++i) {
            Point2D next(current.x + dx[i], current.y + dy[i]);
            queue.push(next);
        }
    }

    return fillPoints;
}