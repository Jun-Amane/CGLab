/*
*
* 文件名: Algorithms/LineClipAlgorithms.hpp
* 作者: Ziyu ZHOU @ SDAU
* 日期: 30/11/24
*
* 说明: 本文件声明了直线裁剪算法的具体实现类
* 目前实现了Cohen-Sutherland直线裁剪算法
*/

#pragma once
#include "ILineClipAlgorithm.hpp"

using namespace MyGraphics;
using namespace MyGraphics::Algorithms;

/**
* Cohen-Sutherland直线裁剪算法类
* 通过编码的方式对直线进行裁剪
* 优点是实现简单,对一般情况处理效率较高
*/
class CohenSutherlandAlgorithm : public ILineClipAlgorithm {
public:
    /**
     * 对直线进行裁剪
     * @param start 直线起点(会被修改为裁剪后的起点)
     * @param end 直线终点(会被修改为裁剪后的终点)
     * @param window 裁剪窗口对象
     * @return 返回是否保留该直线
     *         true - 直线(可能经过裁剪)应该被保留
     *         false - 直线完全在窗口外,应该被舍弃
     */
    bool ClipLine(Point2D& start, Point2D& end, const ClipWindow& window) override;
};