# GenesisCubeEngine

>
> 使用DirectX渲染的轻量化游戏引擎
>

> IDE: CLion

> 编译器：MSVC

> C++ 20

## 使用

```c++
#include <GenesisCubeEngine/Core/Core.h>

class MyProgram : public GenesisCubeEngine::GProgram
{
public:

    MyProgram() noexcept = default;
    
    ~MyProgram() noexcept override = default;

public:

    void Init() override
    {
        // do some work...
    }
    
    void Tick(double deltaTime) override
    {
        // do some work...
    }
    
    void End() override
    {
        // do some work...
    }

private:

    // do some work...

};

GenesisCubeEngine::GProgram *GCProgram()
{
    return new MyProgram();
}


```
