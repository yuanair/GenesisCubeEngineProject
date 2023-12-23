# GenesisCubeEngine

>
> 使用DirectX渲染的轻量化游戏引擎
>

> IDE: CLion

> 编译器：MSVC

> C++ 20

## 使用

> 编译时定义UNICODE宏

```c++
#include <GenesisCubeEngine/FCore/FCore.h>
#include <GenesisCubeEngine/Game/FWindow.h>

using namespace GenesisCubeEngine;

///
/// 定义程序类
///
class MyProgram : public GProgram
{
public:
    
    MyProgram()
    {
        // 注册窗口类
        FWindow::Register(wndClassName);
        
        // 创建窗口
        window.Create(wndClassName, wndName);
        
        // 当窗口关闭时销毁窗口
        window.eOnClose += FWindow::DestroyOnClose;
        
        // 当窗口销毁时退出程序
        window.eOnDestroy += FWindow::ExitOnDestroy;
        
        // do some works ...
        
        // 显示窗口
        window.ShowAndUpdate();
    }
    
    ~MyProgram() override
    {
        // do some works ...
    }

public:
    
    void Tick() override
    {
        window.Tick();
    }

public:
    
    // 窗口类名
    static constexpr TCHAR wndClassName[] = TEXT("main window class");
    
    // 窗口名
    static constexpr TCHAR wndName[] = TEXT("main window");

private:
    
    FWindow window;
    
}

GProgram* GCProgram()
{
    return new MyProgram();
}


```
