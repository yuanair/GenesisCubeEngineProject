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


class MyProgram : public GProgram
{
public:
	
	explicit MyProgram(int nShowCmd) : nShowCmd(nShowCmd) {}
	
	~MyProgram() override = default;

public:
	
	TString TText(const TString &key)
	{
		return GLanguage::Find(gameText, key, nowLanguage);
	}
	
	static void OnDropFiles(FWindow::EventOnDropFilesArgs args)
	{
		std::vector<TPtr<GFileName>> files;
		GFileName::DragQuery(args.hDropInfo, files);
		TString buffer;
		for (size_t i = 0; i < files.size(); i++)
		{
			buffer.append(files[i]->GetFileName()).push_back(TEXT('\n'));
			if (auto *ptr = files[i].Cast<GDirectoryName>()) ptr->Find(files);
		}
		FLogger::Inst().LogInfoODS(buffer);
	}
	
	void Start() override
	{
		FLogger::Inst().LogInfoODS(TEXT("MyProgram Start"));
		// 注册窗口类
		FWindow::Register(mainWndClassName, FWindow::GetIcon(IDI_ICON_Main), FWindow::GetIcon(IDI_ICON_MainSm));
		
		FLogger::Inst().LogInfoODS(TEXT("test"));
		
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
		
		// addWindow.SubMBox(std::format(TEXT("Test: |{:.3f}|"), 42.48978), FCore::name);
		
		mainWindow.eOnTick += [](FWindow::EventOnTickArgs args) -> void
		{
//			LOG_INFO FLogger::Inst() <<
//											std::format(
//												TEXT("deltaTime:{:.7f}\nnowTime:{}"), args.deltaTime,
//												FTimer::LocalTime());
		
		};
		
		TString jsonBuffer;
		{
			std::locale::global(std::locale("zh_CN.UTF-8"));
			TFStream fstream(TEXT("Test.json"), std::ios::in);
			if (!fstream.is_open())
			{
				FWindow::MBox(TEXT("can not open Test.json"), Text("MainWindowName"));
			}
			else
			{
				TString buffer;
				while (std::getline(fstream, buffer))
				{
					jsonBuffer.append(buffer);
					jsonBuffer.push_back(TEXT('\n'));
				}
				fstream.close();
			}
		}
		
		JSON::JsonReader jsonReader(jsonBuffer);
		TPtr<JSON::Json> json = jsonReader.Next();
		
		FLogger::Inst().LogInfoODS(json->ToString());
		
	}
	
	void Tick() override
	{
		mainWindow.Tick();
		addWindow.Tick();
	}
	
	void End() override
	{
		FLogger::Inst().LogInfoODS(TEXT("MyProgram End"));
	}

public:
	
	// 主窗口类名
	static constexpr TCHAR mainWndClassName[] = TEXT("main window class");

private:
	
	const int nShowCmd;
	
	FWindow mainWindow;
	
	FWindow addWindow;
	
	GLanguage zh_cn = GLanguage(TEXT("zh_cn"), TEXT("简体中文"));
	
	GLanguage en_us = GLanguage(TEXT("en_us"), TEXT("English"));
	
	GLanguage language_debug = GLanguage(TEXT("debug"), TEXT("调试语言"));
	
	GLanguage *nowLanguage = &zh_cn;
	
	GStringList gameText =
		{
			{
				TEXT("Language"),       {{&zh_cn, TEXT("语言 (Language)")}, {
																				&en_us, TEXT("Language（语言）")
																			}, {
																				   &language_debug, TEXT("Language")
																			   }}},
			{
				TEXT("MainWindowName"), {{&zh_cn, TEXT("主窗口")},          {
																				&en_us, TEXT("main window")
																			}, {
																				   &language_debug, TEXT("mainWindow")
																			   }}},
			{
				TEXT("AddWindowName"),  {{&zh_cn, TEXT("附加窗口")},        {
																				&en_us, TEXT("add window")
																			}, {
																				   &language_debug, TEXT("addWindow")
																			   }}}
		};
	
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
	return GenesisCubeEngine::FCore::Run(myProgram);
}
