//
// Created by admin on 2023/12/19.
//

#include <GenesisCubeEngine/Core/FCore.h>
#include <GenesisCubeEngine/Core/FFormatter.h>
#include <GenesisCubeEngine/Game/FWindow.h>
#include <GenesisCubeEngine/Debug/Debug.h>
#include <GenesisCubeEngine/Resource/resource.h>
#include <GenesisCubeEngine/Localization/Localization.h>
#include <GenesisCubeEngine/IO/GFileName.h>
#include <GenesisCubeEngine/JSON/Json.h>
#include <GenesisCubeEngine/JSON/JsonReader.h>

#define Text(key) TText(TEXT(key))

using namespace std;
using namespace GenesisCubeEngine;


class MyProgram
{
public:
	
	explicit MyProgram(int nShowCmd)
	{
		
		{
			std::locale::global(std::locale("zh_CN.UTF-8"));
			TIFStream ifStream;
			ifStream.open(TEXT("Data/zh_cn.json"), std::ios::in);
			if (ifStream.is_open())
			{
				JSON::JsonReader jsonReader(ifStream);
				this->zh_cn.LoadFromJson(*jsonReader.NextSafe());
				ifStream.close();
			}
			else
			{
				FWindow::MBox(TEXT("can not open zh_cn.json"), FCore::name);
			}
			ifStream.open(TEXT("Data/en_us.json"), std::ios::in);
			if (ifStream.is_open())
			{
				JSON::JsonReader jsonReader(ifStream);
				this->en_us.LoadFromJson(*jsonReader.NextSafe());
				ifStream.close();
			}
			else
			{
				FWindow::MBox(TEXT("can not open en_us.json"), FCore::name);
			}
			
			ifStream.open(TEXT("Data/language_debug.json"), std::ios::in);
			if (ifStream.is_open())
			{
				JSON::JsonReader jsonReader(ifStream);
				this->language_debug.LoadFromJson(*jsonReader.NextSafe());
				ifStream.close();
			}
			else
			{
				FWindow::MBox(TEXT("can not open language_debug.json"), FCore::name);
			}
		}
		
		// 注册窗口类
		FWindow::Register(mainWndClassName, FWindow::GetIcon(IDI_ICON_Main), FWindow::GetIcon(IDI_ICON_MainSm));
		
		// 创建窗口
		mainWindow.Create(mainWndClassName, Text("MainWindowName"));
		addWindow.Create(mainWndClassName, Text("AddWindowName"));
		
		// 销毁窗口函数
		mainWindow.eOnClose += FWindow::DestroyOnClose;
		addWindow.eOnClose += FWindow::DestroyOnClose;
		
		// 退出程序函数
		mainWindow.eOnDestroy += FWindow::ExitOnDestroy;
		
		// 拖放文件函数
		mainWindow.eOnDropFiles += OnDropFiles;
		
		// 显示窗口
		mainWindow.ShowAndUpdate(nShowCmd);
		addWindow.ShowAndUpdate(nShowCmd);
		
		mainWindow.bEnableOnChar = true;
		
		mainWindow.eOnChar += [](FWindow::EventCharArgs args) -> void
		{
			args.window.SetWindowName(args.window.GetWindowName() + args.input);
		};
		
		mainWindow.eOnTick += [](FWindow::EventOnTickArgs args) -> void
		{
		
		};
		
	}
	
	~MyProgram()
	{
		FLogger::Inst().LogInfoODS(TEXT("MyProgram End"));
	}

public:
	
	TString TText(const TString &key)
	{
		if (nowLanguage == nullptr) return key;
		auto iter = nowLanguage->values.find(key);
		if (iter == nowLanguage->values.end()) return key;
		return iter->second;
	}
	
	static void OnDropFiles(FWindow::EventOnDropFilesArgs args)
	{
		std::list<TPtr<GFileName>> files;
		GFileName::DragQuery(args.hDropInfo, files);
		TString buffer;
		for (auto file: files)
		{
			buffer.append(file->GetFileName()).push_back(TEXT('\n'));
			if (auto *ptr = file.Cast<GDirectoryName>()) ptr->Find(files);
		}
		FLogger::Inst().LogInfoODS(buffer);
	}
	
	void Tick()
	{
		static auto deltaTime = std::chrono::milliseconds(int64_t(1.0f / 60.0f * 1000.0f));
		auto timePoint = std::chrono::system_clock::now() + deltaTime;
		mainWindow.Tick();
		
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(mainWindow.GetHwnd(), &ps);
		auto rect1 = mainWindow.GetWindowRect();
		RECT rect = {.left=rect1.x, .top=rect1.y, .right=rect1.x + rect1.width, .bottom=rect1.y + rect1.height};
		DrawText(hdc, buffer.c_str(), -1, &rect, DT_LEFT);
		EndPaint(mainWindow.GetHwnd(), &ps);
		
		addWindow.Tick();
		std::this_thread::sleep_until(timePoint);
	}

public:
	
	// 主窗口类名
	static constexpr TCHAR mainWndClassName[] = TEXT("main window class");

private:
	
	TString buffer;
	
	FWindow mainWindow;
	
	FWindow addWindow;
	
	GLanguage zh_cn;
	
	GLanguage en_us;
	
	GLanguage language_debug;
	
	GLanguage *nowLanguage = &zh_cn;
	
};

int WINAPI wWinMain
	(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPWSTR lpCmdLine,
		int nShowCmd
	)
{
	MyProgram myProgram(nShowCmd);
	GenesisCubeEngine::FCore::Init();
	while (FWindow::PeekEvent())
	{
		myProgram.Tick();
	}
	return 0;
}
