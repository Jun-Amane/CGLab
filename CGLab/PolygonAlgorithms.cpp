/*
* Algorithms/PolygonAlgorithms.cpp
* Ziyu ZHOU @ SDAU
* 30/11/24
*/

#include "pch.h"
#include "PolygonAlgorithms.hpp"
#include <cmath>
#include <stack>
#include <queue>

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

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

std::vector<Point2D> ScanLineFillAlgorithm::GeneratePoints(const std::vector<Point2D>& vertices) {
    std::vector<Point2D> points;
    if (vertices.empty()) return points;

    // ɨ�����㷨���ݽṹ
    struct EdgeNode {
        float x;       // ��ǰx����
        float dx;      // б�ʵĵ���
        int ymax;      // �ߵ����yֵ
        std::shared_ptr<EdgeNode> next;
        
        EdgeNode() : x(0), dx(0), ymax(0), next(nullptr) {}
    };

    // 1. �ҵ����yֵ
    int maxY = vertices[0].y;
    for (const auto& p : vertices) {
        maxY = std::max<int>(maxY, p.y);
    }

    // 2. ��ʼ��NET��AET
    std::vector<std::shared_ptr<EdgeNode>> NET(maxY + 1);
    for (int i = 0; i <= maxY; i++) {
        NET[i] = std::make_shared<EdgeNode>();
    }
    auto AET = std::make_shared<EdgeNode>();

    // 3. ����NET��
    int vertexCount = static_cast<int>(vertices.size());
    for (int i = 0; i <= maxY; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (vertices[j].y == i) {
                // ����ǰһ����
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
                
                // �����һ����
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

    // 4. ɨ�������
    for (int i = 0; i <= maxY; i++) {
        // ����AET�е�xֵ
        auto p = AET->next;
        while (p) {
            p->x += p->dx;
            p = p->next;
        }

        // ��xֵ����AET
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

        // ɾ��ymax=i�ı�
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

        // ��NET[i]�еı߼���AET
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

        // ���ɨ����
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

std::vector<Point2D> SeedFill4Algorithm::GeneratePoints(
    const std::vector<Point2D>& vertices, const Point2D& seed) {
    
    if (vertices.empty() || !isPointInPolygon(seed, vertices)) {
        return std::vector<Point2D>();
    }

    // �ҵ��߽緶Χ
    int minX = vertices[0].x, maxX = vertices[0].x;
    int minY = vertices[0].y, maxY = vertices[0].y;
    for (const auto& p : vertices) {
        minX = std::min<int>(minX, p.x);
        maxX = std::max<int>(maxX, p.x);
        minY = std::min<int>(minY, p.y);
        maxY = std::max<int>(maxY, p.y);
    }

    // �������㼯�ͷ��ʱ��
    std::vector<Point2D> fillPoints;
    std::vector<std::vector<bool>> visited(
        maxX - minX + 1,
        std::vector<bool>(maxY - minY + 1, false)
    );

    std::queue<Point2D> queue;
    queue.push(seed);

    // ������������
    const int dx[] = {0, 0, -1, 1};
    const int dy[] = {-1, 1, 0, 0};

    while (!queue.empty()) {
        Point2D current = queue.front();
        queue.pop();

        // ��鵱ǰ���Ƿ��ڶ�����ڲ�
        if (!isPointInPolygon(current, vertices)) {
            continue;
        }

        // ת��Ϊ�������
        int relativeX = current.x - minX;
        int relativeY = current.y - minY;

        // ����Ƿ��ѷ���
        if (relativeX < 0 || relativeX >= visited.size() ||
            relativeY < 0 || relativeY >= visited[0].size() ||
            visited[relativeX][relativeY]) {
            continue;
        }

        // ��ǲ���ӵ�
        visited[relativeX][relativeY] = true;
        fillPoints.push_back(current);

        // ���������
        for (int i = 0; i < 4; ++i) {
            Point2D next(current.x + dx[i], current.y + dy[i]);
            queue.push(next);
        }
    }

    return fillPoints;
}

std::vector<Point2D> SeedFill8Algorithm::GeneratePoints(
    const std::vector<Point2D>& vertices, const Point2D& seed) {
    
    if (vertices.empty() || !isPointInPolygon(seed, vertices)) {
        return std::vector<Point2D>();
    }

    // �ҵ��߽緶Χ
    int minX = vertices[0].x, maxX = vertices[0].x;
    int minY = vertices[0].y, maxY = vertices[0].y;
    for (const auto& p : vertices) {
        minX = std::min<int>(minX, p.x);
        maxX = std::max<int>(maxX, p.x);
        minY = std::min<int>(minY, p.y);
        maxY = std::max<int>(maxY, p.y);
    }

    // �������㼯�ͷ��ʱ��
    std::vector<Point2D> fillPoints;
    std::vector<std::vector<bool>> visited(
        maxX - minX + 1,
        std::vector<bool>(maxY - minY + 1, false)
    );

    std::queue<Point2D> queue;
    queue.push(seed);

    // ������������
    const int dx[] = {0, 0, -1, 1, -1, 1, -1, 1};
    const int dy[] = {-1, 1, 0, 0, -1, -1, 1, 1};

    while (!queue.empty()) {
        Point2D current = queue.front();
        queue.pop();

        // ��鵱ǰ���Ƿ��ڶ�����ڲ�
        if (!isPointInPolygon(current, vertices)) {
            continue;
        }

        // ת��Ϊ�������
        int relativeX = current.x - minX;
        int relativeY = current.y - minY;

        // ����Ƿ��ѷ���
        if (relativeX < 0 || relativeX >= visited.size() ||
            relativeY < 0 || relativeY >= visited[0].size() ||
            visited[relativeX][relativeY]) {
            continue;
        }

        // ��ǲ���ӵ�
        visited[relativeX][relativeY] = true;
        fillPoints.push_back(current);

        // ��������
        for (int i = 0; i < 8; ++i) {
            Point2D next(current.x + dx[i], current.y + dy[i]);
            queue.push(next);
        }
    }

    return fillPoints;
}