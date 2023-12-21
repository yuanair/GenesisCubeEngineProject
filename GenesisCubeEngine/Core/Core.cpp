//
// Created by admin on 2023/12/19.
//

#include "Core.h"
#include "Debug.h"
#include "../Game/GWindow.h"

namespace GenesisCubeEngine
{
    
    const TCHAR Core::name[] = TEXT("Genesis Cube Engine");
    
    const TCHAR Core::versionString[] = TEXT("0.1-alpha");
    
    const TCHAR Core::buildTime[] = TEXT(__DATE__);
    
    const int Core::version_code = 1;
    
    static HINSTANCE hInstance = nullptr;
    
    static HINSTANCE hPrevInstance = nullptr;
    
    static LPSTR cmdLine = nullptr;
    
    static int nShowCmd = 0;
    
    void Core::Exit(int nExitCode)
    {
        PostQuitMessage(nExitCode);
    }
    
    HINSTANCE Core::GetInstance()
    {
        return hInstance;
    }
    
    HINSTANCE Core::GetPrevInstance()
    {
        return hPrevInstance;
    }
    
    LPSTR Core::GetCmdLine()
    {
        return cmdLine;
    }
    
    int Core::GetShowCmd()
    {
        return nShowCmd;
    }
    
    int Run()
    {
        // 定义
        MSG msg = {};
        FTimer timer;
        
        // 当为DEBUG模式时，内存泄漏检测
        if (GenesisCubeEngine::bIsDebug)
        {
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
        }
        
        // 获取程序
        GCProgram();
        timer.Reset();
        
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
                GWindow::Tick();
            }
        }
        
        // 删除日志实例
        GenesisCubeEngine::FLogger::DeleteInstance();
        
        return (int) msg.wParam;
    }
    
} // GenesisCubeEngine

int WINAPI WinMain
    (
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nShowCmd
    )
{
    GenesisCubeEngine::hInstance = hInstance;
    GenesisCubeEngine::hPrevInstance = hPrevInstance;
    GenesisCubeEngine::cmdLine = lpCmdLine;
    GenesisCubeEngine::nShowCmd = nShowCmd;
    return GenesisCubeEngine::Run();
}
