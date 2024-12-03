# CGLab: �����ͼ��ѧ�����㷨��ʾ����

����MFC�ļ����ͼ��ѧ�����㷨���ӻ�ʵ�֣�����ֱ�ߡ�Բ����Բ�����㷨�����������㷨����ά/��ά���α任�Ⱦ���ͼ��ѧ�㷨����ʾ��

## ��������

### 1. ֱ�������㷨
- DDA�㷨 
- �е㻭�߷�
- Bresenham�㷨

### 2. Բ�����㷨  
- �е��㷨 
- BresenhamԲ�����㷨

### 3. ��Բ�����㷨
- Bresenham��Բ�����㷨

### 4. ���������㷨
- X-ɨ�������
- ��������㷨(������)
- ��������㷨(������)

### 5. ��ά���α任
- ƽ�Ʊ任
- ��ת�任 
- ���б任
- ���ű任
- �ԳƱ任

### 6. �ü��㷨
- Cohen-Sutherlandֱ�߲ü�
- Weiler-Atherton����βü�

### 7. ��άͼ��
- б����ͼ��Ԥ��
- ��ά���α任(ƽ�ơ���ת�����ŵ�����)
- ����ͼ����

## ����ʵ��

### �������
- �������
- ʹ��Strategy���ģʽʵ���㷨�л�
- ʹ���ִ�C++������ָ��ȹ���
- ����MFCʵ���û������ͼ�λ���

### �ؼ���
- `GraphicsObject`: ͼ�ζ������
- `Line/Circle/Ellipse/...`: ����ͼ����
- `Matrix3x3/Matrix4x4`: ������
- `Point2D/Point3D`: 2D��3D��������
- `Transform2D/Transform3D`: ���α任ʵ��
- `ILineAlgorithm/ICircleAlgorithm/...`: �㷨�ӿ���
- `*Algorithms`: �����㷨��

### View�๦��˵��

#### ���ĳ�Ա����
1. ģʽ�л�
```cpp
bool m_is3DMode;       // 2D/3Dģʽ��־
bool m_isOrthographic; // ��ͶӰ/б����ͶӰ�л�
```

2. ����״̬����
```cpp
bool m_isDrawingPolygon;   // �Ƿ����ڻ��ƶ����
bool m_isClipWindowSet;    // �Ƿ������˲ü�����
CPoint m_lastMousePos;     // ��¼���λ������ʵʱԤ��
```

3. �������
```cpp
// �洢����ͼ�ζ���
std::vector<std::shared_ptr<MyGraphics::GraphicsObject>> m_objects;
// ��ǰ���ڻ��ƵĶ����
std::shared_ptr<MyGraphics::Polygon> m_currentPolygon;
// ��ǰʹ�õĶ�����㷨
MyGraphics::Polygon::Algorithm m_currentPolygonAlgorithm;
```

#### ��������

1. OnDraw��������
```cpp
void CCGLabView::OnDraw(CDC* pDC) {
    // 1. �����ڴ�DC��ʵ��˫����
    CDC memDC;
    CBitmap memBitmap;
    memDC.CreateCompatibleDC(pDC);
    
    // 2. ����ģʽѡ����Ʒ�ʽ
    if (m_is3DMode) {
        if (m_isOrthographic) {
            Draw3ViewsObject(&memDC);     // ��������ͼ
        } else {
            Draw3DObject(&memDC);         // ����б����ͶӰ
        }
    } else {
        // 3. 2Dģʽ�µĻ�������
        // 3.1 ��������˲ü�������û������������ʾ�ü�����
        if (m_isClipWindowSet && m_objects.empty()) {
            m_clipWindow.Draw(&memDC);
        }
        
        // 3.2 ������������ɵ�ͼ�ζ���
        for (const auto& obj : m_objects) {
            obj->Draw(&memDC);
        }
        
        // 3.3 �������λ��Ƶ�ʵʱԤ��
        if (m_isDrawingPolygon && m_currentPolygon) {
            // ���Ƶ�ǰ�����
            m_currentPolygon->Draw(&memDC);
            
            // ��������δ��գ���ʾԤ����
            if (!m_currentPolygon->IsClosed()) {
                DrawPreviewLine(&memDC);
            }
        }
        
        // 3.4 ��ʾ������ʾ
        DrawPrompt(&memDC);
    }
    
    // 4. ���ڴ�DC���ݸ��Ƶ���Ļ
    pDC->BitBlt(0, 0, rect.Width(), rect.Height(), 
                &memDC, 0, 0, SRCCOPY);
}
```

2. ����¼���������
```cpp
void CCGLabView::OnLButtonDown(UINT nFlags, CPoint point) {
    if (m_isDrawingPolygon && m_currentPolygon) {
        if (!m_currentPolygon->IsClosed()) {
            // ��Ӷ���ζ���
            m_currentPolygon->AddVertex(Point2D(point.x, point.y));
            m_lastMousePos = point;
            Invalidate();  // �����ػ�
        }
        else if (m_currentPolygonAlgorithm != Polygon::ALGO_SCANLINE) {
            // ������ѷ�գ��������ӵ�
            m_currentPolygon->SetSeed(Point2D(point.x, point.y));
            m_currentPolygon->GeneratePoints();
            Invalidate();
        }
    }
}

void CCGLabView::OnRButtonDown(UINT nFlags, CPoint point) {
    if (m_isDrawingPolygon && m_currentPolygon) {
        if (!m_currentPolygon->IsClosed()) {
            // ��ն����
            m_currentPolygon->Close();
            
            // �����㷨���;�����������
            if (m_currentPolygonAlgorithm == Polygon::ALGO_SCANLINE) {
                // ɨ�����㷨ֱ����������
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
        // ����Ԥ���ߵ��յ�
        m_lastMousePos = point;
        Invalidate();
    }
}
```

3. ״̬ת������
```cpp
// �������λ���ģʽ
void CCGLabView::OnPolygonX() {
    ClearScreen();  // �����������
    m_isDrawingPolygon = true;
    m_currentPolygon = std::make_shared<Polygon>();
    m_currentPolygon->SetAlgorithm(Polygon::ALGO_SCANLINE);
    m_currentPolygonAlgorithm = Polygon::ALGO_SCANLINE;
}

// �л���3Dģʽ
void CCGLabView::On3dtransformOriginal() {
    ClearAll();
    m_is3DMode = true;
    m_isOrthographic = false;
    m_frustum = std::make_shared<Frustum>();
    UpdateProjection();
    Invalidate();
}
```

ע�⣺���ϴ���չʾ����Ҫ�Ŀ������̣���Ϊ����ʾĿ�ģ�������ƽ����ְ������View���С�

## ��������

- Visual Studio 2022
- MFC
- C++17
- Windows SDK 10.0

## ����������

### ���뻷������
- ƽ̨���߼�: ѡ��v143(VS2022)
- Windows SDK�汾: 10.0
- MFC��ʹ��: �ھ�̬����ʹ��MFC
- �ַ���: ʹ��Unicode�ַ���
- C\++���Ա�׼: C\++17

### ���벽��
1. ʹ��Visual Studio�򿪽�������ļ�(.sln)
2. ���ý������ƽ̨Ϊx64
3. ѡ��Debug����Release������
4. ���Build -> Build Solution���й���
5. �ȴ��������
6. ��x64/ReleaseĿ¼���ҵ���ִ���ļ�

## ʹ��˵��

1. ѡ��˵��е��㷨����
2. ������ʾ�����Ҫ����
3. �۲��㷨ִ�н���Ŀ��ӻ�չʾ
4. ����ʹ��Clear�������

## �ܹ����

��Ŀ���÷ֲ�ܹ�:
- �㷨��: ʵ�ָ���ͼ��ѧ�㷨
- ģ�Ͳ�: ����ͼ�ζ�������ݽṹ
- ��ͼ��: �����û�������ͼ����ʾ

## ����ʾ��

```cpp
// ʹ��Bresenham�㷨����ֱ��
auto line = std::make_shared<MyGraphics::Line>();
line->SetAlgorithm(MyGraphics::Line::ALGO_BRESENHAM);
line->SetPoints(start, end);
line->GeneratePoints();
```

## ��νṹ

```
������ Algorithms/       # �㷨ʵ��
������ Math/            # ��ѧ������
������ Models/          # ͼ��ģ����
������ Dialogs/         # �Ի���UI
```

## ��չ���Զ���

### ����µ�ͼ���㷨
1. �����㷨�ӿ�
```cpp
// �ڶ�Ӧ��IxxxAlgorithm.hpp������½ӿ�
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

2. ʵ���㷨��
```cpp
// ���µ��㷨ʵ���ļ���
class NewAlgorithm : public INewAlgorithm {
public:
    std::vector<Point2D> GeneratePoints(...) override {
        // ʵ���㷨�߼�
    }
};
```

3. ��ͼ�ζ����������֧��
```cpp
// �ڶ�Ӧ��ͼ������
class Shape : public GraphicsObject {
public:
    enum Algorithm {
        // ������㷨����
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

4. �����û�����
   - ����Դ�ļ�����Ӳ˵���
   - ����������
   - ʵ�ֽ����߼�

### ����µ�ͼ�ζ���
1. �����µ�ͼ����
```cpp
class NewShape : public GraphicsObject {
public:
    NewShape() : GraphicsObject(OT_NEWSHAPE) {}
    
    void GeneratePoints() override {
        // ʵ�ֵ������߼�
    }
    
    void Draw(CDC* pDC) override {
        // ʵ�ֻ����߼�
    }
};
```

2. �������㷨֧��
   - �����㷨�ӿ���
   - ʵ�־����㷨��
   - ��ͼ�����м����㷨

3. ������������
   - ��Ӳ�������Ի���
   - ʵ���������
   - ���²˵��͹�����

### �޸������㷨
1. �ҵ���Ӧ���㷨ʵ����
2. �޸�GeneratePoints()�����е��߼�
3. ���ֽӿڲ��䣬ȷ��������

## ���

����Ŀ��ѭ MIT ���֤��


***Designed by Ziyu ZHOU at SDAU***

*30th. Nov. 2024*