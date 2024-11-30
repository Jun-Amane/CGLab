/*
 * 文件: Models/Frustum.hpp
 * 作者: Ziyu ZHOU @ SDAU
 * 日期: 30/11/24
 *
 * 说明: 本文件定义了Frustum类，该类继承自Object3D
 */

#pragma once
#include "Object3D.hpp"

namespace MyGraphics {
    class Frustum : public Object3D {
    public:
        /**
         * 构造函数
         * @param baseSize: 底面边长，默认值为100.0
         * @param topSize: 顶面边长，默认值为60.0
         * @param height: 高，默认值为120.0
         */
        Frustum(double baseSize = 100.0, double topSize = 60.0, double height = 120.0);

        /**
         * 默认析构函数
         * 由于使用了继承，析构函数为virtual，确保派生类销毁时调用正确的析构逻辑。
         */
        ~Frustum() override = default;
    };
}
