//
// Created by admin on 2023/12/19.
//

#include <GenesisCubeEngine/Core/FCore.h>
#include <GenesisCubeEngine/Core/FFormatter.h>
#include <GenesisCubeEngine/Game/GWindow.h>
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
	
	MyProgram(const TString &cmdLine, int nShowCmd);
	
	~MyProgram();

public:
	
	TString TText(const TString &key);
	
	void Tick();

private:
	
	TPtr<GWindow> mainWindow;
	
	TPtr<GWindow> addWindow;
	
	GLanguage zh_cn;
	
	GLanguage en_us;
	
	GLanguage language_debug;
	
	GLanguage *nowLanguage = &zh_cn;
	
	FTimer timer;
};


class MainWindow : public GWindow
{
public:
	
	// 主窗口类名
	static constexpr TCHAR mainWndClassName[] = TEXT("main window class");
	
	explicit MainWindow(int nShowCmd, MyProgram &program);
	
	void OnChar(const TChar &input) override;
	
	void OnString(const TString &input) override;
	
	void OnTick(float deltaTime) override;
	
	void OnDropFiles(HDROP hDropInfo) override;

protected:
	void OnDestroy() override;

public:


private:
	
	MyProgram &program;
	
	TString buffer;
	
};

void MainWindow::OnDropFiles(HDROP hDropInfo)
{
	std::list<TPtr<GFileName>> files;
	GFileName::DragQuery(hDropInfo, files);
	TString message;
	for (auto file: files)
	{
		message.append(file->GetFileName()).push_back(TEXT('\n'));
		if (auto *ptr = file.Cast<GDirectoryName>()) ptr->Find(files);
	}
	FLogger::Inst().LogInfoODS(message);
}

MainWindow::MainWindow(int nShowCmd, MyProgram &program)
	: program(program)
{
	
	// 注册窗口类
	GWindow::Register(mainWndClassName, FCore::GetIcon(IDI_ICON_Main), FCore::GetIcon(IDI_ICON_MainSm));
	
	// 创建窗口
	Create(mainWndClassName, program.Text("MainWindowName"));
	
	// 显示窗口
	ShowAndUpdate(nShowCmd);
	
	bEnableOnChar = true;
	
}

void MainWindow::OnChar(const TChar &input)
{
	GWindow::OnChar(input);
	if (input == VK_BACK)
	{
		if (!buffer.empty()) buffer.pop_back();
	}
	else buffer += input;
	// input point
	inputPoint = {(int) buffer.size(), 0};
}

void MainWindow::OnString(const TString &input)
{
	GWindow::OnString(input);
	buffer += input;
	// input point
	inputPoint = {(int) buffer.size(), 0};
}

void MainWindow::OnTick(float deltaTime)
{
	GWindow::OnTick(deltaTime);
	HDC hdc = GetDC(GetHWnd());
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
	
	RECT rect = {0, 0, 500, 500};
	FillRect(hdc, &rect, brush);
	DrawText(hdc, buffer.c_str(), -1, &rect, DT_LEFT);
	
	DeleteBrush(brush);
	DeleteDC(hdc);
}

void MainWindow::OnDestroy()
{
	GWindow::OnDestroy();
	FCore::Exit(0);
}

class AddWindow : public GWindow
{
public:
	
	AddWindow(int nShowCmd, MyProgram &program)
		: program(program)
	{
		
		// 创建窗口
		Create(MainWindow::mainWndClassName, program.Text("AddWindowName"));
		
		// 显示窗口
		ShowAndUpdate(nShowCmd);
	}
	
	~AddWindow() override
	= default;

public:
	
	MyProgram &program;
	
};


MyProgram::MyProgram(const TString &cmdLine, int nShowCmd)
{
	GenesisCubeEngine::FCore::Init();
	
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
			GWindow::MBox(TEXT("can not open zh_cn.json"), FCore::name);
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
			GWindow::MBox(TEXT("can not open en_us.json"), FCore::name);
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
			GWindow::MBox(TEXT("can not open language_debug.json"), FCore::name);
		}
	}
	
	mainWindow = new MainWindow(nShowCmd, *this);
	addWindow = new AddWindow(nShowCmd, *this);
}

void MyProgram::Tick()
{
	timer.Tick();
	auto deltaTime = (float) timer.GetDeltaTime();
	mainWindow->Tick(deltaTime);
	addWindow->Tick(deltaTime);
}

TString MyProgram::TText(const TString &key)
{
	if (nowLanguage == nullptr) return key;
	auto iter = nowLanguage->values.find(key);
	if (iter == nowLanguage->values.end()) return key;
	return iter->second;
}

MyProgram::~MyProgram() = default;

#ifdef UNICODE

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
#else

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#endif
{
	MyProgram myProgram(lpCmdLine, nShowCmd);
	while (GWindow::PeekEvents())
	{
		myProgram.Tick();
	}
	return 0;
}