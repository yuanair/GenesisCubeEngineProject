//
// Created by admin on 2023/12/19.
//
#include <GenesisCubeEngine/Core/Core.h>
#include <GenesisCubeEngine/Game/GWindow.h>

#include "../Resource/resource.h"

using namespace std;
using namespace GenesisCubeEngine;

// 主窗口类名
constexpr TCHAR mainWindowClassName[] = TEXT("main window class");

// 主窗口名
constexpr TCHAR mainWindowWindowName[] = TEXT("main window");


GWindow mainWindow;

void GCProgram()
{
    
    // 注册窗口类
    if (!GWindow::Register(
        mainWindowClassName, LoadIcon(Core::hInstance, MAKEINTRESOURCEW(IDI_ICON_ProgramIcon)),
        LoadIcon(Core::hInstance, MAKEINTRESOURCEW(IDI_ICON_ProgramIconSm))))
    {
        GWindow::MBox(
            nullptr, TEXT("GWindow::RegisterClass() Failed"), mainWindowWindowName, MB_ICONSTOP | MB_OK
        );
        return Core::Exit(-1);
    }
    
    // 创建窗口
    if (!mainWindow.Create(mainWindowClassName, mainWindowWindowName))
    {
        GWindow::MBox(nullptr, TEXT("GWindow.Create() Failed"), mainWindowWindowName, MB_ICONSTOP | MB_OK);
        return Core::Exit(-1);
    }
    
    // 显示窗口
    mainWindow.ShowAndUpdate();
    
    // 销毁窗口函数
    mainWindow.eOnClose += [](GWindow::EventArgs args) -> void
    {
        args.window.Destroy();
    };
    
    OutputDebugString(TEXT("Test Debug View!"));
    
    int *a = new int;
    
}

void GCTick()
{
    mainWindow.Tick();
}