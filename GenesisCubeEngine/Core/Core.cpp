//
// Created by admin on 2023/12/19.
//

#include "Core.h"
#include "Debug.h"

namespace GenesisCubeEngine
{
    
    const TCHAR Core::name[] = TEXT("Genesis Cube Engine");
    
    const TCHAR Core::versionString[] = TEXT("0.1-alpha");
    
    const TCHAR Core::buildTime[] = TEXT(__DATE__);
    
    const int Core::version_code = 1;
    
    HINSTANCE Core::hInstance = nullptr;
    
    HINSTANCE Core::hPrevInstance = nullptr;
    
    LPSTR Core::cmdLine = nullptr;
    
    int Core::nShowCmd = 0;
    
    void Core::TestGenesisCubeEngine()
    {
        MessageBox(nullptr, buildType, TEXT("GCE编译类型"), MB_OK);
        MessageBox(nullptr, TEXT("<Test field测试字段>"), TEXT("GCE测试"), MB_OK);
    }
    
    void Core::Exit(int nExitCode)
    {
        PostQuitMessage(nExitCode);
    }
    
    
} // GenesisCubeEngine

int Run()
{
    // 定义
    MSG msg = {};
    
    // 当为DEBUG模式时，内存泄漏检测
    if (GenesisCubeEngine::bIsDebug)
    {
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    }
    
    // 获取程序
    GCProgram();
    
    // 消息循环
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            GCTick();
        }
    }
    
    // 删除日志实例
    GenesisCubeEngine::FLogger::DeleteInstance();
    
    return (int) msg.wParam;
}

int WINAPI WinMain
    (
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nShowCmd
    )
{
    GenesisCubeEngine::Core::hInstance = hInstance;
    GenesisCubeEngine::Core::hPrevInstance = hPrevInstance;
    GenesisCubeEngine::Core::cmdLine = lpCmdLine;
    GenesisCubeEngine::Core::nShowCmd = nShowCmd;
    return Run();
}