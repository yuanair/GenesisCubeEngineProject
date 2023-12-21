//
// Created by admin on 2023/12/19.
//
#include <GenesisCubeEngine/Core/Core.h>
#include <GenesisCubeEngine/Game/GWindow.h>
#include <GenesisCubeEngine/Core/Debug.h>
#include <GenesisCubeEngine/Resource/resource.h>
#include <GenesisCubeEngine/Localization/Localization.h>
#include <GenesisCubeEngine/IO/GFile.h>

#define Text(key) TText(TEXT(key))

using namespace std;
using namespace GenesisCubeEngine;

/// 中文
GLanguage zh_cn(TEXT("zh_cn"), TEXT("简体中文"));

/// 英文
GLanguage en_us(TEXT("en_us"), TEXT("English"));

/// 当前语言
GLanguage *nowLanguage = &zh_cn;

/// 游戏文字
GStringList gameText =
    {
        {TEXT("Language"),       {{&zh_cn, TEXT("语言 (Language)")}, {&en_us, TEXT("Language（语言）")}}},
        {TEXT("MainWindowName"), {{&zh_cn, TEXT("主窗口")},          {&en_us, TEXT("main window")}}},
        {TEXT("AddWindowName"),  {{&zh_cn, TEXT("附加窗口")},        {&en_us, TEXT("add window")}}}
    };

TString TText(const TString &key)
{
    return GLanguage::Find(gameText, key, nowLanguage);
}

// 主窗口类名
constexpr TCHAR mainWndClassName[] = TEXT("main window class");


GWindow mainWindow;
GWindow addWindow;

void OnDropFiles(GWindow::EventOnDropFilesArgs args)
{
    std::vector<TPtr<GFileName>> files;
    GFile::DragQuery(args.hDropInfo, files);
    for (size_t i = 0; i < files.size(); i++)
    {
        FLogger::GetInstance() << files[i]->GetFileName() << TEXT("\n");
        if (auto *ptr = files[i].Cast<GDirectory>()) ptr->Find(files);
    }
    LOG_INFO_ODS_M(nullptr, Core::name) FLogger::GetInstance();
}

void GCProgram()
{
    FLogger::GetInstance().RemoveOldLogFile(time_t(0));
    
    // 注册窗口类
    GWindow::Register(mainWndClassName, GWindow::GetIcon(IDI_ICON_Main), GWindow::GetIcon(IDI_ICON_MainSm));
    
    // 创建窗口
    mainWindow.Create(mainWndClassName, Text("MainWindowName"));
    addWindow.Create(mainWndClassName, Text("AddWindowName"));
    
    // 销毁窗口函数
    mainWindow.eOnClose += GWindow::DestroyOnClose;
    addWindow.eOnClose += GWindow::DestroyOnClose;
    
    // 退出程序函数
    mainWindow.eOnDestroy += GWindow::ExitOnDestroy;
    
    // 拖放文件函数
    mainWindow.eOnDropFiles += OnDropFiles;
    
    // 显示窗口
    mainWindow.ShowAndUpdate();
    addWindow.ShowAndUpdate();
    
}

