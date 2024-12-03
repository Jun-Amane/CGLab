# CGLab: 计算机图形学经典算法演示程序

基于MFC的计算机图形学基本算法可视化实现，包含直线、圆、椭圆生成算法，多边形填充算法，二维/三维几何变换等经典图形学算法的演示。

## 功能特性

### 1. 直线生成算法
- DDA算法 
- 中点画线法
- Bresenham算法

### 2. 圆生成算法  
- 中点算法 
- Bresenham圆生成算法

### 3. 椭圆生成算法
- Bresenham椭圆生成算法

### 4. 多边形填充算法
- X-扫描线填充
- 种子填充算法(四邻域)
- 种子填充算法(八邻域)

### 5. 二维几何变换
- 平移变换
- 旋转变换 
- 错切变换
- 缩放变换
- 对称变换

### 6. 裁剪算法
- Cohen-Sutherland直线裁剪
- Weiler-Atherton多边形裁剪

### 7. 三维图形
- 斜二侧图形预览
- 三维几何变换(平移、旋转、缩放等五种)
- 三视图生成

## 技术实现

### 核心设计
- 面向对象
- 使用Strategy设计模式实现算法切换
- 使用现代C++中智能指针等功能
- 基于MFC实现用户界面和图形绘制

### 关键类
- `GraphicsObject`: 图形对象基类
- `Line/Circle/Ellipse/...`: 具体图形类
- `Matrix3x3/Matrix4x4`: 矩阵类
- `Point2D/Point3D`: 2D、3D点坐标类
- `Transform2D/Transform3D`: 几何变换实现
- `ILineAlgorithm/ICircleAlgorithm/...`: 算法接口类
- `*Algorithms`: 具体算法类

### View类功能说明

#### 核心成员变量
1. 模式切换
```cpp
bool m_is3DMode;       // 2D/3D模式标志
bool m_isOrthographic; // 正投影/斜二测投影切换
```

2. 交互状态控制
```cpp
bool m_isDrawingPolygon;   // 是否正在绘制多边形
bool m_isClipWindowSet;    // 是否设置了裁剪窗口
CPoint m_lastMousePos;     // 记录鼠标位置用于实时预览
```

3. 对象管理
```cpp
// 存储所有图形对象
std::vector<std::shared_ptr<MyGraphics::GraphicsObject>> m_objects;
// 当前正在绘制的多边形
std::shared_ptr<MyGraphics::Polygon> m_currentPolygon;
// 当前使用的多边形算法
MyGraphics::Polygon::Algorithm m_currentPolygonAlgorithm;
```

#### 运行流程

1. OnDraw绘制流程
```cpp
void CCGLabView::OnDraw(CDC* pDC) {
    // 1. 创建内存DC以实现双缓冲
    CDC memDC;
    CBitmap memBitmap;
    memDC.CreateCompatibleDC(pDC);
    
    // 2. 根据模式选择绘制方式
    if (m_is3DMode) {
        if (m_isOrthographic) {
            Draw3ViewsObject(&memDC);     // 绘制三视图
        } else {
            Draw3DObject(&memDC);         // 绘制斜二测投影
        }
    } else {
        // 3. 2D模式下的绘制流程
        // 3.1 如果设置了裁剪窗口且没有其他对象，显示裁剪窗口
        if (m_isClipWindowSet && m_objects.empty()) {
            m_clipWindow.Draw(&memDC);
        }
        
        // 3.2 绘制所有已完成的图形对象
        for (const auto& obj : m_objects) {
            obj->Draw(&memDC);
        }
        
        // 3.3 处理多边形绘制的实时预览
        if (m_isDrawingPolygon && m_currentPolygon) {
            // 绘制当前多边形
            m_currentPolygon->Draw(&memDC);
            
            // 如果多边形未封闭，显示预览线
            if (!m_currentPolygon->IsClosed()) {
                DrawPreviewLine(&memDC);
            }
        }
        
        // 3.4 显示操作提示
        DrawPrompt(&memDC);
    }
    
    // 4. 将内存DC内容复制到屏幕
    pDC->BitBlt(0, 0, rect.Width(), rect.Height(), 
                &memDC, 0, 0, SRCCOPY);
}
```

2. 鼠标事件处理流程
```cpp
void CCGLabView::OnLButtonDown(UINT nFlags, CPoint point) {
    if (m_isDrawingPolygon && m_currentPolygon) {
        if (!m_currentPolygon->IsClosed()) {
            // 添加多边形顶点
            m_currentPolygon->AddVertex(Point2D(point.x, point.y));
            m_lastMousePos = point;
            Invalidate();  // 触发重绘
        }
        else if (m_currentPolygonAlgorithm != Polygon::ALGO_SCANLINE) {
            // 多边形已封闭，设置种子点
            m_currentPolygon->SetSeed(Point2D(point.x, point.y));
            m_currentPolygon->GeneratePoints();
            Invalidate();
        }
    }
}

void CCGLabView::OnRButtonDown(UINT nFlags, CPoint point) {
    if (m_isDrawingPolygon && m_currentPolygon) {
        if (!m_currentPolygon->IsClosed()) {
            // 封闭多边形
            m_currentPolygon->Close();
            
            // 根据算法类型决定后续操作
            if (m_currentPolygonAlgorithm == Polygon::ALGO_SCANLINE) {
                // 扫描线算法直接生成填充点
                m_currentPolygon->GeneratePoints();
                m_objects.push_back(m_currentPolygon);
                m_isDrawingPolygon = false;
            }
            Invalidate();
        }
    }
}

void CCGLabView::OnMouseMove(UINT nFlags, CPoint point) {
    if (m_isDrawingPolygon && m_currentPolygon 
        && !m_currentPolygon->IsClosed()) {
        // 更新预览线的终点
        m_lastMousePos = point;
        Invalidate();
    }
}
```

3. 状态转换流程
```cpp
// 进入多边形绘制模式
void CCGLabView::OnPolygonX() {
    ClearScreen();  // 清除现有内容
    m_isDrawingPolygon = true;
    m_currentPolygon = std::make_shared<Polygon>();
    m_currentPolygon->SetAlgorithm(Polygon::ALGO_SCANLINE);
    m_currentPolygonAlgorithm = Polygon::ALGO_SCANLINE;
}

// 切换到3D模式
void CCGLabView::On3dtransformOriginal() {
    ClearAll();
    m_is3DMode = true;
    m_isOrthographic = false;
    m_frustum = std::make_shared<Frustum>();
    UpdateProjection();
    Invalidate();
}
```

注意：以上代码展示了主要的控制流程，但为了演示目的，这种设计将多个职责集中在View类中。

## 开发环境

- Visual Studio 2022
- MFC
- C++17
- Windows SDK 10.0

## 构建与运行

### 编译环境配置
- 平台工具集: 选择v143(VS2022)
- Windows SDK版本: 10.0
- MFC的使用: 在静态库中使用MFC
- 字符集: 使用Unicode字符集
- C\++语言标准: C\++17

### 编译步骤
1. 使用Visual Studio打开解决方案文件(.sln)
2. 配置解决方案平台为x64
3. 选择Debug（或Release）配置
4. 点击Build -> Build Solution进行构建
5. 等待编译完成
6. 在x64/Release目录下找到可执行文件

## 使用说明

1. 选择菜单中的算法类型
2. 根据提示输入必要参数
3. 观察算法执行结果的可视化展示
4. 可以使用Clear清除画布

## 架构设计

项目采用分层架构:
- 算法层: 实现各类图形学算法
- 模型层: 定义图形对象和数据结构
- 视图层: 处理用户交互和图形显示

## 代码示例

```cpp
// 使用Bresenham算法绘制直线
auto line = std::make_shared<MyGraphics::Line>();
line->SetAlgorithm(MyGraphics::Line::ALGO_BRESENHAM);
line->SetPoints(start, end);
line->GeneratePoints();
```

## 层次结构

```
├── Algorithms/       # 算法实现
├── Math/            # 数学工具类
├── Models/          # 图形模型类
└── Dialogs/         # 对话框UI
```

## 扩展与自定义

### 添加新的图形算法
1. 定义算法接口
```cpp
// 在对应的IxxxAlgorithm.hpp中添加新接口
namespace MyGraphics {
    namespace Algorithms {
        class INewAlgorithm {
        public:
            virtual ~INewAlgorithm() = default;
            virtual std::vector<Point2D> GeneratePoints(...) = 0;
        };
    }
}
```

2. 实现算法类
```cpp
// 在新的算法实现文件中
class NewAlgorithm : public INewAlgorithm {
public:
    std::vector<Point2D> GeneratePoints(...) override {
        // 实现算法逻辑
    }
};
```

3. 在图形对象类中添加支持
```cpp
// 在对应的图形类中
class Shape : public GraphicsObject {
public:
    enum Algorithm {
        // 添加新算法类型
        ALGO_NEW = xxx
    };
    
    void SetAlgorithm(Algorithm algo) {
        switch(algo) {
            case ALGO_NEW:
                m_algorithm = std::make_unique<NewAlgorithm>();
                break;
        }
    }
};
```

4. 更新用户界面
   - 在资源文件中添加菜单项
   - 添加命令处理函数
   - 实现交互逻辑

### 添加新的图形对象
1. 创建新的图形类
```cpp
class NewShape : public GraphicsObject {
public:
    NewShape() : GraphicsObject(OT_NEWSHAPE) {}
    
    void GeneratePoints() override {
        // 实现点生成逻辑
    }
    
    void Draw(CDC* pDC) override {
        // 实现绘制逻辑
    }
};
```

2. 添加相关算法支持
   - 创建算法接口类
   - 实现具体算法类
   - 在图形类中集成算法

3. 创建交互界面
   - 添加参数输入对话框
   - 实现命令处理函数
   - 更新菜单和工具栏

### 修改现有算法
1. 找到对应的算法实现类
2. 修改GeneratePoints()方法中的逻辑
3. 保持接口不变，确保兼容性

## 许可

本项目遵循 MIT 许可证。


***Designed by Ziyu ZHOU at SDAU***

*30th. Nov. 2024*