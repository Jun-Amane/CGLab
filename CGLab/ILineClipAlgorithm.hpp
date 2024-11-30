/*
*
* 文件名: Algorithms/ILineClipAlgorithm.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件定义了直线裁剪算法的接口类
* 所有具体的直线裁剪算法都需要继承并实现该接口
*/

#pragma once
#include "Point2D.hpp"
#include "ClipWindow.hpp"

namespace MyGraphics {
    namespace Algorithms {

        /**
         * 直线裁剪算法的抽象接口类
         * 定义了直线裁剪算法的标准接口
         * 提供了算法的多态性支持
         */
        class ILineClipAlgorithm {
        public:
            /**
             * 虚析构函数,确保正确的多态析构
             */
            virtual ~ILineClipAlgorithm() = default;

            /**
             * 纯虚函数,对直线进行裁剪
             * @param start 直线的起点坐标(将被修改为裁剪后的起点)
             * @param end 直线的终点坐标(将被修改为裁剪后的终点)
             * @param window 裁剪窗口对象
             * @return 返回是否保留该直线
             *         true - 直线与裁剪窗口相交,保留裁剪后的部分
             *         false - 直线完全在裁剪窗口外,应该被完全裁剪
             */
            virtual bool ClipLine(Point2D& start, Point2D& end, const ClipWindow& window) = 0;
        };

    } // namespace Algorithms
} // namespace MyGraphics