/*
 * Algorithms/WeilerAthertonAlgorithm.hpp
 * Ziyu ZHOU @ SDAU
 * 30/11/24
 */


#pragma once
#include "Point2D.hpp"
#include "IPolygonAlgorithm.hpp"
#include "ClipWindow.hpp"
#include <list>

namespace MyGraphics {
    namespace Algorithms {
        class WeilerAthertonAlgorithm : public IPolygonAlgorithm {
        public:
            std::vector<Point2D> ClipPolygon(
                const std::vector<Point2D>& vertices,
                const ClipWindow& window) override;

        private:
            // �����������
            static const int CODE_C = 0x0000;  // �ڲ�
            static const int CODE_N = 0x0008;  // ��
            static const int CODE_S = 0x0004;  // ��
            static const int CODE_E = 0x0002;  // ��
            static const int CODE_W = 0x0001;  // ��

            // �������������
            int ComputeCode(const Point2D& point, const ClipWindow& window);
            
            // ����һ���ߵĲü�
            void ClipEdge(const Point2D& start, const Point2D& end, 
                         const ClipWindow& window,
                         std::vector<Point2D>& result);

            // ���㽻��
            Point2D ComputeIntersection(
                const Point2D& p1, const Point2D& p2,
                int edge_code, const ClipWindow& window);
        };
    }
}
