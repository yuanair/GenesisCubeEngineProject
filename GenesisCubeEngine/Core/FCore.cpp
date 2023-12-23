//
// Created by admin on 2023/12/19.
//

#include "FCore.h"
#include "../Debug/Debug.h"
#include "../Game/FWindow.h"

namespace GenesisCubeEngine
{
    
    const TCHAR FCore::name[] = TEXT("Genesis Cube Engine");
    
    const TCHAR FCore::versionString[] = TEXT("0.1-alpha");
    
    const TCHAR FCore::buildTime[] = TEXT(__DATE__);
    
    const int FCore::version_code = 1;
    
    static HINSTANCE hInstance = nullptr;
    
    static HINSTANCE hPrevInstance = nullptr;
    
    static LPSTR cmdLine = nullptr;
    
    static int nShowCmd = 0;
    
    void FCore::Exit(int nExitCode)
    {
        PostQuitMessage(nExitCode);
    }
    
    HINSTANCE FCore::Shell(HWND hWnd, const TString &operation, const TString &file, const TString &parameters,
                           const TString &directory, INT showCmd)
    {
        return ShellExecute(hWnd, operation.c_str(), file.c_str(), parameters.c_str(), directory.c_str(), showCmd);
    }
    
    HINSTANCE FCore::GetInstance()
    {
        return hInstance;
    }
    
    HINSTANCE FCore::GetPrevInstance()
    {
        return hPrevInstance;
    }
    
    LPSTR FCore::GetCmdLine()
    {
        return cmdLine;
    }
    
    int FCore::GetShowCmd()
    {
        return nShowCmd;
    }
    
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
        GProgram *program = GCProgram();
        if (program == nullptr) throw ENullptrException(__FUNCSIG__ TEXT(":: program is nullptr"));
        
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
                program->Tick();
            }
        }
        
        // 删除程序
        delete program;
        
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
